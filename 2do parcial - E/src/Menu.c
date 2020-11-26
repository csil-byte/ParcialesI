/*
 * Menu.c
 *
 *  Created on: 26 nov. 2020
 *      Author: user
 */

#include "Menu.h"
#include "utn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>



/** \brief Genera opciones de menu y guarda la elegida en la variable pasada por referencia
 *
 * \param int* menu
 * \return int  --------- devuelve -1 cuando hay error |  0 cuando está todo ok
 *
 */
int getMainMenuCarga(int* menu)
{
	int retorno = -1;
	int bufferMenu;
	if (menu != NULL && utn_getNumero("\n1- Agregar cliente\n2- Vender afiches"
			"-\n3- Modificar venta\n4- Cobrar venta\n5- Informe de cobros"
			"\n6- Informe de deudas\n7- Generar estadísticas\n8- Salir\n", "\nError\n", &bufferMenu, 2, 8, 1) == 0)
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
int getMenuInformes(int* menu)
{
	int retorno = -1;
	int bufferMenu;
		if (menu != NULL && utn_getNumero("\n1- Cliente al que se le vendió mas afiches"
				"\n2- Cliente al que se le vendió menos afiches"
				"-\n3- Venta con mas afiches vendidos\n4- Salir\n", "\nError\n", &bufferMenu, 2, 4, 1) == 0)
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
