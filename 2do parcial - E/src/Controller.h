/*
 * Controller.h
 *
 *  Created on: 26 nov. 2020
 *      Author: user
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "Cliente.h"
#include "Ventas.h"

int printClient_bySaleId(LinkedList* pArrayListCliente, LinkedList* pArrayVentas, int idVenta);

/////////////////////////////////   CLIENTE    ALTA | MODIFICACIÓN | BAJA      //////////////////////////////////////////////////////
int controller_addCliente(LinkedList* pArrayListCliente);
int controller_hardCode(LinkedList* pArrayListCliente, char* name, char* apellido, char* cuit );
int controller_editCliente(LinkedList* pArrayListCliente);
void cliente_delete(Cliente* this);
int controller_removeCliente(LinkedList* pArrayListCliente, LinkedList* pVentas);

/////////////////////////////////   VENTAS    ALTA | MODIFICACIÓN | BAJA      //////////////////////////////////////////////////////
int controller_addVenta(LinkedList* pArrayListVenta,LinkedList* pArrayListCliente);
int venta_hardCode(LinkedList* pArrayListVenta, char* idCliente, char* nombreArchivo, char* cantidad, char* estado, char* zona );

int controller_editVenta(LinkedList* pArrayListVenta, LinkedList* pArrayClientes);
int menuModificacion (LinkedList* pArrayListVenta, int* indiceModificar);
//////////////////////////////////////// C  O  B  R  A  N  Z  A  S //////////////////////////////////
int ventas_cobranza (LinkedList* pArrayListVenta, LinkedList* pCliente);

void venta_delete(Venta* this);
int controller_removeVenta(LinkedList* pArrayListVenta);
int removeAllVentas_byClientId(LinkedList* pArrayListCliente, LinkedList* pArrayVentas, int idCliente);

///////////////////// AUX

int cliente_areAllSalesPaid(LinkedList* pArrayListCliente, LinkedList* pArrayVentas, int idCliente);




#endif /* CONTROLLER_H_ */
