/*
 ============================================================================
 Name        : Parcial I .c
 Author      : Cecilia
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#include "Cliente.h"
#include "Aviso.h"
#include "Informe.h"

#define QTY_CLIENTES 100
#define QTY_AVISO 1000
#define CUIT 14

int main(void) {

	setbuf(stdout, NULL);
	Cliente pListClientes[QTY_CLIENTES];
	Aviso pAviso [QTY_AVISO];
	int menu;
////////////////descomentar para usar los clientes y avisos dados de alta de manera forzosa///////////////////////////////////

	int idCliente = 0;
	int idAviso = 0;

	initCliente(pListClientes, QTY_CLIENTES);
	initAviso(pAviso,QTY_AVISO);

/////////////// para usar los clientes y avisos dados de alta de manera forzosa para facilitar debugging, descomentar lo siguiente: /////////////////
	clienteAltaForzada (pListClientes, QTY_CLIENTES, 0, &idCliente, "Ana", "Bolena", "01-00000000-1");
	clienteAltaForzada (pListClientes, QTY_CLIENTES, 1, &idCliente, "Salem", "Salome", "02-00000000-2");
	clienteAltaForzada (pListClientes, QTY_CLIENTES, 2, &idCliente, "Cheyenne", "TieneApellidoCheyenne", "03-00000000-3");
	clienteAltaForzada (pListClientes, QTY_CLIENTES, 3, &idCliente, "Ricky", "Martin", "04-00000000-4");
	clienteAltaForzada (pListClientes, QTY_CLIENTES, 4, &idCliente, "David", "Bisbal", "05-00000000-5");

	avisoAltaForzada (pAviso, QTY_AVISO, 0, &idAviso, 1, "Hola, este es mi primer aviso",                0);
	avisoAltaForzada (pAviso, QTY_AVISO, 1, &idAviso, 1, "Bueno, a ver cuando se termina la cuarentena", 1);
	avisoAltaForzada (pAviso, QTY_AVISO, 2, &idAviso, 5, "Bah, qcyo, está bueno a veces",                1);
	avisoAltaForzada (pAviso, QTY_AVISO, 3, &idAviso, 1, "A ver si apruebo",                             1);
	avisoAltaForzada (pAviso, QTY_AVISO, 4, &idAviso, 2, "Aviso random generado",                        2);
	avisoAltaForzada (pAviso, QTY_AVISO, 5, &idAviso, 2, "Donnie Darko no es tan buena peli como dicen", 3);
	avisoAltaForzada (pAviso, QTY_AVISO, 6, &idAviso, 3, "Casi último aviso",                            4);
	avisoAltaForzada (pAviso, QTY_AVISO, 7, &idAviso, 3, "Casi casi último aviso",                       4);
	avisoAltaForzada (pAviso, QTY_AVISO, 8, &idAviso, 3, "Ultimo aviso",                                 4);

	do {
		getMainMenu(&menu);
		switch (menu) {
		case 1:
			addCliente(pListClientes, QTY_CLIENTES);
			break;
		case 2:
			cliente_modificar (pListClientes, QTY_CLIENTES);
			break;
		case 3:
			removeClienteConAvisos(pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO);
			break;
		case 4:
			aviso_alta (pAviso, QTY_AVISO, pListClientes, QTY_CLIENTES);
			break;
		case 5:
			aviso_modificarEstado (pAviso, QTY_AVISO, pListClientes, QTY_CLIENTES);
			break;
		case 6:
			printClienteInforme(pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO);
			break;
		case 7:
			getSubMenu(pListClientes, QTY_CLIENTES, pAviso, QTY_AVISO);
			break;
		case 8:
			break;
		}

	} while (menu != 8);

}


