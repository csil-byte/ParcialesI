/*
 * Cliente.h
 *
 *  Created on: 21 sep. 2020
 *      Author: user
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_

#include "LinkedList.h"
//#include <stdio.h>

#define TRUE 1
#define FALSE 0
#define NAME 51
#define CUIT 13


struct {
int id; //idCliente
char nombre[NAME]; //nombreCliente
char apellido[NAME]; //apellidoCliente
char cuit[CUIT]; //cuitCliente

}typedef Cliente;

int controller_generarIdNuevo(LinkedList* pArrayListCliente);

/////////////////////////////////////// INFORMES | LISTADOS | AUXILIARES  ///////////////////////////////////////
int controller_ListCliente(LinkedList* pArrayListCliente);
int cliente_printByIndex(LinkedList* pArrayListCliente, int index);
int cliente_PrintById(LinkedList* pArrayListCliente, int id);
int findClienteById(LinkedList* pArrayListCliente, int id);
int controller_sortCliente(LinkedList* pArrayListCliente);

/////////////////////////////////////      AUXILIARES   CONSTRUCTORES     //////////////////////////////////////
Cliente* cliente_new(void);
Cliente* cliente_newParametros(char* id,char* nombre, char* apellido,char* cuit);
/////////////////////////////////////        GETTERS & SETTERS                //////////////////////////////////////
int cliente_setId(Cliente* this,int id);
int cliente_getIdTxt (Cliente* this, char* id);
int cliente_getId(Cliente* this,int* id);
int cliente_setNombre(Cliente* this,char* nombre);
int cliente_getNombre(Cliente* this,char* nombre);
int cliente_setApellido(Cliente* this,char* apellido);
int cliente_getApellido(Cliente* this,char* apellido);
int cliente_setCuit(Cliente* this,char* cuit);
int cliente_getCuit(Cliente* this,char* cuit);





#endif /* ARRAYCliente_H_ */
