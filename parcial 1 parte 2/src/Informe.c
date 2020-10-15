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
				cliente_printByIndex(pListClientes, QTY_CLIENTES, i);

				for (int j = 0; j < limiteAviso ; j++)
				{
					if(pAviso[j].isEmpty == FALSE &&  pListClientes[i].idCliente == pAviso[j].idCliente)
					{
						aviso_printByIndex(pAviso, QTY_AVISO, j);
					}
				}
				retorno = 0;
			}
		}
	}
	return retorno;
}
/*getCantidadAvisosTotalesPorCliente
* \brief given an index for a client, prints how many ads each client has
* \param list Aviso* | \param length int | pList Clientes | int limiteClientes | int indice
* \return [-1] if no clients have been added and [0] if there is at least one.
*/
int getCantidadAvisosTotalesPorCliente(Cliente* pListClientes, int len, Aviso* pAviso, int limiteAviso, int id)
{
	int retorno = -1;
	int contadorAvisos = 0;

	if (cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 && pListClientes != NULL &&  len > 0 && pAviso != NULL && limiteAviso > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (pListClientes[i].isEmpty == FALSE && pListClientes[i].idCliente == id)
			{
				for (int j = 0; j < limiteAviso ; j++)
				{
					if(pAviso[j].isEmpty == FALSE &&  pListClientes[i].idCliente == pAviso[j].idCliente)
					{
						contadorAvisos++;
					}
				}
			}
		}
		retorno = contadorAvisos;
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
	int a;
	int idMaximos[LIMITEINDICE];

	if (pListClientes != NULL && pAviso != NULL && limiteClientes > 0 && limiteAviso > 0)
	{
		a = 0;
		for (int i = 0; i < limiteClientes && pListClientes[i].isEmpty == FALSE; i++)
		{
			totalAvisos = (getCantidadAvisosTotalesPorCliente(pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO, i));
			if (i == 0 || totalAvisos > maxAvisos )
			{
				maxAvisos = totalAvisos;
				idMaximos[a] = i;
			}
			else if ( totalAvisos == maxAvisos )
			{
				a++;
				idMaximos[a] = i;
			}
		}
		a++;
		idMaximos[a] = -1;
		printf("CLIENTE CON MÁS AVISOS:\n");
		for (a = 0; a < LIMITEINDICE ; a++)
		{
			if (idMaximos[a] == -1)
			{
				break;
			}
			cliente_printByIndex(pListClientes, QTY_CLIENTES, (findClienteById(pListClientes, QTY_CLIENTES, idMaximos[a]))  );
		}
		printf("La cantidad de avisos son: %d \n", maxAvisos);
		retorno = 0;
	}
	return retorno;
}
int getCantidadAvisosPausadosPorCliente(Cliente* pListClientes, int len, Aviso* pAviso, int limiteAviso, int id)
{
	int retorno = -1;
	int contadorAvisos = 0;

	if (cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 && pListClientes != NULL &&  len > 0 && pAviso != NULL && limiteAviso > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (pListClientes[i].isEmpty == FALSE && pListClientes[i].idCliente == id)
			{
				for (int j = 0; j < limiteAviso ; j++)
				{
					if(pAviso[j].isEmpty == FALSE && pAviso[j].estado == FALSE &&  pListClientes[i].idCliente == pAviso[j].idCliente)
					{
						contadorAvisos++;
					}
				}
			}
		}
		retorno = contadorAvisos;
	}
	return retorno;
}
/*getClienteConMasAvisosPausados
* \brief goes through aviso array and checks for paused ads using a counter
* \param list Aviso* | \param length int | pList Clientes | int limiteClientes |
* \return [-1] if parameters are null [0] if everything ok
*/
int getClienteConMasAvisosPausados (Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso)
{
	int retorno = 0;
	int totalAvisos;
	int maxAvisos = 0;
	int a;
	int i;
	int idMaximos[LIMITEINDICE];

	if (pListClientes != NULL && pAviso != NULL && limiteClientes > 0 && limiteAviso > 0)
	{
		a = 0;
		for ( i = 0; i < limiteClientes && pListClientes[i].isEmpty == FALSE; i++)
		{
			totalAvisos = getCantidadAvisosPausadosPorCliente(pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO, i);

			if (i == 0 || totalAvisos > maxAvisos )
			{
				maxAvisos = totalAvisos;
				idMaximos[a] = i;
			}
			else if ( totalAvisos == maxAvisos )
			{
				a++;
				idMaximos[a] = i;
			}
		}
		a++;
		idMaximos[a] = -1;

		printf("CLIENTE CON MÁS AVISOS PAUSADOS:\n");
		for (a = 1; a < LIMITEINDICE ; a++)
		{
			if (idMaximos[a] == -1)
			{
				break;
			}
			cliente_printByIndex(pListClientes, QTY_CLIENTES, (findClienteById(pListClientes, QTY_CLIENTES, idMaximos[a]))  );
		}
		printf("\nLa cantidad de avisos son: %d \n", maxAvisos);
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
		for (int i = 0; i < limiteAvisos; i++)
		{
			if (pAviso[i].estado == FALSE && pAviso[i].isEmpty == FALSE)
			{
			totalAvisos++;
			}
		}
		retorno = totalAvisos;
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
int getRubroConMasAvisos(Cliente *pListClientes, int limiteClientes, Aviso *pAviso, int limiteAviso) {
	int retorno = -1;
	int j;
	int i;
	int k;
	int a = 0;
	int rubros[RUBRO];
	int rubroMaxCantidad;
	int rubroMaxFinal[10];

	if (aviso_validacionAlta(pAviso, QTY_AVISO) == 0 && pListClientes != NULL && pAviso != NULL && limiteClientes > 0 && limiteAviso > 0)
	{
		for (j = 1; j < RUBRO; j++)
		{
			k = 0;
			for (i = 0; i < limiteClientes && pAviso[i].isEmpty == FALSE; i++)
			{
				if (pAviso[i].rubro == j)
				{
					rubros[j] = k++;
				}
			}
			if (j == 1 || k > rubroMaxCantidad)
			{
				rubroMaxCantidad = k;
				rubroMaxFinal[a] = j;
			}
			else if (j != 1 && k == rubroMaxCantidad)
			{
				a++;
				rubroMaxFinal[a] = j;
			}
		}
		for (a = 0; a < 5 && rubroMaxFinal[a] > 0 && rubroMaxFinal[a] < RUBRO && (rubroMaxFinal[a] != rubroMaxFinal[a+1]) ; a++)
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
			if (utn_getNumero("\n1-Cliente con más avisos\n2-Cantidad de avisos pausados\n3-Rubro con mas avisos\n4-Cliente con más avisos activos\n5-Cliente con más avisos pausados\n6-Salir\n", "\nError\n", &bufferMenu, 2, 6, 1) == 0)
			{
				menu = bufferMenu;
				switch (menu)
				{
				case 1:
					getClienteConMasAvisos (pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO);
					break;
				case 2:
					printf("La cantidad de avisos pausados son: %d  \n", getCantidadAvisosPausados (pAviso, QTY_AVISO));
					break;
				case 3:
					getRubroConMasAvisos (pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO);
					break;
				case 4:
					getClienteConMasAvisosActivos(pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO);
					break;
				case 5:
					getClienteConMasAvisosPausados (pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO);
					break;
				case 6:
					break;
				}
			}
		}while (menu != 6);
		retorno = 0;
	}
	return retorno;
}
/*getClienteConMasAvisosActivos
* \brief calls getCantidadAvisosPorCliente, and compares to get client with max ads
* \param list Aviso* | \param length int | pList Clientes | int limiteClientes |
* \return [-1] if parameters are null [0] if everything ok
*/
int getClienteConMasAvisosActivos (Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso)
{
	int retorno = 0;
	int totalAvisos;
	int maxAvisos = 0;
	int a;
	int idMaximos[LIMITEINDICE];

	if (pListClientes != NULL && pAviso != NULL && limiteClientes > 0 && limiteAviso > 0)
	{
		a = 0;
		for (int i = 0; i < limiteClientes && pListClientes[i].isEmpty == FALSE; i++)
		{
			totalAvisos = (getCantidadAvisosActivosPorCliente(pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO, i));

			if (i == 0 || totalAvisos > maxAvisos )
			{
				maxAvisos = totalAvisos;
				idMaximos[a] = i;
			}
			else if ( totalAvisos == maxAvisos )
			{
				a++;
				idMaximos[a] = i;
			}
		}
		a++;
		idMaximos[a] = -1;

		printf("CLIENTE CON MÁS AVISOS:\n");
		for (a = 0; a < LIMITEINDICE ; a++)
		{
			if (idMaximos[a] == -1)
			{
				break;
			}
			cliente_printByIndex(pListClientes, QTY_CLIENTES, (findClienteById(pListClientes, QTY_CLIENTES, idMaximos[a]))  );
		}
		printf("La cantidad de avisos son: %d \n", maxAvisos);
		retorno = 0;
	}
	return retorno;
}
/*getCantidadAvisosActivosPorCliente //////////// CANTIDAD AVISOS ACTIVOS
* \brief given an index for a client, prints how many ads each client has
* \param list Aviso* | \param length int | pList Clientes | int limiteClientes | int indice
* \return [-1] if no clients have been added and [0] if there is at least one.
*/
int getCantidadAvisosActivosPorCliente(Cliente* pListClientes, int len, Aviso* pAviso, int limiteAviso, int id)
{
	int retorno = -1;
	int contadorAvisos = 0;

	if (cliente_validacionAlta (pListClientes, QTY_CLIENTES) == 0 && pListClientes != NULL &&  len > 0 && pAviso != NULL && limiteAviso > 0)
	{
		for (int i = 0; i < len; i++)
		{
			if (pListClientes[i].isEmpty == FALSE && pListClientes[i].idCliente == id)
			{
				for (int j = 0; j < limiteAviso ; j++)
				{
					if(pAviso[j].isEmpty == FALSE && pAviso[j].estado == TRUE &&  pListClientes[i].idCliente == pAviso[j].idCliente)
					{
						contadorAvisos++;
					}
				}
			}
		}
		retorno = contadorAvisos;
	}
	return retorno;
}

