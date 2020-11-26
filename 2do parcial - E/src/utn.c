#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "utn.h"
#define TEXTO_AVISO 64
#define CUIT 14
#define ARRAY_SIZE 4096
static int isCuit(char* pResult);


int utn_getCadenaNumerica(char* mensaje,char* mensajeError,char* pResultado,int minimo,int maximo,int reintentos)
{
	int retorno = -1;
	char bufferString[LIMITE_BUFFER_STRING];

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos >= 0)
	{
		do
		{
			printf("%s",mensaje);
			if(myGets(bufferString, LIMITE_BUFFER_STRING) == 0 && utn_verifyNumArray(bufferString) == 1 )
			{
				strcpy(pResultado, bufferString);
				retorno = 0;
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}
		while(reintentos > 0);
	}
	return retorno;
}

int utn_verifyNumArray(char* array)
{
	int i=0;
	int retorno = 1;
	if(array[0] == '-')
		{
			i = 1;
		}
	if(array != NULL && strlen(array) > 0)
		{
		while(array[i] != '\0')
		{
			if(array[i] < '0' || array[i] > '9' )
			{
				retorno = 0;
				break;
			}
			i++;
		}
	}
	return retorno;
}

static int isCuit(char string[])
{
	int retorno;
	int guiones=0;
	if(string != NULL && strlen(string) > 0 && string[2] == '-' && string[11] == '-' && string[12] != '\0')
	{
		retorno = 1;
		for(int i = 0;string[i] != '\0'; i++)
		{
			if(string[i] == '-')
			{
				guiones++;
			}
			if(guiones>2 || ((string[i] < '0' || string[i] > '9') && string[i] != '-'))
			{
				retorno = 0;
				break;
			}
		}
	}
	return retorno;
}
int utn_getCuit(char msg[], char msgError[], char pResult[], int attempts, int limit)
{
	int retorno = -1;
	char bufferString[ARRAY_SIZE];

	if(msg != NULL && msgError != NULL && pResult != NULL && attempts >= 0)
	{
		do
		{
			printf("\n%s", msg);
			if(myGets(bufferString, ARRAY_SIZE) == 0 && isCuit(bufferString) == 1 && strnlen(bufferString, sizeof(bufferString)) < limit)
			{
				retorno = 0;
				strncpy(pResult, bufferString, limit);
				break;
			}
			else
			{
				printf("%s", msgError);
				attempts--;
			}
		}while(attempts >= 0);
	}
	return retorno;
}
/** utn_getNumero
brief Solicita un entero al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int minimo, valor minimo admitido
 * \param int minimo, valor maximo admitido
 * \return (-1) Error / (0) Ok*/
int utn_getNumero (char* mensaje, char* mensajeError, int* pResultado,int reintentos,int maximo, int minimo)
 {

	int retorno = -1;
	int buffer;

	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos > 0)
	{
		do{
			printf("%s", mensaje);
			fflush(stdin);
			if(getInt(&buffer) == 0 &&
					buffer >= minimo &&
					buffer <= maximo)
			{
				*pResultado = buffer;
				retorno = 0;
				break;
			}
			else
			{
				printf("%s", mensajeError);
				reintentos--;
			}
		}while(reintentos >=0);
	}
	return retorno;
}
/*getInt
 *
 */
int getInt ( int* pResultado)
{
	int retorno=-1;
	char buffer[50];
	if(pResultado != NULL &&
			myGets(buffer, sizeof(buffer))==0 &&
			esNumerica(buffer, sizeof(buffer))==1)
	{
		retorno=0;
		*pResultado=atoi(buffer);
	}
	return retorno;
}
/*myGets
 *
 */
int myGets(char cadena[], int longitud)
{
	int retorno=-1;
	if(cadena != NULL && longitud >0 && fgets(cadena,longitud,stdin)==cadena)
	{
		fflush(stdin);
		if(cadena[strlen(cadena)-1] == '\n' && cadena[0] != '\n')
		{
		cadena[strlen(cadena)-1] = '\0';
		}
		retorno=0;
	}
	return retorno;
}
/** esNumerica
 * \brief Verifica si la cadena ingresada es numerica
 * \param cadena Cadena de caracteres a ser analizada
 * \return Retorna 1 (vardadero) si la cadena es numerica y 0 (falso) si no lo es
 */
int esNumerica(char* cadena, int limite)
{
	int retorno = 1; // VERDADERO
	int i;
	for(i=0;i<limite && cadena[i] != '\0';i++)
	{
		if(i==0 && (cadena[i] == '+' || cadena[i] == '-'))
		{
			continue;
		}
		if(cadena[i] > '9' || cadena[i] < '0')
		{
			retorno = 0;
			break;		}
	}
	return retorno;
}
/** esUnNombreValido
 * brief
 * 	Verifica una cadena recibida como parametro para determinir si es un nombre valido
 * \param char* cadena, Cadena a analizar
 * \param int limite, indica la cantidad de letras maxima de la cadena
 * \return (0) Indicar que no es un nombre valido / (1) Indica que que es un nombre valido
 */
int esUnNombreValido(char* cadena,int limite)
{
	int respuesta = 1; // TODO OK

	for(int i=0; i<=limite && cadena[i] != '\0';i++)
	{
		//esta mal <----- A - Z -----> Esta mal
		if(	(cadena[i] < 'A' || cadena[i] > 'Z') &&
			(cadena[i] < 'a' || cadena[i] > 'z') &&
			(cadena[i] == '.' || cadena[i] != ' ') && (cadena[i]!='-' || cadena[0]=='-' ))
		{
			respuesta = 0;
			break;
		}
	}
	return respuesta;
}
int utn_getTexto(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite)
{
	char bufferString[TEXTO_AVISO];
	int retorno = -1;
	int allFine = (mensaje != NULL && mensajeError != NULL && pResultado != NULL && reintentos >= 0 && limite > 0);

	if(	allFine)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,TEXTO_AVISO) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)<= limite )
			{
				retorno = 0;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);

	if (reintentos == -1)
		{
				printf("Se ha quedado sin reintentos, favor intentar de nuevo \n");
		}
	}
	return retorno;}


int utn_getNombre(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;
	int allFine = (mensaje != NULL && mensajeError != NULL && pResultado != NULL && reintentos >= 0 && limite > 0);

	if(	allFine)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)<= limite &&
				esUnNombreValido(bufferString,limite) != 0 )
			{
				retorno = 0;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);

	if (reintentos == -1)
		{
				printf("Se ha quedado sin reintentos, favor intentar de nuevo \n");
		}
	}
	return retorno;

}
/**
 * \brief Solicita un nombre al usuario
 * \param char* mensaje, Es el mensaje a ser mostrado al usuario
 * \param char* mensaje, Es el mensaje de error a ser mostrado al usuario
 * \param int* pResultado, puntero al espacio de memoria donde se dejara el valor obtenido
 * \param int reintentos, cantidad de oportunidades para ingresar el dato
 * \param int limite, indica la cantidad de letras maxima del nombre
 * \return (-1) Error / (0) Ok
 *
 */
int utn_getNickName(char* mensaje, char* mensajeError, char* pResultado,int reintentos, int limite)
{
	char bufferString[LIMITE_BUFFER_STRING];
	int retorno = -1;

	if(		mensaje != NULL &&
			mensajeError != NULL &&
			pResultado != NULL &&
			reintentos >= 0 &&
			limite > 0)
	{
		do
		{
			printf("%s",mensaje);
			if( myGets(bufferString,LIMITE_BUFFER_STRING) == 0 &&
				strnlen(bufferString,sizeof(bufferString)-1)<= limite &&
				esUnNombreValido(bufferString,limite) != 0 )
			{
				retorno = 0;
				//NO EXISTE pResultado = bufferString;
				strncpy(pResultado,bufferString,limite);
				break;
			}
			else
			{
				printf("%s",mensajeError);
				reintentos--;
			}
		}while(reintentos >= 0);

	}
	return retorno;

}

//////////////////////////////////////////////////////////////////
int utn_getNumeroFloat(float* pResultado,char* mensaje,char* mensajeError,float minimo,float maximo,int reintentos){
	int retorno = -1;
	float bufferFloat;
	int resultadoScan;
	if(pResultado != NULL && mensaje != NULL && mensajeError != NULL && minimo <= maximo && reintentos > 0){
		do{
			printf("%s", mensaje);
			fflush(stdin);
			resultadoScan = getFloat(&bufferFloat);
			if(resultadoScan && minimo <= bufferFloat && maximo >= bufferFloat){
				*pResultado = bufferFloat;
				retorno = 0;
				break;
			}else{
				printf("%s", mensajeError);
				printf("\n-REINTENTOS: %d \n",reintentos);
				reintentos--;
			}

		}while(reintentos >= 0);
	}
	return retorno;
}
////////////////////////////////////////
int getFloat(float* pFloat){
	int retorno = 0;
	char bufferFloat[64];
	if(pFloat != NULL){
		fflush(stdin);

		if(!myGets(bufferFloat,sizeof(bufferFloat)) && esFlotante(bufferFloat,sizeof(bufferFloat))){
			*pFloat = atof(bufferFloat);
			retorno = 1;
		}
	}
	return retorno;
}
/////////////////////////////////////////
int esFlotante(char* array,int limite){
	int retorno = -1;
	int i = 0;
	int contadorDePuntos = 0;

	if(array != NULL && limite > 0){
		retorno = 1;
		if(array[0] != '+' || array[0] != '-'){
			i = 1;
		}
		while(array[i] != '\0'){
			if((array[i] < '0' || array[i] > '9') && array[i] != '.'){
				retorno = 0;
				break;
			}
			if(array[i] == '.'){
				contadorDePuntos++;
				if(contadorDePuntos > 1){
					retorno = 0;
					break;
				}
			}
			i++;
		}
	}
	return retorno;
}
/////////////////////////////////////////////////////////////

