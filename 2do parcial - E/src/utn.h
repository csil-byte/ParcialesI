/*
 * utn.h
 *
 *  Created on: Sep 8, 2020
 *      Author: Mauro
 */

#ifndef UTN_H_
#define UTN_H_

#define LIMITE_BUFFER_STRING 4096
#define TEXTO_AVISO 64

int utn_verifyNumArray(char* array);
int utn_getCadenaNumerica(char* mensaje,char* mensajeError,char* pResultado,int minimo,int maximo,int reintentos);

int utn_getCuit(char msg[], char msgError[], char pResult[], int attempts, int limit);
int utn_getNumero(char* mensaje, char* mensajeError, int* pResultado,int reintentos,int maximo,int minimo);
int getInt (int* pResultado);
int esNumerica(char* cadena, int limite);
int myGets(char* cadena, int longitud);
int esUnNombreValido(char* cadena,int limite);
int utn_getTexto(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite);

int esAlfaNumerica(char* pResultado);
int utn_getNombre(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite);
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos);
int utn_getNickName(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite);
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos);
int getFloat(float* pFloat);
int esFlotante(char* array,int limite);


#endif /* UTN_H_ */
