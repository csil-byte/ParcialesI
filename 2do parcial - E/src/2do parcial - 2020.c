#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "LinkedList.h"
#include "Cliente.h"
#include "Ventas.h"
#include "Informes.h"
#include "Archivos.h"
#include "Controller.h"
#include "Menu.h"
#define MAX 1
#define MIN 0

int main(void) {

	setbuf(stdout, NULL);
	LinkedList* listaClientes = ll_newLinkedList();
	LinkedList* listaVentas = ll_newLinkedList();
	LinkedList* ventas_cobradas =ll_newLinkedList();
	int informes;
	int menu;

	if( cliente_controllerLoadFromText("clientes.csv" , listaClientes) == 0 &&
		ventas_controllerLoadFromText("ventas.csv" , listaVentas) == 0 )
	{
	ventas_cobradosPorCliente(listaVentas, listaClientes, &ventas_cobradas, 0);
	do {
		getMainMenuCarga(&menu);
		switch (menu) {
		case 1:
			if (!controller_addCliente(listaClientes))
			{
				controller_ListCliente(listaClientes);
				cliente_saveAsText("clientes.csv" , listaClientes);
			}
		break;
		case 2:
			if (controller_addVenta(listaVentas,listaClientes) == 0)
			{
				ventas_saveAsText("ventas.csv" , listaVentas);
				controller_ListVenta(listaVentas);
			}
		break;
		case 3:
			if (ventas_listSinCobrar(listaVentas) == 0 && controller_editVenta(listaVentas, listaClientes) == 0)
			{  ventas_saveAsText("ventas.csv" , listaVentas);}
		break;
		case 4:
			if (ventas_listSinCobrar(listaVentas) == 0 && ventas_cobranza (listaVentas, listaClientes) == 0)
			{ ventas_saveAsText("ventas.csv" , listaVentas);}
		break;
		case 5:
			if (ventasEstado_saveAsText("cobradas.csv" , listaVentas, listaClientes, 0) == 0)
			{	  printf("Los datos se han guardado correctamente\n");   }
			else {printf("Ha ocurrido un error al guardar el archivo \n");}
		break;
		case 6:
			if (ventasEstado_saveAsText("deudas.csv" , listaVentas, listaClientes, 1) == 0)
			{	  printf("Los datos se han guardado correctamente\n");   }
			else {printf("Ha ocurrido un error al guardar el archivo \n");}
		break;
		case 7:
			getMenuInformes(&informes);
			switch(informes)
					{
					case 1:
						clientes_max_min(listaVentas, listaClientes, 0, MAX);
						break;
					case 2:
						clientes_max_min(listaVentas, listaClientes, 0, MIN);
						break;
					case 3:
						ventas_max_min(listaVentas, listaClientes, 0, MAX);
						break;
					case 4:
						break;
					}
			break;
		case 8:
			break;
		}

	} while (menu != 8);
	}
	else
	{
		printf("Ha ocurrido un error al cargar los archivos. Favor volver a intentar\n");
	}

}
