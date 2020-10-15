/*
 * Employee.h
 *
 *  Created on: 21 sep. 2020
 *      Author: user
 */

#ifndef AVISO_H_
#define AVISO_H_
#include "Cliente.h"
#define QTY_AVISO 1000
#define TRUE 1
#define FALSE 0
#define TEXTO_AVISO 64
#define RUBRO 7


struct {
int idAviso;
int rubro;
char textoAviso[TEXTO_AVISO];
int estado;
int isEmpty;
int idCliente;
}typedef Aviso;

int avisoAltaForzada (Aviso* pAviso, int lenAviso, int indiceAviso, int* idAviso, int rubro, char* textoAviso, int idCliente, int estado);
int initAviso(Aviso* pAviso, int limit);
int aviso_validacionAlta (Aviso* pAviso, int len);
int aviso_buscarLibreRef(Aviso* pAviso, int limit, int *pIndex);
int aviso_printByIndex(Aviso* pAviso, int limit, int index);
int aviso_generarIdNuevo(void);
int findAvisoById(Aviso* pAviso, int len, int id);
int aviso_alta (Aviso* pAviso, int limiteAviso, Cliente* pListClientes, int limiteClientes);
int aviso_modificarEstado (Aviso* pAviso, int lenAviso, Cliente* pListClientes, int limiteClientes);
int removeClienteConAvisos(Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso);


int aviso_buscadorIndiceLibre (Aviso* pAviso, int len);
int aviso_buscarId(Aviso* pAviso, int limite, int id);


#endif /* ARRAYAviso_H_ */
