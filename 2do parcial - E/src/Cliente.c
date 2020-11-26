/*
 * Clientes.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Informes.h"
#include "LinkedList.h"
#include "utn.h"
#include "Cliente.h"
#include "Validaciones.h"

#define TRUE 1
#define FALSE 0
#define LONG_NOMBRE 400
#define NAME 51
#define CUIT 13
static int findMaxId(LinkedList* pArrayListCliente);

//////////////////////// //////       ID         ///////////////////////////////////////////////////////////

/** \brief Encuentra cual es el max id, según la longitud de la lista, la recorre con un for hasta
 * encontrar el valor maximo y lo devuelve por return.
 *
 * \param LinkedList* pArrayListCliente
 * \return int  --------- devuelve -1 cuando hay error |  id > -1 cuando todo ok
 *
 */
static int findMaxId(LinkedList* pArrayListCliente)
{
	Cliente* pCliente;
	int len;
	int max;
	int id = -1;

	if(pArrayListCliente != NULL)
	{
		len = ll_len(pArrayListCliente);
		for(int i =0;i<len;i++)
		{
			pCliente = (Cliente*)ll_get(pArrayListCliente,i);
			cliente_getId(pCliente,&id);
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
 * \param LinkedList* pArrayListCliente
 * \return int  --------- devuelve -1 cuando hay error |  id > -1 cuando todo ok
 *
 */
int controller_generarIdNuevo(LinkedList* pArrayListCliente)
	{
	static int id = -1;
    static int flag = 1;

	    if(pArrayListCliente != NULL)
	    {
			if(flag == 1)
			{
				id = findMaxId(pArrayListCliente);
				flag++;
			}
			id++;
	    }
	    return id;
	}

/////////////////////////////////////// INFORMES | LISTADOS | AUXILIARES  ///////////////////////////////////////

/** \brief Listar TODOS clientes
 *Usa ll_isEmpty como para verificar que primero se hayan cargado los datos desde algún archivo, hace las validaciones
 *	y guarda la longitud de la lista para luego iterar sobre ella e imprimir los datos. Se agregó el índice para
 *	asistir con la corrección.
 *
 * \param pArrayListCliente LinkedList*
 * \return int -1 si hubo error | 0 si todo ok
 *
 */
int controller_ListCliente(LinkedList* pArrayListCliente)
{
	int retorno = -1;
	Cliente* bufferCliente;
	int len;

	if (pArrayListCliente != NULL && ll_len(pArrayListCliente) > -1 &&(Cliente*) ll_get(pArrayListCliente,0) != NULL)
		{
			len = ll_len(pArrayListCliente);
			for (int i = 0; i < len ; i++)
			{
				bufferCliente = (Cliente*)ll_get(pArrayListCliente,i);
				printf("==============   Indice: %d |   ID: %d | Nombre: %s   | Apellido: %s  | Cuit: %s    |         ==============  \n", i, bufferCliente->id, bufferCliente->nombre, bufferCliente->apellido, bufferCliente->cuit);
			}
			retorno = 0;
		}

	return retorno;
}
/** \brief Listar cliente por indice
 *	Hace las validaciones y llama a ll_ger para obtener los datos del cliente en ese índice.
 *
 * \param pArrayListCliente LinkedList*  | int index
 * \return int -1 si hubo error | 0 si todo ok
 *
 */
int cliente_printByIndex(LinkedList* pArrayListCliente, int index)
{
	int retorno = -1;
	Cliente* bufferCliente;

	if (pArrayListCliente != NULL && index > -1 && ll_len(pArrayListCliente) > -1 && index <= ll_len(pArrayListCliente) && (Cliente*)ll_get(pArrayListCliente,index) != NULL)
	{
		bufferCliente = (Cliente*)ll_get(pArrayListCliente,index);
		printf("==============      Nombre: %s | Apellido: %s | CUIT: %s |      ==============  \n:", bufferCliente->nombre, bufferCliente->apellido, bufferCliente->cuit);
		retorno = 0;
	}
	return retorno;
}
/** \brief Encontrar cliente por id, devolviendo el indice
 *	Itera hasta encontrar el cliente solicitado por id, devolviendo el índice dentro de la LL
 *	en el que se encuentra
 *
 * \param pArrayListCliente LinkedList*  |    int id
 * \return int -1 si hubo error | >-1 el indice
 *
 */
int findClienteById(LinkedList* pArrayListCliente, int id)
{
	int retorno = -1;
		int len;
		Cliente* bufferCliente;
		if (pArrayListCliente != NULL && id > -1 && ll_len(pArrayListCliente) > -1)
		{
			len = ll_len(pArrayListCliente);
			for (int i = 0; i < len; i++)
			{
				if (bufferCliente != NULL && (Cliente*)ll_get(pArrayListCliente,i) != NULL )
				{
					bufferCliente = (Cliente*) ll_get(pArrayListCliente,i);
					if( bufferCliente->id == id )
					{
						retorno = i;
						break;
					}
				}
			}
		}
		return retorno;
}
/** \brief Listar cliente por id, devolviendo el indice
 *	Itera hasta encontrar el cliente solicitado por id, devolviendo el índice dentro de la LL
 *	en el que se encuentra
 *
 * \param pArrayListCliente LinkedList*  |    int id
 * \return int -1 si hubo error | >-1 el indice
 *
 */
int cliente_PrintById(LinkedList* pArrayListCliente, int id)
{
	int retorno = -1;
	int len;
	Cliente* bufferCliente;
	if (pArrayListCliente != NULL && id > -1 && ll_len(pArrayListCliente) > -1)
	{
		len = ll_len(pArrayListCliente);
		for (int i = 0; i < len; i++)
		{
			if (bufferCliente != NULL && (Cliente*)ll_get(pArrayListCliente,i) != NULL )
			{
				bufferCliente = (Cliente*) ll_get(pArrayListCliente,i);
				if( bufferCliente->id == id )
				{
					printf("==============      Nombre: %s | Apellido: %s | CUIT: %s |      ==============  \n:", bufferCliente->nombre, bufferCliente->apellido, bufferCliente->cuit);
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
 * \return puntero de la entidad construida -> Cliente*
 *
 */
Cliente* cliente_new(void)
{
	return (Cliente*) malloc (sizeof(Cliente));
}
/** \brief Permite darle valores a los campos de la entidad utilizando los setters para acceder de forma segura
 *
 * \param recibe todos los campo de la entidad char | nombre, id, apellido, cuit
 * \return int  --------- devuelve puntero a la entidad Cliente |  NULL cuando hay error.
 *
 */
Cliente* cliente_newParametros(char* id,char* nombre, char* apellido,char* cuit)
{
	Cliente* this = NULL;
	this = cliente_new();

	if (this != NULL)
	{
		if (!cliente_setId(this, atoi(id)) &&
			!cliente_setNombre (this, nombre) &&
			!cliente_setApellido (this, apellido) &&
			!cliente_setCuit (this, cuit))
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
 * \param Cliente* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int cliente_setId(Cliente* this,int id)
{
int retorno = -1;
	if (this != NULL )
			//&& id>-1)
	{
		this->id = id;
		retorno = 0;
	}
	return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 * Hecho para recibir al ID como char, función auxiliar.
 *
 * \param char id
 * \param Cliente* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int cliente_getIdTxt (Cliente* this, char* id)
{
	int retorno = -1;
	if (this != NULL  && id != NULL)
	{
		retorno = 0;
		sprintf(id, "%d", this->id);
	}
	return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 * Hecho para recibir al ID como char, función auxiliar.
 *
 * \param int id
 * \param Cliente* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int cliente_getId(Cliente* this,int* id)
{
		int retorno = -1;
		if (this != NULL )//&& id != NULL)
		{
			retorno = 0;
			*id = this->id;
		}
		return retorno;
}
/** \brief Permite asignar un valor validado al campo nombre de la entidad.
 *
 * \param int id
 * \param Cliente* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int cliente_setNombre(Cliente* this,char* nombre)
{
	int retorno = -1;
	if (this != NULL && nombre != NULL && isValidName(nombre, LONG_NOMBRE ))
		{
			retorno = 0;
			strcpy(this->nombre, nombre);
		}
		return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 *
 * \param char nombre
 * \param Cliente* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int cliente_getNombre(Cliente* this,char* nombre)
{
	int retorno = -1;
		if (this != NULL && nombre != NULL)
		{
			retorno = 0;
			strcpy (nombre, this->nombre);
		}
		return retorno;
}
/** \brief Permite asignar un valor validado al campo nombre de la entidad.
 *
 * \param int id
 * \param Cliente* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int cliente_setApellido(Cliente* this,char* apellido)
{
	int retorno = -1;
	if (this != NULL && apellido != NULL && isValidName(apellido, LONG_NOMBRE) )
		{
			retorno = 0;
			strcpy(this->apellido, apellido);
		}
		return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 *
 * \param char apellido
 * \param Cliente* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int cliente_getApellido(Cliente* this,char* apellido)
{
	int retorno = -1;
		if (this != NULL && apellido != NULL)
		{
			retorno = 0;
			strcpy (apellido, this->apellido);
		}
		return retorno;
}
/** \brief Permite asignar un valor validado al campo nombre de la entidad.
 *
 * \param int id
 * \param Cliente* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int cliente_setCuit(Cliente* this,char* cuit)
{
	int retorno = -1;
	if (this != NULL && cuit != NULL && isValidCuit(cuit) == 1 )
		{
			retorno = 0;
			strcpy(this->cuit, cuit);
		}
		return retorno;
}
/** \brief Permite acceder a un campo de la entidad.
 *
 * \param char cuit
 * \param Cliente* this
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int cliente_getCuit(Cliente* this,char* cuit)
{
	int retorno = -1;
		if (this != NULL && cuit != NULL)
		{
			retorno = 0;
			strcpy (cuit, this->cuit);
		}
		return retorno;
}

