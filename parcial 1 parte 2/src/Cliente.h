/*
 * Cliente.h
 *
 *  Created on: 21 sep. 2020
 *      Author: user
 */

#ifndef CLIENTE_H_
#define CLIENTE_H_
//clientes
#define TRUE 1
#define FALSE 0
#define NAME 51
#define CUIT 14
#define QTY_CLIENTES 100

struct {
int idCliente;
char nombreCliente[NAME];
char apellidoCliente[NAME];
char cuitCliente[CUIT];
int isEmpty;
}typedef Cliente;



int clienteAltaForzada (Cliente* pListClientes, int len, int indice, int* idCliente, char* nombreCliente, char* apellidoCliente, char* cuitCliente);
int initCliente(Cliente* pListClientes, int limit);
int getMainMenu(int* menu);
int cliente_generarIdNuevo(void);
int cliente_printByIndex(Cliente* pListClientes, int limit, int index);
int addCliente(Cliente* pListClientes, int len);
int findClienteById(Cliente* pListClientes, int len, int id);
int cliente_validacionAlta (Cliente* pListClientes, int len);
int cliente_buscadorIndiceLibre (Cliente* pListClientes, int len);
int cliente_modificar (Cliente* pListClientes, int limite);
int client_findByCuit(Cliente* pListClientes, int len,char* cuit);
////////////////////////////////////////////////////////////////////////


int findClienteById(Cliente* pListClientes, int len, int id);
int printCliente(Cliente* pListClientes, int len);
int cliente_buscarLibreRef(Cliente* pListClientes, int limit, int *pIndex);
int cliente_printById(Cliente* pListClientes, int limit, int index);
int cliente_buscarId(Cliente* pListClientes, int limite, int id);


#endif /* ARRAYCliente_H_ */
