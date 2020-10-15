/*
 * Clientes.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "Cliente.h"

#define TRUE 1
#define FALSE 0
#define NAME 51
#define CUIT 14
#define QTY_CLIENTES 100


/*clienteAltaForzada
* \brief: da de alta varios clientes para facilitar el debugging del programa
* \param list: array de estructura a utilizar | limite de estructura | indice | id | nombre | apellido | cuit
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int clienteAltaForzada (Cliente* pListClientes, int len, int indice, int* idCliente, char* nombreCliente, char* apellidoCliente, char* cuitCliente)
{
	int retorno = 0;
	Cliente bufferClientes;

	if (pListClientes != NULL && len > -1)
	{
		strncpy(bufferClientes.nombreCliente, nombreCliente, NAME);
		strncpy(bufferClientes.apellidoCliente, apellidoCliente, NAME);
		strncpy(bufferClientes.cuitCliente, cuitCliente, CUIT);
		bufferClientes.idCliente = cliente_generarIdNuevo();
		bufferClientes.isEmpty = FALSE;
		pListClientes[indice] = bufferClientes;
		retorno = 0;
	}
	return retorno;
}
/*initCliente
* \brief To indicate that all position in the array are empty, this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Employee* Pointer to array of employees
* \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int initCliente(Cliente* pListClientes, int len) {
int retorno = -1;
	if (pListClientes != NULL && len > 0) {
		for (int i = 0; i < len; i++)
		{
			pListClientes[i].isEmpty = TRUE;
		}
		retorno = 0;
	}
return retorno;
}
/*getMainMenu
* \brief asks user for an int in order to access main menu, after a couple of tries if user still doesn't input valid number, program ends with error
* \param -- *menu ---Pointer to save input int
* \return int Return (-1) if error - (0) if Ok
*/
int getMainMenu(int* menu)
{
	int retorno = -1;
	int bufferMenu;

	if (menu != NULL && utn_getNumero("\n1-Alta de cliente\n2-Modificar datos del cliente\n3-Eliminar cliente\n4-Publicar un aviso\n5-Pausar o reanudar una publicación \n6-Imprimir clientes\n7-Informar\n8-Salir\n", "\nError\n", &bufferMenu, 2, 8, 1) == 0)
	{
		*menu = bufferMenu;
		retorno = 0;
	}
	else
	{
		exit(-1);
	}

	return retorno;
}
/*cliente_generarIdNuevo
* \brief uses constant to generate a new id for each client added by user, functions as a counter
* \returns generated id
*/
int cliente_generarIdNuevo(void)
	{
	    static int id= -1;
	    id = id+1;
	    return id;
	}
/*cliente_printByIndex
* \brief given an index, prints out information regarding client in said index
* \param list Cliente* | length int | param index int
* \return [-1] if no clients have been added in said index [0] if there is one.
*/
int cliente_printByIndex(Cliente* pListClientes, int limit, int index)
{
	int retorno = -1;
	if(pListClientes != NULL && limit > 0 && index < limit)
	{
		if(pListClientes[index].isEmpty == FALSE)
		{
			retorno = 0;

			printf("\n==========ID de cliente: %d - Nombre de cliente: %s  - Apellido de cliente: %s - Cuit: %s========== \n"
					,pListClientes[index].idCliente, pListClientes[index].nombreCliente, pListClientes[index].apellidoCliente, pListClientes[index].cuitCliente );
		}
	}
	return retorno;
}
/* AddCliente
*brief add information regarding a client in an existing list of clients in the first empty position.
* 1 - checks received parameters aren't NULL  & asks user for input | 2 - finds first empty position
* 3 - saves input in an auxiliary buffer | 4- generates new id |
* 5 - gives Client list in said index same value as buffer | 6 - sets isEmpty value to false | 7 - prints
* \param list Cliente* |  \param len int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without free space *** also validates that index is greater than -1***]  - (0) if Ok
*/
int addCliente(Cliente* pListClientes, int len)
{
	int retorno = -1;
	int indice;
	Cliente bufferList;

	if ( pListClientes != NULL && len > 0  && (cliente_buscadorIndiceLibre (pListClientes, QTY_CLIENTES)  > -1) )
	{
		indice = cliente_buscadorIndiceLibre (pListClientes, QTY_CLIENTES);
		if ( pListClientes[indice].isEmpty == TRUE &&
				( utn_getNombre("\n Nombre?","\nError",bufferList.nombreCliente,2,NAME) == 0   ) &&
				( utn_getNombre("\n Apellido?","\nError",bufferList.apellidoCliente,2,NAME) == 0   ) &&
				( utn_getCuit("Ingrese su cuit\n", "Error, ingrese un CUIT válido \n", bufferList.cuitCliente, 2, CUIT) == 0 ))
		{
			bufferList.idCliente= cliente_generarIdNuevo();
			pListClientes[indice] = bufferList;
			pListClientes[indice].isEmpty = FALSE;
			cliente_printByIndex(pListClientes, QTY_CLIENTES, indice);
			retorno = 0;
		}
	}
	return retorno;
}
/*cliente_validacionAlta
* \brief validates if at least one client that has been added
* \param list Cliente* | param length int
* \return [-1] if no employees have been added and [0] if there is at least one.
*/
int cliente_validacionAlta (Cliente* pListClientes, int len)
{
	int retorno = -1;
	if (pListClientes != NULL && len > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if(pListClientes[i].isEmpty == FALSE )
			{
				retorno = 0;
				break;
			}
			else
			{
				printf ("Error, deberá ingresar al menos un cliente para acceder a este sector. \n");
				break;
			}
		}
	}
	return retorno;
}
/* findClienteById
* \brief finds a Client by Id and returns the index position in array.
* \param list Employee* | param len int | param id int
* \return Return employee index position or (-1) if [Invalid length or NULL pointer received or employee not found]
*/
int findClienteById(Cliente *pListClientes, int len, int id)
{
	int retorno = -1;

	if (pListClientes != NULL && len > 0) {
		for (int i = 0; i < len; i++) {
			if (pListClientes[i].isEmpty == FALSE) {
				if (pListClientes[i].idCliente == id) {
					retorno = i;
					break;
				}
			}
		}
	}
	return retorno;
}
/*cliente_buscadorIndiceLibre
* \brief goes through array and finds first index position that is free and returns it
* \param list Employee* | param len int
* \return [-1] if there are no free spaces or >-1 to indicate index of free space
*/
int cliente_buscadorIndiceLibre(Cliente *pListClientes, int len) {
	int retorno = -1;
	if (pListClientes != NULL && len > 0) {
		for (int i = 0; i < len; i++) {
			if (pListClientes[i].isEmpty == TRUE) {

				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
/*cliente_modificar
* \brief function validates at least one employee has been added, asks for valid id and asks user's input to modify all the categories in Cliente struct.
* \param list Cliente* Pointer to array of clientes |  param len int Array length
* \return int Return (-1) if Error [Invalid length | NULL pointer | invalid inputs | invalid index | or no clients have been added first] - (0) if Ok
*/
int cliente_modificar (Cliente* pListClientes, int limite)
{
	int retorno = -1;
	int indiceAModificar;
	int confirmacion;
	Cliente bufferList;

	if (cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 && pListClientes != NULL && limite > 0 &&
			utn_getNumero("Ingrese el ID que desea modificar\n", "Error, ingrese una opción válida\n", &bufferList.idCliente,2,INT_MAX,0) == 0 &&
			findClienteById (pListClientes, QTY_CLIENTES, bufferList.idCliente) > -1  )
	{
		indiceAModificar = findClienteById (pListClientes, QTY_CLIENTES, bufferList.idCliente);
		cliente_printByIndex(pListClientes, QTY_CLIENTES, indiceAModificar);
		if (utn_getNumero("\n¿Está seguro que desea modificar a este cliente?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
		{
			if ((pListClientes[indiceAModificar].isEmpty == FALSE &&
				utn_getNombre("\n Nombre?","\nError",bufferList.nombreCliente,2,NAME) == 0 ) &&
				utn_getNombre("\n Apellido?","\nError",bufferList.apellidoCliente,2,NAME) == 0 &&
				utn_getCuit("Ingrese su cuit\n", "Error, ingrese un CUIT válido \n", bufferList.cuitCliente, 2, CUIT) == 0)
			{
				bufferList.isEmpty = FALSE;
				pListClientes[indiceAModificar] = bufferList;
				cliente_printByIndex(pListClientes, QTY_CLIENTES, indiceAModificar);
			}
		}
		printf("\n El cliente ha sido modificado. \n");
		retorno = 0;
	}
	return retorno;
}

