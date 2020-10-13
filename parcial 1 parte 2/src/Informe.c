/*
 * Informe.c
 *
 *  Created on: 11 oct. 2020
 *      Author: user
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "Cliente.h"
#include "Aviso.h"
#include "Informe.h"
/*printClienteInforme
* \brief prints each clients with corresponding ads
* \param list Aviso* | \param length int | pList Clientes | int limiteClientes
* \return [-1] if no clients have been added and [0] if there is at least one.
*/
int printClienteInforme(Cliente* pListClientes, int len, Aviso* pAviso, int limiteAviso)
{
	int retorno = -1;

	if (cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 && pListClientes != NULL &&  len > 0 && pAviso != NULL && limiteAviso > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (pListClientes[i].isEmpty == FALSE)
			{
				printf("\nID de cliente: %d - Nombre de cliente: %s - Apellido de cliente: %s - Cuit: %s\n"
						,pListClientes[i].idCliente, pListClientes[i].nombreCliente, pListClientes[i].apellidoCliente, pListClientes[i].cuitCliente );

				for (int j = 0; j < limiteAviso ; j++)
				{
					if(pAviso[j].isEmpty == FALSE && pAviso[j].estado == TRUE &&  pListClientes[i].idCliente == pAviso[j].idCliente)
					{
						printf("ID de cliente: %d - ID de aviso: %d - Rubro: %d - Texto: %s \n"
								,pAviso[j].idCliente, pAviso[j].idAviso, pAviso[j].rubro, pAviso[j].textoAviso);
					}
				}
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*getCantidadAvisosPorCliente
* \brief given an index for a client, prints how many ads each client has
* \param list Aviso* | \param length int | pList Clientes | int limiteClientes | int indice
* \return [-1] if no clients have been added and [0] if there is at least one.
*/
int getCantidadAvisosPorCliente(Cliente* pListClientes, int len, Aviso* pAviso, int indice, int limiteAviso)
{
	int retorno = -1;
	int cantidadAvisos = 0;

	if (cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 && pListClientes != NULL &&  len > 0 && pAviso != NULL && limiteAviso > 0 && pListClientes[indice].isEmpty == FALSE)
	{
		for (int j = 0; j < limiteAviso ; j++)
		{
			if(pAviso[j].isEmpty == FALSE && pAviso[j].estado == TRUE &&  pListClientes[indice].idCliente == pAviso[j].idCliente)
			{
				cantidadAvisos++;
			}
		}
		retorno = cantidadAvisos;
	}
	return retorno;
}
/*getClienteConMasAvisos
* \brief calls getCantidadAvisosPorCliente, and compares to get client with max ads
* \param list Aviso* | \param length int | pList Clientes | int limiteClientes |
* \return [-1] if parameters are null [0] if everything ok
*/
int getClienteConMasAvisos (Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso)
{
	int retorno = 0;
	int totalAvisos;
	int maxAvisos = 0;
	int indice;
	int flagAvisos = 0;

	if (pListClientes != NULL && pAviso != NULL && limiteClientes > 0 && limiteAviso > 0)
	{
		for (int i = 0; i < limiteClientes && pListClientes[i].isEmpty == FALSE; i++)
		{
			totalAvisos = (getCantidadAvisosPorCliente(pListClientes, QTY_CLIENTES, pAviso, i, QTY_AVISO));
			if (flagAvisos == 0 || totalAvisos > maxAvisos )
			{
				flagAvisos = 1;
				maxAvisos = totalAvisos;
				indice = i;

			}
		}
		cliente_printByIndex(pListClientes, QTY_CLIENTES, indice);
		printf("Este cliente tiene %d avisos \n", maxAvisos);
		retorno = 0;
	}
	return retorno;
}
/*getCantidadAvisosPausados
* \brief goes through aviso array and checks for paused ads using a counter
* \param list Aviso* | \param length int | pList Clientes | int limiteClientes |
* \return [-1] if parameters are null [0] if everything ok
*/
int getCantidadAvisosPausados (Aviso* pAviso, int limiteAvisos)
{
	int retorno = -1;
	int totalAvisos= 0;

	if (aviso_validacionAlta (pAviso, QTY_AVISO)== 0 &&  pAviso != NULL  && limiteAvisos > 0)
	{
		for (int i = 0; i < limiteAvisos && pAviso[i].estado == FALSE; i++)
		{
			totalAvisos++;
		}
		printf("La cantidad de avisos pausados son: %d  \n", totalAvisos);
		retorno = 0;
	}
	return retorno;
}
/*getRubroConMasAvisos
* \brief - 1 - makes an array of rubros/categories, with limit set to qty of rubros allowed in original struct
* 		 - 2 - with for loop, goes through ads to check if rubro in structureArray is the same to rubro in array, using a counter
* 		 - 3 - rubroMaxFinal is an array of max rubros in case there are more than 1 rubro with the same max number
* \param list Aviso* | \param length int | pList Clientes | int limiteClientes |
* \return [-1] if parameters are null | [0] if everything ok
*/
int getRubroConMasAvisos (Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso)
{
	int retorno = -1;
	int j = 0;
	int i = 0;
	int flag = 0;
	int k = 0;
	int a = 0;
	int rubros[RUBRO];
	int rubroMaxCantidad = 0;
	int rubroMaxFinal[10];

	if (aviso_validacionAlta (pAviso, QTY_AVISO)== 0 && pListClientes != NULL && pAviso != NULL && limiteClientes > 0 && limiteAviso > 0)
	{
		for (j = 1; j < RUBRO; j++)
		{
			k = 0;
			for (i = 0; i < limiteClientes && pAviso[i].isEmpty == FALSE; i++)
			{
				if (pAviso[i].rubro == j)
				{
					rubros[j]= k++;
				}
			}
			if (flag == 0 || k > rubroMaxCantidad)
			{
				flag = 1;
				rubroMaxCantidad = k;
				rubroMaxFinal[a] = j;
				retorno = 0; }
			else if (flag == 1 && k == rubroMaxCantidad)
			{
				a++;
				rubroMaxFinal[a] = j;}
		}
		for (a = 0; a < 5 && rubroMaxFinal[a] > 0 && rubroMaxFinal[a] < RUBRO ; a++)
		{
			printf("===========EL RUBRO CON MÁS CANTIDAD ES: %d===================\n", rubroMaxFinal[a]);
		}

		retorno = 0;
	}
	return retorno;
}
/*getSubMenu
* \brief validates at least one ad and one client has been added in order to get proper inform, using a switch as a menu
* \param list Aviso* | \param length int | pList Clientes | int limiteClientes |
* \return [-1] if parameters are NULL or if user inputs menu option wrong past limit [0] if everything ok
*/
int getSubMenu(Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso)
{
	int retorno = -1;
	int bufferMenu;
	int menu;

	if (cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 && aviso_validacionAlta (pAviso, QTY_AVISO)== 0 )
	{
		do{
			if (utn_getNumero("\n1-Cliente con más avisos\n2-Cantidad de avisos pausados\n3-Rubro con mas avisos\n4-Salir\n", "\nError\n", &bufferMenu, 2, 4, 1) == 0)
			{
				menu = bufferMenu;
				switch (menu)
				{
				case 1:
					getClienteConMasAvisos (pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO);
					break;
				case 2:
					getCantidadAvisosPausados (pAviso, QTY_AVISO);
					break;
				case 3:
					getRubroConMasAvisos (pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO);
					break;
				case 4:
					break;
				}
			}
		}while (menu != 4);
		retorno = 0;
	}
	return retorno;
}
