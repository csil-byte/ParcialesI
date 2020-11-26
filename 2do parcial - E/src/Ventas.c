/*
 * Ventas.c
 *
 *  Created on: 21 sep. 2020
 *      Author: user
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Ventas.h"
#include "Informes.h"
#include "LinkedList.h"
#include "utn.h"
#include "Controller.h"

#define LONG_NOMBRE 4096
#define CABA 1
#define ZONA_SUR 2
#define ZONA_OESTE 3
#define COBRADO 0
#define A_COBRAR 1
#define MAX 1
#define MIN 0

static int findMaxId(LinkedList* pArrayListVenta);

//////////////////////// //////       ID         ///////////////////////////////////////////////////////////

/** \brief Encuentra cual es el max id, según la longitud de la lista, la recorre con un for hasta
 * encontrar el valor maximo y lo devuelve por return.
 *
 * \param LinkedList* pArrayListVenta
 * \return int  --------- devuelve -1 cuando hay error |  id > -1 cuando todo ok
 *
 */
static int findMaxId(LinkedList* pArrayListVenta)
{
	Venta* pVenta;
	int len;
	int max;
	int id = -1;

	if(pArrayListVenta != NULL)
	{
		len = ll_len(pArrayListVenta);
		for(int i =0;i<len;i++)
		{
			pVenta = (Venta*)ll_get(pArrayListVenta,i);
			venta_getIdVenta(pVenta,&id);
			if (i == 0 || id > max)
			{
				max = id;
			}
		}
		id = max;
	}
	return id;
}
/** \brief Genera id nuevo llamando a findMaxId para tener en cuenta el maximo y usa una bandera para saber
 * cuando se cargan los datos por primera vez para leer el listado de ids.
 *
 * \param LinkedList* pArrayListVenta
 * \return int  --------- devuelve -1 cuando hay error |  id > -1 cuando todo ok
 *
 */
int venta_generarIdNuevo(LinkedList* pArrayListVenta)
{
	static int id = -1;
    static int flag = 1;


	    if(pArrayListVenta != NULL)
	    {
			if(flag == 1)
			{
				id = findMaxId(pArrayListVenta);
				flag++;
			}
			id++;
	    }
	    return id;
}

///////////////////////////////// INFORMES - ESTADÍSTICAS ///////////////////////////////////

/** \brief según condicion -> estado, llama a un clone filter para generar una nueva LL
 *
 *  \param pEstructura LinkedList* \param pEstructura LinkedList* \param pEstructura LinkedList* para guardar
 * \return int -1 si listas están vacías | 0 si todo k
 *
 */
int ventas_cobradosPorCliente(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, LinkedList** ventas_cobradas, int estado )
{
	int retorno = -1;
	if (ll_isEmpty(pArrayListVenta)==0 && ll_isEmpty(pArrayListCliente)==0 && (estado == 0 || estado == 1))
		{
			*ventas_cobradas = ll_CF_condicion(pArrayListVenta,pArrayListCliente, CF_condicionFiltro_ventasEstado, estado);
			if ( ll_isEmpty(*ventas_cobradas)==0)
			{
					retorno = 0;
			}
		}
	return retorno;
}
/** \brief FILTER = ll_CF_condicion
 *
 *  \param pEstructura LinkedList* \param pEstructura LinkedList* \param pEstructura LinkedList* para guardar
 * \return int -1 si listas están vacías | 0 si todo k
 *
 */
int CF_condicionFiltro_ventasEstado(void* id_venta, void* id_cliente, int estado )
{
	int retorno = -1;
	Venta* bufferVentas;
	Cliente* bufferClientes;
	bufferVentas = (Venta*) id_venta;
	bufferClientes = (Cliente*) id_cliente;

	if (bufferVentas != NULL && bufferClientes != NULL && (estado == 0 || estado ==1))
	{
		if (bufferVentas->estado == estado)
			{
				retorno = 0;
			}
		else
		{
			retorno = 1;
		}
	}
	return retorno;
}


///////////////////////////////////////  LISTADOS | AUXILIARES  ///////////////////////////////////////

/** \brief Listar ventas
 *	Guarda la longitud de la lista para luego iterar sobre ella e imprimir los datos.
 *
 * \param pArrayListVenta LinkedList*
 * \return int -1 si hubo error | 0 si todo ok
 *
 */
int controller_ListVenta(LinkedList* pArrayListVenta)
{
	int retorno = -1;
	Venta* bufferVenta;
	int len;

	if (pArrayListVenta != NULL && ll_len(pArrayListVenta) > -1 &&(Venta*) ll_get(pArrayListVenta,0) != NULL)
		{
			len = ll_len(pArrayListVenta);
			for (int i = 0; i < len ; i++)
			{
				bufferVenta = (Venta*)ll_get(pArrayListVenta,i);
				printf("==============      ID Venta: %d | ID Cliente: %d | Nombre archivo: %s | Cantidad: %d | Estado: %d | Zona: %d |     ==============  \n",
					bufferVenta->idVenta, bufferVenta->idCliente, bufferVenta->nombreArchivo, bufferVenta->cantidad, bufferVenta->estado, bufferVenta->zona);
			}
			retorno = 0;
		}
	return retorno;
}
/** \brief Listar ventas SIN COBRAR
 *	Guarda la longitud de la lista para luego iterar sobre ella e imprimir los datos.
 *
 * \param pArrayListVenta LinkedList*
 * \return int -1 si hubo error | 0 si todo ok
 *
 */
int ventas_listSinCobrar(LinkedList* pArrayListVenta)
{
	int retorno = -1;
	Venta* bufferVenta;
	int len;

	if (ll_isEmpty(pArrayListVenta)==0)
	{
		if (pArrayListVenta != NULL && ll_len(pArrayListVenta) > -1 &&(Venta*) ll_get(pArrayListVenta,0) != NULL)
		{
			len = ll_len(pArrayListVenta);
			for (int i = 0; i < len ; i++)
			{
				bufferVenta = (Venta*)ll_get(pArrayListVenta,i);
				if (bufferVenta->estado == 1)
				{
					printf("==============Indice: %d | ID Venta: %d | ID Cliente: %d | Nombre archivo: %s | Cantidad: %d | Estado: %d | Zona: %d |     ==============  \n",
					i, bufferVenta->idVenta, bufferVenta->idCliente, bufferVenta->nombreArchivo, bufferVenta->cantidad, bufferVenta->estado, bufferVenta->zona);
				}
			}
			retorno = 0;
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más ventas. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Listar ventas COBRADAS
 *	Guarda la longitud de la lista para luego iterar sobre ella e imprimir los datos.
 *
 * \param pArrayListVenta LinkedList*
 * \return int -1 si hubo error | 0 si todo ok
 *
 */
int ventas_listCobradas(LinkedList* pArrayListVenta)
{
	int retorno = -1;
	Venta* bufferVenta;
	int len;

	if (ll_isEmpty(pArrayListVenta)==0)
	{
		if (pArrayListVenta != NULL && ll_len(pArrayListVenta) > -1 &&(Venta*) ll_get(pArrayListVenta,0) != NULL)
		{
			len = ll_len(pArrayListVenta);
			for (int i = 0; i < len ; i++)
			{
				bufferVenta = (Venta*)ll_get(pArrayListVenta,i);
				if (bufferVenta->estado == 0)
				{
					printf("==============Indice: %d | ID Venta: %d | ID Cliente: %d | Nombre archivo: %s | Cantidad: %d | Estado: %d | Zona: %d |     ==============  \n",
					i, bufferVenta->idVenta, bufferVenta->idCliente, bufferVenta->nombreArchivo, bufferVenta->cantidad, bufferVenta->estado, bufferVenta->zona);
				}
			}
			retorno = 0;
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más ventas. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Listar venta por indice
 *	Hace las validaciones y llama a ll_ger para obtener los datos del venta en ese índice.
 *
 * \param pArrayListVenta LinkedList*  | int index
 * \return int -1 si hubo error | 0 si todo ok
 *
 */
int venta_printByIndex(LinkedList* pArrayListVenta, int index)
{
	int retorno = -1;
	Venta* bufferVenta;

	if (pArrayListVenta != NULL && index > -1 && ll_len(pArrayListVenta) > -1 && index <= ll_len(pArrayListVenta) && (Venta*)ll_get(pArrayListVenta,index) != NULL)
	{
		bufferVenta = (Venta*)ll_get(pArrayListVenta,index);
		printf("==============      ID Venta: %d | ID Cliente: %d | Nombre archivo: %s | Cantidad: %d | Estado: %d | Zona: %d |     ==============  \n",
		bufferVenta->idVenta, bufferVenta->idCliente, bufferVenta->nombreArchivo, bufferVenta->cantidad, bufferVenta->estado, bufferVenta->zona);
		retorno = 0;
	}
	return retorno;
}
/** \brief Buscar venta por id, devolviendo el indice
 *	Itera hasta encontrar el venta solicitado por id, devolviendo el índice dentro de la LL
 *	en el que se encuentra
 *
 * \param pArrayListVenta LinkedList*  |    int id
 * \return int -1 si hubo error | >-1 el indice
 *
 */
int findVentaById(LinkedList* pArrayListVenta, int idVenta)
{
	int retorno = -1;
	int len;
	Venta* bufferVenta;
	if (pArrayListVenta != NULL && idVenta > -1 && ll_len(pArrayListVenta) > -1)
	{
		len = ll_len(pArrayListVenta);
		for (int i = 0; i < len; i++)
		{
			if (bufferVenta != NULL && (Venta*)ll_get(pArrayListVenta,i) != NULL )
			{
				bufferVenta = (Venta*) ll_get(pArrayListVenta,i);
				if( bufferVenta->idVenta == idVenta )
				{
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}
/** \brief Imprimir por id de venta, devolviendo el indice
 *	Itera hasta encontrar la venta solicitado por idVenta, devolviendo el índice
 *	en el que se encuentra
 *
 * \param pArrayListVenta LinkedList*  |    int id
 * \return int -1 si hubo error | >-1 el indice
 *
 */
int venta_PrintById(LinkedList* pVenta, int idVenta)
{
	int retorno = -1;
	int len;
	Venta* b_venta;
	if (pVenta != NULL && idVenta > -1 && ll_len(pVenta) > -1)
	{
		len = ll_len(pVenta);
		for (int i = 0; i < len; i++)
		{
			if (b_venta != NULL && (Venta*)ll_get(pVenta,i) != NULL )
			{
				b_venta = (Venta*) ll_get(pVenta,i);
				if( b_venta->idVenta == idVenta )
				{
					printf("==============Indice: %d | ID Venta: %d | ID Cliente: %d | Nombre archivo: %s | Cantidad: %d | Estado: %d | Zona: %d |     ==============  \n",
					i, b_venta->idVenta, b_venta->idCliente, b_venta->nombreArchivo, b_venta->cantidad, b_venta->estado, b_venta->zona);
					retorno = 0;
					break;
				}
			}
		}
	}
	return retorno;
}


/////////////////////////////////////      AUXILIARES   CONSTRUCTORES     //////////////////////////////////////

/** \brief Permite reservar memoria dinámica para un elemento de la entidad
 *
 * \param  | no recibe |
 * \return puntero de la entidad construida -> Venta*
 *
 */
Venta* venta_new(void)
{
	return (Venta*) malloc (sizeof(Venta));
}
/** \brief Permite darle valores a los campos de la entidad utilizando los setters para acceder de forma segura
 *
 * \param recibe todos los campo de la entidad char | nombre, id, sueldo, horastrabajadas
 * \return int  --------- devuelve puntero a la entidad Venta |  NULL cuando hay error.
 *
 */
Venta* venta_newParametros(char* idVenta, char* idCliente, char* nombreArchivo, char* cantidad, char* estado,char* zona)
{
	Venta* this = NULL;
	this = venta_new();

	if (this != NULL)
	{
		if (!venta_setIdVenta(this, atoi(idVenta)) &&
			!venta_setIdCliente(this, atoi(idCliente)) &&
			!venta_setNombreArchivo (this, nombreArchivo) &&
			!venta_setCantidad (this, atoi(cantidad)) &&
			!venta_setEstado (this, atoi(estado)) &&
			!venta_setZona(this, atoi(zona)))
		{
			return this;
		}
	}
	return NULL;
}

/////////////////////////////////////        GETTERS & SETTERS                //////////////////////////////////////

/** \brief Permite asignar un valor validado al campo Id de la entidad.
 *
 * \param int id
 * \param Venta* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int venta_setIdVenta(Venta* this,int idVenta)
{
int retorno = -1;
	if (this != NULL)
	{
		this->idVenta = idVenta;
		retorno = 0;
	}
	return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 * Hecho para recibir al ID como char, función auxiliar.
 *
 * \param char id
 * \param Venta* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int venta_getIdTxtVenta (Venta* this, char* idVenta)
{
	int retorno = -1;
	if (this != NULL  && idVenta != NULL)
	{
		retorno = 0;
		sprintf(idVenta, "%d", this->idVenta);
	}
	return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 * Hecho para recibir al ID como char, función auxiliar.
 *
 * \param int id
 * \param Venta* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int venta_getIdVenta(Venta* this,int* idVenta)
{
		int retorno = -1;
		if (this != NULL && idVenta != NULL)
		{
			retorno = 0;
			*idVenta = this->idVenta;
		}
		return retorno;
}
int venta_setIdCliente(Venta* this,int idCliente)
{
int retorno = -1;
	if (this != NULL)
	{
		this->idCliente = idCliente;
		retorno = 0;
	}
	return retorno;
}
int venta_getIdCliente(Venta* this,int* idCliente)
{
		int retorno = -1;
		if (this != NULL && idCliente != NULL)
		{
			retorno = 0;
			*idCliente = this->idCliente;
		}
		return retorno;
}
/** \brief Permite asignar un valor validado al campo nombre de la entidad.
 *
 * \param int id
 * \param Venta* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int venta_setNombreArchivo(Venta* this,char* nombreArchivo)
{
	int retorno = -1;
	if (this != NULL && nombreArchivo != NULL ) //falta validacion???
		{
			retorno = 0;
			strcpy(this->nombreArchivo, nombreArchivo);
		}
		return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 *
 * \param char nombre
 * \param Venta* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int venta_getNombreArchivo(Venta* this,char* nombreArchivo)
{
	int retorno = -1;
		if (this != NULL && nombreArchivo != NULL)
		{
			retorno = 0;
			strcpy (nombreArchivo, this->nombreArchivo);
		}
		return retorno;
}
int venta_setCantidad(Venta* this,int cantidad)
{
int retorno = -1;
	if (this != NULL)
	{
		this->cantidad = cantidad;
		retorno = 0;
	}
	return retorno;
}
int venta_getCantidad(Venta* this,int* cantidad)
{
		int retorno = -1;
		if (this != NULL && cantidad != NULL)
		{
			retorno = 0;
			*cantidad = this->cantidad;
		}
		return retorno;
}
int venta_setEstado(Venta* this,int estado)
{
int retorno = -1;
	if (this != NULL)
	{
		this->estado = estado;
		retorno = 0;
	}
	return retorno;
}
int venta_getEstado(Venta* this,int* estado)
{
		int retorno = -1;
		if (this != NULL && estado != NULL)
		{
			retorno = 0;
			*estado = this->estado;
		}
		return retorno;
}
int venta_setZona(Venta* this,int zona)
{
int retorno = -1;
	if (this != NULL )//&& (zona > 0 && zona < 4))
	{
		this->zona = zona;
		retorno = 0;
	}
	return retorno;
}
int venta_getZona(Venta* this,int* zona)
{
		int retorno = -1;
		if (this != NULL && zona != NULL)
		{
			retorno = 0;
			*zona = this->zona;
		}
		return retorno;
}
