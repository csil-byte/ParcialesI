/*
 * Informe.h
 *
 *  Created on: 11 oct. 2020
 *      Author: user
 */

#ifndef INFORME_H_
#define INFORME_H_

//clientes
#define PRECIO_MAX 99999999.00
#define TRUE 1
#define FALSE 0
#define NAME 51
#define CUIT 14
#define QTY_CLIENTES 100
//aviso
#define QTY_AVISO 1000
#define TEXTO_AVISO 64
#define DIRECCION 100
#define RUBRO 7
#define LIMITEINDICE 10


int printClienteInforme(Cliente* pListClientes, int len, Aviso* pAviso, int limiteAviso);


int getCantidadAvisosTotalesPorCliente(Cliente* pListClientes, int len, Aviso* pAviso, int limiteAviso, int id);
int getClienteConMasAvisos (Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso);

int getClienteConMasAvisosActivos (Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso);
int getCantidadAvisosActivosPorCliente(Cliente* pListClientes, int len, Aviso* pAviso, int limiteAviso, int id);

int getClienteConMasAvisosPausados (Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso);
int getCantidadAvisosPausadosPorCliente(Cliente* pListClientes, int len, Aviso* pAviso, int limiteAviso, int id);
int getCantidadAvisosPausados (Aviso* pAviso, int limiteAvisos);

int getRubroConMasAvisos (Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso);
int getSubMenu(Cliente* pListClientes, int limiteClientes, Aviso* pAviso, int limiteAviso);





#endif /* INFORME_H_ */
