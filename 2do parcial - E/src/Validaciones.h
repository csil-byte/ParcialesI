/*
 * Validaciones.h
 *
 *  Created on: 26 nov. 2020
 *      Author: user
 */

#ifndef VALIDACIONES_H_
#define VALIDACIONES_H_

#include "LinkedList.h"

int isValidName(char* cadena,int limite);
int isValidCuit(char string[]);
int isCuitRepeated(LinkedList* pClientes, char* cuit);

#endif /* VALIDACIONES_H_ */
