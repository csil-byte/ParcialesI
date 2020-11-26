/*
 * Archivos.h
 *
 *  Created on: 26 nov. 2020
 *      Author: user
 */

#ifndef ARCHIVOS_H_
#define ARCHIVOS_H_

#include "LinkedList.h"
#include <stdio.h>

/////////////////////////////////       C  A  R  G  A  CLIENTES      //////////////////////////////////////////////////////


int cliente_parserFromText(FILE* pFile , LinkedList* pArrayListCliente);
int cliente_controllerLoadFromText(char* path , LinkedList* pArrayListCliente);

/////////////////////////////////       C  A  R  G  A  VENTAS      //////////////////////////////////////////////////////


int parser_VentasEstadoToText(FILE* pFile , LinkedList* pClientes, LinkedList* pVenta, int estado);
int ventasEstado_saveAsText(char* path , LinkedList* pVentas, LinkedList* pClientes, int estado);

int ventas_controllerLoadFromText(char* path , LinkedList* pArrayListVenta);
int ventas_parserFromText(FILE* pFile , LinkedList* pArrayListVenta);

//////////////////////////////////CLIENTES-  G  U   A   R   D  A  R  //////////////////////////////////////

int cliente_saveAsText(char* path , LinkedList* pArrayListCliente);
int parser_ClienteToText(FILE* pFile , LinkedList* pClientes);

//////////////////////////////// VENTAS- G  U   A   R   D  A  R  //////////////////////////////////////

int parser_VentasEstadoToText(FILE* pFile , LinkedList* pClientes, LinkedList* pVenta, int estado);
int ventasEstado_saveAsText(char* path , LinkedList* pVentas, LinkedList* pClientes, int estado);
int ventas_saveAsText(char* path , LinkedList* pVentas);
int parser_VentasToText(FILE* pFile,  LinkedList* pVenta);




#endif /* ARCHIVOS_H_ */
