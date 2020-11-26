/*
 * Informes.h
 *
 *  Created on: 26 nov. 2020
 *      Author: user
 */

#ifndef INFORMES_H_
#define INFORMES_H_

//#include "LinkedList.h"

#include "LinkedList.h"
#include "utn.h"
#include "Cliente.h"
#include "Ventas.h"

//////////// FUNCIONES CRITERIOS

int totalVentas_porCliente(void* id_venta, void* id_cliente, int estado );
int estado_xCliente(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int estado, int id);
int criterioMaxMin_porQty(void* id_venta, int estado );


////////// MAX MINS
int clientes_max_min(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int estado, int limite);
int ventas_max_min(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int estado, int limite);


#endif /* INFORMES_H_ */
