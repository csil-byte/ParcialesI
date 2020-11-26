/*
 * Validaciones.c
 *
 *  Created on: 26 nov. 2020
 *      Author: user
 */

#include "Validaciones.h"
//#include "LinkedList.h"
#include "Cliente.h"
//#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define CUIT 13


/** esUnNombreValido
 * brief
 * 	Verifica una cadena recibida como parametro para determinir si es un nombre valido
 * \param char* cadena, Cadena a analizar
 * \param int limite, indica la cantidad de letras maxima de la cadena
 * \return (0) Indicar que no es un nombre valido / (1) Indica que que es un nombre valido
 */
int isValidName(char* cadena,int limite)
{
	int respuesta = 1; // TODO OK

	for(int i=0; i<=limite && cadena[i] != '\0';i++)
	{
		//esta mal <----- A - Z -----> Esta mal
		if(	(cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			(cadena[i] == '.' || cadena[i] != ' ') && (cadena[i]!='-' || cadena[0]=='-' ))
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}

int isCuitRepeated(LinkedList* pClientes, char* cuit)
{
	int retornar=-1;
	Cliente* bufferClient;
	char bufferCuit[CUIT];
	if(pClientes!=NULL && cuit!=NULL)
	{
		retornar=0;
		for(int i=0;i<ll_len(pClientes);i++)
		{
			bufferClient = ll_get(pClientes, i);
			if(bufferClient!=NULL && !cliente_getCuit(bufferClient, bufferCuit))
			{
				if(!strncmp(bufferCuit, cuit,CUIT))
				{
					retornar=1;
				}
			}
		}
	}
	return retornar;
}
int isValidCuit(char string[])
{
	int retorno;
	int guiones=0;
	if(string != NULL && strlen(string) > 0 && string[2] == '-' && string[11] == '-' && string[12] != '\0')
	{
		retorno = 1;
		for(int i = 0;string[i] != '\0'; i++)
		{
			if(string[i] == '-')
			{
				guiones++;
			}
			if(guiones>2 || ((string[i] < '0' || string[i] > '9') && string[i] != '-'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
