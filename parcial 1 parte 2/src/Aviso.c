/*
 * Employee.c
 *
 *  Created on: 21 sep. 2020
 *      Author: user
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Cliente.h"
#include "Aviso.h"
#include "utn.h"




/*avisoAltaForzada
* \brief: da de alta varios avisos para facilitar el debugging del programa
* \param list: array de estructura a utilizar | limite de estructura | indice | id | nombre | apellido | cuit
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int avisoAltaForzada (Aviso* pAviso, int lenAviso, int indiceAviso, int* idAviso, int rubro, char* textoAviso, int idCliente)
{
	int retorno = 0;
	Aviso bufferAviso;

	if (pAviso != NULL && lenAviso > -1)
	{
		strncpy(bufferAviso.textoAviso, textoAviso, TEXTO_AVISO);
		bufferAviso.rubro = rubro;
		bufferAviso.idCliente = idCliente;
		bufferAviso.idAviso = aviso_generarIdNuevo();
		bufferAviso.isEmpty = FALSE;
		bufferAviso.estado = TRUE;
		pAviso[indiceAviso] = bufferAviso;
		retorno = 0;
	}
	return retorno;
}
/*initAviso
* \brief To indicate that all position in the array are empty, this function put the flag (isEmpty) in TRUE in all
* position of the array
* \param list Aviso* Pointer to array of employees |  \param len int Array length
* \return int Return (-1) if Error [Invalid length or NULL pointer] - (0) if Ok
*/
int initAviso(Aviso* pAviso, int len) {
int retorno = -1;
	if (pAviso != NULL && len > 0) {
		for (int i = 0; i < len; i++)
		{
			pAviso[i].isEmpty = TRUE;
			pAviso[i].estado = FALSE;


		}
		retorno = 0;
	}
return retorno;
}
/*aviso_validacionAlta
* \brief validate if there'sat least one aviso that has been added
* \param list Aviso* | \param length int
* \return [-1] if no avisos have been added and [0] if there is at least one.
*/
int aviso_validacionAlta (Aviso* pAviso, int len)
{
int retorno = -1;
    if (pAviso != NULL && len > 0)
    {
        for (int i = 0; i < len; i++)
        {
            if(pAviso[i].isEmpty == FALSE )
            {
                retorno = 0;
                break;
            }
            else
            {
            	printf ("Error, deberá ingresar al menos un aviso para acceder a este sector. \n");
            	break;
            }
        }
    }
    return retorno;
}
/*aviso_buscarLibreRef ////// DEVUELVE PRIMER INDICE LIBRE
* \brief goes through array and finds first index position that is free and saves it to pINDEX pointer
* \param list Employee* | param len int | pointer to index
* \return [-1] if there are no free spaces or >-1 to indicate index of free space
*/
int aviso_buscarLibreRef(Aviso* pAviso, int limit, int *pIndex)
{
    int retornar = -1;
    if(pAviso != NULL && pIndex != NULL && limit>0)
    {
        for(int i = 0; i < limit; i++)
        {
            if(pAviso[i].isEmpty == TRUE)
            {
                *pIndex = i;
                retornar = 0;
                break;
            }
        }
    }
    return retornar;
}
/*aviso_printByIndex
* \brief given an index, prints out information regarding client in said index
* \param list Cliente* | length int | param index int
* \return [-1] if no clients have been added in said index [0] if there is one.
*/
int aviso_printByIndex(Aviso* pAviso, int limit, int index)
{
		int retorno = -1;
		if(pAviso != NULL && limit > 0 && index < limit)
		{
			if(pAviso[index].isEmpty == FALSE)
			{
				retorno = 0;

				printf("ID de cliente: %d - ID de aviso: %d - Rubro: %d - Texto: %s \n   \n"
				,pAviso[index].idCliente, pAviso[index].idAviso, pAviso[index].rubro, pAviso[index].textoAviso);
			}
		}
		return retorno;
}
/*aviso_generarIdNuevo
* \brief uses constant to generate a new id for each client added by user, functions as a counter
* \returns generated id
*/
int aviso_generarIdNuevo(void)
	{
	    static int id= 0;
	    id = id+1;
	    return id;
	}
/* findAvisoById
* \brief find an Aviso by Id and returns the index position in array.
* \param list Aviso* | \param len int | \param id int
* \return Return employee index position or (-1) if [Invalid length or NULL pointer received or employee not found]
*/
int findAvisoById(Aviso* pAviso, int len, int id)
{
    int retorno = -1;

    if (pAviso != NULL && len > 0)
    {
        for (int i = 0; i < len; i++)
        {
            if(pAviso[i].isEmpty == FALSE )
            {
                if(pAviso[i].idAviso == id)
                {
                   retorno = i;
                    break;
                }
            }
        }
    }
    return retorno;
}
/* aviso_alta
*brief add information regarding a client in an existing list of clients in the first empty position.
* 1 - checks that at least 1 client has been added in order to add an add &
* checks received parameters aren't NULL  & asks user for input | 2 - asks user input for client that it wants to
* add an ad for, finds that client's information & looks for first empty position for ad
* 3 - saves input in an auxiliary buffer | 4- generates new id for ad |
* 5 - gives Client list in said index same value as buffer | 6 - sets isEmpty value to false and ad state to ACTIVE/TRUE
* 7 - prints
* \param list Aviso* |  \param limiteAviso int | \param list Cliente* |  \param limiteClientes int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without free space *** also validates that index is greater than -1***]  - (0) if Ok
*/
int aviso_alta (Aviso* pAviso, int limiteAviso, Cliente* pListClientes, int limiteClientes)
{
	Aviso bufferAviso;
	int retorno = -1;
	int indice;

	if (cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 && pAviso != NULL  && pListClientes != NULL && limiteAviso >0 && limiteClientes >0)
	{
		if ((utn_getNumero("Ingresar el ID del cliente \n", "ID de Cliente incorrecto, ingrese un id válido\n", &bufferAviso.idCliente ,2,1000000,1) == 0) &&
				(findClienteById(pListClientes, QTY_CLIENTES, bufferAviso.idCliente) > -1) )
		{
			if (aviso_buscarLibreRef (pAviso, QTY_AVISO, &indice) == 0)
			{
				if (utn_getNumero("Ingresar el rubro\n", "Rubro incorrecto, ingrese un rubro válido\n", &bufferAviso.rubro,2,RUBRO,1) == 0 &&
						utn_getTexto ("Ingresar el texto para su aviso\n", "Error, ingrese un texto válido\n", bufferAviso.textoAviso,2, TEXTO_AVISO) == 0   )
				{
					pAviso[indice] = bufferAviso;
					pAviso[indice].idAviso = aviso_generarIdNuevo();
					pAviso[indice].estado = TRUE;
					pAviso[indice].isEmpty = FALSE;
					aviso_printByIndex(pAviso, QTY_AVISO, indice);         }
				else{
					printf("\n Hubo un error, favor intentar de nuevo \n");  }
			}
			else {
				printf(" \n No quedan espacios libres  \n"); }
		}
		else
		{
			printf(" \n Ingresó un ID inválido, favor intentar de nuevo\n");
		}
	}
	return retorno ;
}
/* aviso_alta
*brief: modifies pAviso.estado to active or paused
* \param list Aviso* |  \param limiteAviso int | \param list Cliente* |  \param limiteClientes int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without free space *** also validates that index is greater than -1***]  - (0) if Ok
*/
int aviso_modificarEstado (Aviso* pAviso, int lenAviso, Cliente* pListClientes, int limiteClientes)
{
	int retorno = -1;
	int bufferId;
	int bufferEstado;
	int id;
	int indice;
	int estado;
	int confirmacion;

	if ((aviso_validacionAlta (pAviso, QTY_AVISO)== 0) && pAviso != NULL && lenAviso > 0)
	{
		if (((utn_getNumero("Ingresar el ID del aviso cuyo estado desea modificar \n", "Error, ingresar un id válido\n", &bufferId,2,100000,1))== 0) && findAvisoById(pAviso, QTY_AVISO, bufferId) > -1)
		{
			id = bufferId;
			indice = findAvisoById(pAviso, QTY_AVISO, id);
			aviso_printByIndex(pAviso, QTY_AVISO, indice);
			if(utn_getNumero("¿Que modificación desea hacer?\n 0- Pausar aviso \n 1- Activar aviso\n", "Error, ingresar una opción válida\n", &bufferEstado,2,1,0) == 0 &&
					utn_getNumero("¿Está seguro que desea modificar?\n 0- Si \n 1- No\n", "Error, ingresar una opción válida\n", &confirmacion,2,1,0) == 0)
			{

				estado = bufferEstado;
				switch(confirmacion)
				{
				case 0:
					switch(estado)
					{
					case 0:
						if (pAviso[indice].estado == 1)
						{
							pAviso[indice].estado = 0;
						}
						else
						{
							printf("Error, este aviso ya está pausado\n");
						}
						break;
					case 1:
						if (pAviso[indice].estado == 0)
						{
							pAviso[indice].estado = 1;
						}
						else
						{
							printf("Error, este aviso ya está activo\n");
						}
						break;
					}
					break;
					case 1:
						break;
				}
				retorno = 0;
			}
			else
			{
				printf("Error, ingrese un ID válido. Vuelva a intentar\n");
			}
		}
	}
	return retorno;
}
/* removeClientesConAvisos
*brief: removes client and all ads adjudicated to said client
* \param list Aviso* |  \param limiteAviso int | \param list Cliente* |  \param limiteClientes int
* \return int Return (-1) if Error [Invalid length or NULL pointer or without free space *** also validates that index is greater than -1***]  - (0) if Ok
*/
int removeClienteConAvisos(Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso)
{
	int retorno = -1;
	int bufferIndex;
	int bufferId;

	if( cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 && pListClientes != NULL && pAviso != NULL && limiteClientes > 0 && limiteAviso > 0 &&
		utn_getNumero("Ingrese el ID de la cliente que desea eliminar\n", "Error, ingrese un ID válido\n", &bufferId,2,1000000000,1) == 0 && bufferId > -1 &&
		findClienteById(pListClientes, QTY_CLIENTES, bufferId) > -1 )
	{
		bufferIndex = findClienteById(pListClientes, QTY_CLIENTES, bufferId);
		if (pListClientes[bufferIndex].isEmpty == FALSE)
		{
			printf ("Este ID corresponde al siguiente cliente: \n");
			cliente_printByIndex(pListClientes, QTY_CLIENTES, bufferIndex);
			pListClientes[bufferIndex].isEmpty = TRUE;

			for (int j = 0; j < limiteAviso ; j++)
			{
				if(pAviso[j].isEmpty == FALSE  &&  pListClientes[bufferIndex].idCliente == pAviso[j].idCliente)
				{
					pAviso[j].isEmpty = TRUE;
				}
			}
			retorno = 0;
		}
		else
		{
			printf ("Error, no se encuentra cargado ninguna cliente con este ID.");
		}
	}
	return retorno;
}
int aviso_buscadorIndiceLibre (Aviso* pAviso, int len)
{
	int retorno = -1;
	if(pAviso != NULL && len > 0)
	{
		for(int i=0;i<len;i++)
		{
			if (pAviso[i].isEmpty == TRUE)
			{

				retorno = i;
				break;
			}
		}
	}
	return retorno;
}
