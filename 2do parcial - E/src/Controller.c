/*
 * Controller.c
 *
 *  Created on: 26 nov. 2020
 *      Author: user
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#define COBRADO 0
#define A_COBRAR 1
#include "LinkedList.h"
#include "Controller.h"
#include "Validaciones.h"
#include "Ventas.h"
#include "Cliente.h"
#include "utn.h"
#define LONG_NOMBRE 400


/** \brief Buscar cliente por id de venta e imprime
 *	Itera hasta encontrar el venta solicitado por id, devolviendo el índice dentro de la LL
 *	en el que se encuentra
 *
 * \param pArrayListVenta LinkedList*  |    int id
 * \return int -1 si hubo error | >-1 el indice
 *
 */
int printClient_bySaleId(LinkedList* pArrayListCliente, LinkedList* pArrayVentas, int idVenta)
{
	int retorno = -1;
	int len;
	Cliente* bufferCliente;
	Venta* bufferVenta;
	int indice;

	if (pArrayListCliente != NULL && idVenta > -1 && ll_len(pArrayListCliente) > -1)
	{
		indice = findVentaById(pArrayVentas, idVenta);
		len = ll_len(pArrayListCliente);
		if ((Venta*)ll_get(pArrayVentas,indice) != NULL )
			{
				bufferVenta = (Venta*)ll_get(pArrayVentas,indice);
				for (int i = 0; i<len ; i++){
					bufferCliente = (Cliente*)ll_get(pArrayListCliente,i);
				if( bufferVenta->idCliente == bufferCliente->id )
				{
					printf("==============      Nombre: %s | Apellido: %s | CUIT: %s |      ==============  \n:", bufferCliente->nombre, bufferCliente->apellido, bufferCliente->cuit);
					retorno = 0;
					break;
				}}
			}
	}
	return retorno;
}

///////////////////////////////// CLIENTE      ALTA | MODIFICACIÓN | BAJA      //////////////////////////////////////////////////////

/** \brief Alta de clientes
 *	Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide al usuario
 *	los datos que desea agregar, se genera un id, y se llama al newParametros para guardar en un buffer.
 * 	Con el ll_add se agregan los datos recibidos del buffer en pArrayListCliente.
 *
 * \param path char*
 * \param  LinkedList*
 * \return int -1 si hubo error en la carga o no se cargó el archivo previamente.
 *
 */
int controller_addCliente(LinkedList* pArrayListCliente)
{
	int retorno = -1;
	char id[LONG_NOMBRE] ;
	char nombre[LONG_NOMBRE];
	char apellido[LONG_NOMBRE];
	char cuit[LONG_NOMBRE];

	Cliente* bufferCliente;

	if (ll_isEmpty(pArrayListCliente)==0)
	{
		if( !utn_getNombre("Ingresar nombre\n", "Error, ingresar un nombre válido\n", nombre,2, LONG_NOMBRE) &&
				!utn_getNombre("Ingresar apellido\n", "Error, ingresar un nombre válido\n", apellido,2, LONG_NOMBRE) &&
				!utn_getCuit("Ingresar cuit\n", "Error, ingresar un nombre válido\n", cuit,2, LONG_NOMBRE) )
		{
			if (isCuitRepeated(pArrayListCliente, cuit) == 0)
			{
					sprintf(id, "%d", controller_generarIdNuevo(pArrayListCliente));
					bufferCliente = cliente_newParametros(id, nombre, apellido, cuit);
					ll_add(pArrayListCliente, bufferCliente);
					printf("Cliente agregado con éxito\n");
					retorno = 0;
			}
			else
			{
				printf("\nError. Este CUIT ya está ingresado en nuestro sistema\n");
			}
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más clientes. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Hardcodeo - auxiliar interno para armado de programa
 *
 */
int controller_hardCode(LinkedList* pArrayListCliente, char* name, char* apellido, char* cuit )
{
	int output = -1;
	char id[LONG_NOMBRE] ;
	Cliente* bufferCliente;
	{
		sprintf(id, "%d", controller_generarIdNuevo(pArrayListCliente));
		bufferCliente = cliente_newParametros(id, name, apellido, cuit);
		ll_add(pArrayListCliente, bufferCliente);
	}
    return output;
}
/** \brief Modificar datos de cliente
 *Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide el ID a modificar.
 *Se verifica que sea válido y se imprime para luego pedir la confirmación del usuario.
 *En caso de confirmación, se modificaran todos los campos del cliente, se imprimirá el cliente modificado
 *	y luego se imprimiran todos los clientes para facilitar revisión.
 *
 * \param pArrayListCliente LinkedList*
 * \return int -1 si hay error | 0 si todo ok
 */
int controller_editCliente(LinkedList* pArrayListCliente)
{
	int retorno = -1;
	int bufferId;
	int indiceAModificar;
	int confirmacion;
	Cliente* bufferList;

	char nombre[LONG_NOMBRE];
	char apellido[LONG_NOMBRE];

	if (ll_isEmpty(pArrayListCliente)==0)
	{
		if 	(	pArrayListCliente != NULL &&
				utn_getNumero("Ingrese el ID que desea modificar\n", "Error, ingrese una opción válida\n", &bufferId,2,999999,0) == 0
				&& findClienteById(pArrayListCliente, bufferId) > -1  )
			{
				indiceAModificar = findClienteById(pArrayListCliente, bufferId);
				cliente_printByIndex(pArrayListCliente, indiceAModificar);
			if (utn_getNumero("\n¿Está seguro que desea modificar a este cliente?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
			{
				switch (confirmacion)
				{
				case (0):
				if ((Cliente*)ll_get(pArrayListCliente, indiceAModificar) != NULL &&
					!utn_getNombre("Ingresar nombre\n", "Error, ingresar un nombre válido\n", nombre,2, LONG_NOMBRE) &&
					!utn_getNombre("Ingresar apellido\n", "Error, ingresar un nombre válido\n", apellido,2, LONG_NOMBRE) )
						{
							bufferList = (Cliente*)ll_get(pArrayListCliente, indiceAModificar);
							cliente_setNombre(bufferList, nombre);
							cliente_setApellido(bufferList, apellido);
							printf("\n El cliente ha sido modificado. \n");
							cliente_printByIndex(pArrayListCliente, indiceAModificar);
							controller_ListCliente(pArrayListCliente);
							retorno = 0;
						}
				break;
				case (1):
						printf("\n No se ha modificado al cliente. \n");
					retorno = 0;
				break;
				}
			}
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más clientes. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Baja de cliente auxiliar - libera memoria
 *
 * \param pArrayListCliente LinkedList*
 *
 */
void cliente_delete(Cliente* this)
{
	free(this);
}
/** \brief Baja de cliente
 *Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide el ID a modificar.
 *Se verifica que sea válido y se imprime para luego pedir la confirmación del usuario.
 *En caso de confirmación, se eliminará al cliente usando ll_pop para no perder el acceso a la dirección del cliente en memoria.
 *
 *
 *Se eliminaran SÓLO si todos las ventas están en estado 0. Se eliminaran todas las ventas asociadas.
 * \param pArrayListCliente LinkedList*
 * \return int -1 si no logró eliminarse | 0 si se eliminó cliente o si el usuario decidió no hacerlo
 *
 */
int controller_removeCliente(LinkedList* pArrayListCliente, LinkedList* pVentas)
{
	int retorno = -1;
	int bufferId;
	int indiceAModificar;
	int confirmacion;
	Cliente* bufferList;

	if (ll_isEmpty(pArrayListCliente)==0)
	{
		if (  	pArrayListCliente != NULL && pVentas != NULL &&
				utn_getNumero("Ingrese el ID que desea eliminar\n", "Error, ingrese un número válido\n", &bufferId,2,INT_MAX,0) == 0 &&
				findClienteById(pArrayListCliente, bufferId) > -1                  )
		{
			indiceAModificar = findClienteById(pArrayListCliente, bufferId);
			cliente_printByIndex(pArrayListCliente, indiceAModificar);
			if (utn_getNumero("\n¿Está seguro que desea eliminar a este cliente?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
			{
				switch(confirmacion)
				{
				case (0):
						if (removeAllVentas_byClientId(pArrayListCliente, pVentas, bufferId) == 0)
						{
							bufferList = ll_pop(pArrayListCliente,indiceAModificar);
							cliente_delete(bufferList);
								printf("Cliente eliminado con éxito\n");
						retorno = 0;
						}
				break;
				case (1):
						printf("El cliente no se ha eliminado\n");
					retorno = 0;
				break;
				}
			}
		}
		else if (findClienteById(pArrayListCliente, bufferId) < 0 )
		{
			printf("Error, no existe ningún cliente bajo este ID. Favor volver a intentar\n");
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más clientes. Favor volver a intentar\n");
	}
	return retorno;
}

/////////////////////////////////       ALTA | MODIFICACIÓN | BAJA      //////////////////////////////////////////////////////

/** \brief Alta de ventas
 *	Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide al usuario
 *	los datos que desea agregar, se genera un id, y se llama al newParametros para guardar en un buffer.
 * 	Con el ll_add se agregan los datos recibidos del buffer en pArrayListVenta.
 *
 * \param path char*
 * \param  LinkedList*
 * \return int -1 si hubo error en la carga o no se cargó el archivo previamente.
 *
 */
int controller_addVenta(LinkedList* pArrayListVenta,LinkedList* pArrayListCliente)
{	int retorno = -1;
	int bufferZona;
	char idVenta[LONG_NOMBRE] ;
	char idCliente[LONG_NOMBRE];
	char nombreArchivo[LONG_NOMBRE];
	char cantidad[LONG_NOMBRE];
	char estado[LONG_NOMBRE];
	char zona[LONG_NOMBRE];
	int indice;

	Venta* bufferVenta;

	if (ll_isEmpty(pArrayListCliente)==0)
	{
		if( !utn_getCadenaNumerica("Ingresar ID del cliente\n","Error, ingresar un ID válido\n",idCliente,0,INT_MAX,2)
				&& findClienteById(pArrayListCliente, atoi(idCliente)) > -1 )
		{

			indice = findClienteById(pArrayListCliente, atoi(idCliente));
			printf("indice??? %d, \n", indice);
			if( !utn_getNombre("Ingresar nombre del archivo\n", "Error, ingresar un nombre válido\n", nombreArchivo,2, LONG_NOMBRE) &&
				!utn_getCadenaNumerica("Ingresar cantidad\n","Error, ingresar una cantidad válida\n",cantidad,1,INT_MAX,2) &&
				!utn_getNumero("Ingresar zona\n1- CABA\n2- ZONA SUR\n3- ZONA OESTE\n","Error, ingresar una zona válida\n",&bufferZona,2,3,1)      )
			{
				sprintf(idVenta, "%d", venta_generarIdNuevo(pArrayListVenta));
				sprintf(estado, "%d", A_COBRAR);
				sprintf(zona, "%d", bufferZona);
				bufferVenta = venta_newParametros(idVenta, idCliente, nombreArchivo, cantidad, estado, zona);
				ll_add(pArrayListVenta, bufferVenta);
				printf("Venta agregada con éxito\n");
				retorno = 0;
			}
		}
		else
		{
			printf("Este cliente no se encuentra en el sistema. Favor ingresar un id válido\n");
		}
	}
	else
	{
		printf("Error, deberá ingresar al menos 1 cliente para adjudicar una venta\n");
	}
	return retorno;
}
/** \brief Hardcodeo - auxiliar interno para armado de programa
 *
 */
int venta_hardCode(LinkedList* pArrayListVenta, char* idCliente, char* nombreArchivo, char* cantidad, char* estado, char* zona )
{
	int output = -1;
	char idVenta[LONG_NOMBRE] ;
	char bufferEstado[LONG_NOMBRE] ;
	Venta* bufferVenta;
	{
		sprintf(idVenta, "%d", venta_generarIdNuevo(pArrayListVenta));
		sprintf(bufferEstado, "%d", atoi(estado));
		bufferVenta = venta_newParametros(idVenta, idCliente, nombreArchivo, cantidad, bufferEstado, zona);
		ll_add(pArrayListVenta, bufferVenta);
	}
    return output;
}
/** \brief Modificar datos de venta - getDatos
 *Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide el ID a modificar.
 *Se verifica que sea válido y se imprime para luego pedir la confirmación del usuario.
 *En caso de confirmación, se modificaran todos los campos del venta, se imprimirá el venta modificado
 *	y luego se imprimiran todos los ventas para facilitar revisión.
 *
 * \param pArrayListVenta LinkedList*
 * \return int -1 si hay error | 0 si todo ok
 */
int controller_editVenta(LinkedList* pArrayListVenta, LinkedList* pArrayClientes)
{
	int retorno = -1;
	int bufferId;
	int indiceAModificar;
	int confirmacion;
	Venta* bufferList;

	if (ll_isEmpty(pArrayListVenta)==0 && ll_isEmpty(pArrayClientes)==0)
	{
		if 	(	pArrayListVenta != NULL &&
				utn_getNumero("Ingrese el ID de la venta que desea modificar\n", "Error, ingrese una opción válida\n", &bufferId,2,999999,0) == 0
				&& findVentaById(pArrayListVenta, bufferId) > -1  )
			{
				indiceAModificar = findVentaById(pArrayListVenta, bufferId);
				bufferList = (Venta*)ll_get(pArrayListVenta, indiceAModificar);
				venta_printByIndex(pArrayListVenta, indiceAModificar);
				if (bufferList->estado == 1)
				{
					printClient_bySaleId(pArrayClientes, pArrayListVenta, bufferId);
					if (utn_getNumero("\n¿Está seguro que desea modificar a este venta?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
					{
						switch (confirmacion)
						{
						case (0):
							menuModificacion (pArrayListVenta, &indiceAModificar);
							retorno = 0;
						break;
						case (1):
							printf("\n No se ha modificado al venta. \n");
							retorno = 0;
						break;
						}
					}
				}
				else{ printf("Error. Sólo se podrán modificar ventas que aún no estén cobradas.\n"); }
		}
		else{printf("Error, este ID no corresponde a una venta en nuestro sistema. Favor volver a intentar\n");}
	}
	else{ printf("Error, deberá cargar un archivo antes de agregar más ventas. Favor volver a intentar\n");}
	return retorno;
}
/** \brief Modificar datos de venta - modificar por cateogoría
 *
 * \param pArrayListVenta LinkedList*
 * \return int -1 si hay error | 0 si todo ok
 */
int menuModificacion (LinkedList* pArrayListVenta, int* indiceModificar)
{
	int retorno = -1;
	int menu;
	Venta* bufferList;
	int cantidad;
	int zona;
	char nombreArchivo[LONG_NOMBRE];

	do{
		if (!utn_getNumero("\nIngresar el campo que desea modificar\n1- Archivo\n2- Cantidad\n3- Zona\n4- Salir\n", "Error, ingresar una opción válida\n", &menu,2,4,1) &&
			(Venta*)ll_get(pArrayListVenta, *indiceModificar) != NULL )
		{
			bufferList = (Venta*)ll_get(pArrayListVenta, *indiceModificar);
			switch (menu)
			{
			case 1: // ARCHIVO
				if (!utn_getNombre("Ingresar nombre del archivo\n", "Error, ingresar un nombre válido\n", nombreArchivo,2, LONG_NOMBRE) )
				{
					venta_setNombreArchivo(bufferList, nombreArchivo);
					printf("\n Campo modificado con éxito. \n");
					venta_printByIndex(pArrayListVenta, *indiceModificar);
				}
				break;
			case 2: //CANTIDAD
				if (!utn_getNumero("Ingresar cantidad\n","Error, ingresar una cantidad válida\n", &cantidad,1,INT_MAX,2) )
					{
					venta_setCantidad(bufferList, cantidad);
					printf("\n Campo modificado con éxito. \n");
					venta_printByIndex(pArrayListVenta, *indiceModificar);
					}
				break;
			case 3: // ZONA
				if (!utn_getNumero("Ingresar zona\n","Error, ingresar una cantidad válida\n", &zona,1,3,2) )
					{
						venta_setZona(bufferList, zona);
						printf("\n Campo modificado con éxito. \n");
						venta_printByIndex(pArrayListVenta, *indiceModificar);
					}
				break;
			case 4: // SALIR
				break;
			}
		}
	}while (menu != 4);

	return retorno;
}
/** \brief Modificar estado de venta
 *Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide el ID a modificar.
 *Se verifica que sea válido y se imprime para luego pedir la confirmación del usuario.
 *En caso de confirmación, se modificaran todos los campos del venta, se imprimirá el venta modificado
 *	y luego se imprimiran todos los ventas para facilitar revisión.
 *
 * \param pArrayListVenta LinkedList*
 * \return int -1 si hay error | 0 si todo ok
 */
int ventas_cobranza (LinkedList* pArrayListVenta, LinkedList* pCliente)
{
	int retorno = -1;
	int bufferId;
	int indiceAModificar;
	int confirmacion;
	Venta* bufferList;

	if (ll_isEmpty(pArrayListVenta)==0 && ll_isEmpty(pCliente)==0)
	{
		if (  	pArrayListVenta != NULL &&
				utn_getNumero("Ingrese el ID de la venta a cobrar\n", "Error, ingrese un número válido\n", &bufferId,2,INT_MAX,0) == 0 &&
				findVentaById(pArrayListVenta, bufferId) > -1                  )
		{
			indiceAModificar = findVentaById(pArrayListVenta, bufferId);
			venta_printByIndex(pArrayListVenta, indiceAModificar);
			printClient_bySaleId(pCliente, pArrayListVenta, bufferId);
			if (utn_getNumero("\n¿Está seguro que desea cobrar esta venta?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
			{
				switch(confirmacion)
				{
				case (0):
						if ((Venta*)ll_get(pArrayListVenta, indiceAModificar) != NULL)
						{
							bufferList = (Venta*)ll_get(pArrayListVenta, indiceAModificar);
							venta_setEstado(bufferList,0);
							printf("Venta cobrada con éxito\n");
							venta_printByIndex(pArrayListVenta, indiceAModificar);
							retorno = 0;
						}
				break;
				case (1):
						printf("El estado no se ha modificado\n");
						retorno = 0;
				break;
				}
			}

		}
	}
	else
		{
			printf("Error, deberá cargar un archivo antes de agregar más ventas. Favor volver a intentar\n");
		}
	return retorno;
}

/** \brief Baja de venta auxiliar - libera memoria
 *
 * \param pArrayListVenta LinkedList*
 *
 */
void venta_delete(Venta* this)
{
	free(this);
}
/** \brief Baja de 1 de venta
 *Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide el ID a modificar.
 *Se verifica que sea válido y se imprime para luego pedir la confirmación del usuario.
 *En caso de confirmación, se eliminará al venta usando ll_pop para no perder el acceso a la dirección del venta en memoria.
 *
 * \param pArrayListVenta LinkedList*
 * \return int -1 si no logró eliminarse | 0 si se eliminó venta o si el usuario decidió no hacerlo
 *
 */
int controller_removeVenta(LinkedList* pArrayListVenta)
{
	int retorno = -1;
	int bufferId;
	int indiceAModificar;
	int confirmacion;
	Venta* bufferList;

	if (ll_isEmpty(pArrayListVenta)==0)
	{
		if (  	pArrayListVenta != NULL &&
				utn_getNumero("Ingrese el ID que desea eliminar\n", "Error, ingrese un número válido\n", &bufferId,2,INT_MAX,0) == 0 &&
				findVentaById(pArrayListVenta, bufferId) > -1                  )
		{
			indiceAModificar = findVentaById(pArrayListVenta, bufferId);
			venta_printByIndex(pArrayListVenta, indiceAModificar);
			if (utn_getNumero("\n¿Está seguro que desea eliminar a este venta?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
			{
				switch(confirmacion)
				{
				case (0):
						bufferList = (Venta*)ll_get(pArrayListVenta, indiceAModificar);
						//bufferList =
						ll_pop(pArrayListVenta,indiceAModificar);
						venta_delete(bufferList);
						venta_printByIndex(pArrayListVenta, indiceAModificar);
						printf("Venta eliminado con éxito\n");
						retorno = 0;
				break;
				case (1):
						printf("El venta no se ha eliminado\n");
					retorno = 0;
				break;
				}
			}
		}
		else if (findVentaById(pArrayListVenta, bufferId) < 0 )
		{
			printf("Error, no existe ningún venta bajo este ID. Favor volver a intentar\n");
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más ventas. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Baja de todas las ventas asociada a un cliente
 *Usa ll_isEmpty como flag para verificar que primero se hayan cargado los datos desde archivo, se pide el ID a modificar.
 *Se verifica que sea válido y se imprime para luego pedir la confirmación del usuario.
 *En caso de confirmación, se eliminará al venta usando ll_pop para no perder el acceso a la dirección del venta en memoria.
 *
 * \param pArrayListVenta LinkedList*
 * \return int -1 si no logró eliminarse | 0 si se eliminó venta o si el usuario decidió no hacerlo
 *
 */
int removeAllVentas_byClientId(LinkedList* pArrayListCliente, LinkedList* pArrayVentas, int idCliente)
{
	int retorno = -1;
	int len;
	Venta* bufferVenta;

	if (pArrayListCliente != NULL && pArrayVentas != NULL && idCliente > -1 && ll_len(pArrayVentas) > -1)
	{
		len = ll_len(pArrayVentas);
		if (cliente_areAllSalesPaid(pArrayListCliente, pArrayVentas, idCliente) == 0)
		{
			for (int i = 1; i<len-1 ; i++)
			{
				bufferVenta = (Venta*)ll_get(pArrayVentas,i);
				len = ll_len(pArrayVentas);
				if( bufferVenta->idCliente == idCliente )
				{
					bufferVenta = ll_pop(pArrayVentas,i);
					venta_delete(bufferVenta);
					retorno = 0;
				}
			}
		}
		else
		{
			printf("Error. Este cliente tiene pagos adeudados.\n");
		}
	}

	return retorno;
}

////////////// AUX
/** \brief Revisa si todas las ventas de un cliente están cobradas
 *
 *En caso de confirmación, se iterará y en caso de encontrar 1 sóla venta en estado 1, hace break y devuelve -1
 * \param pArrayListVenta LinkedList*
 * \return int -1 si no hay venta sin cobrar | 0 si todo ok
 *
 */
int cliente_areAllSalesPaid(LinkedList* pArrayListCliente, LinkedList* pArrayVentas, int idCliente)
{
int retorno = -1;
int len;
Venta* bufferVenta;

	if (pArrayListCliente != NULL && pArrayVentas != NULL && idCliente > -1 && ll_len(pArrayVentas) > -1)
	{
		len = ll_len(pArrayVentas);
		for (int i = 1; i<len-1 ; i++)
		{
			bufferVenta = (Venta*)ll_get(pArrayVentas,i);
			if( bufferVenta->idCliente == idCliente && bufferVenta->estado == 0 )
			{
				retorno = 0;
			}
			else if (bufferVenta->idCliente == idCliente && bufferVenta->estado == 1)
			{
				break;
			}
		}
	}
	return retorno;
}


