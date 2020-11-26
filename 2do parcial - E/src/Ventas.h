/*
 * Employee.h
 *
 *  Created on: 21 sep. 2020
 *      Author: user
 */

#ifndef VENTAS_H_
#define VENTAS_H_
#include "Cliente.h"
#define QTY_AVISO 1000
#define TRUE 1
#define FALSE 0
#define TEXTO_AVISO 64
#define RUBRO 7


struct {
int idVenta;
int idCliente;
char nombreArchivo[TEXTO_AVISO];
int cantidad;
int estado; //(a cobrar, cobrada)
int zona; //(CABA, ZONA SUR, ZONA OESTE)
}typedef Venta;

int venta_generarIdNuevo(LinkedList* pArrayListVenta);

///////////////////////////////// INFORMES - ESTADÍSTICAS ///////////////////////////////////

int ventas_cobradosPorCliente(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, LinkedList** ventas_cobradas, int estado );
int CF_condicionFiltro_ventasEstado(void* id_venta, void* id_cliente, int estado );

/////////////////////////////////////// INFORMES | LISTADOS | AUXILIARES  ///////////////////////////////////////
int controller_ListVenta(LinkedList* pArrayListVenta);
int ventas_listSinCobrar(LinkedList* pArrayListVenta);
int ventas_listCobradas(LinkedList* pArrayListVenta);
int venta_printByIndex(LinkedList* pArrayListVenta, int index);
int venta_PrintById(LinkedList* pVenta, int idVenta);
int findVentaById(LinkedList* pArrayListVenta, int idVenta);

/////////////////////////////////////      AUXILIARES   CONSTRUCTORES     //////////////////////////////////////

Venta* venta_new(void);
Venta* venta_newParametros(char* idVenta, char* idCliente, char* nombreArchivo, char* cantidad, char* estado,char* zona);

/////////////////////////////////////        GETTERS & SETTERS                //////////////////////////////////////

int venta_setIdVenta(Venta* this,int idVenta);
int venta_getIdTxtVenta (Venta* this, char* idVenta);
int venta_getIdVenta(Venta* this,int* idVenta);

int venta_setIdCliente(Venta* this,int idCliente);
int venta_getIdCliente(Venta* this,int* idCliente);

int venta_setNombreArchivo(Venta* this,char* nombreArchivo);
int venta_getNombreArchivo(Venta* this,char* nombreArchivo);
int venta_setCantidad(Venta* this,int cantidad);
int venta_getCantidad(Venta* this,int* cantidad);
int venta_setEstado(Venta* this,int estado);
int venta_getEstado(Venta* this,int* estado);
int venta_setZona(Venta* this,int zona);
int venta_getZona(Venta* this,int* zona);


#endif /* ARRAYAviso_H_ */
