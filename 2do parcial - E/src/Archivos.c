/*
 * Archivos.c
 *
 *  Created on: 26 nov. 2020
 *      Author: user
 */

#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "Archivos.h"
#include "Cliente.h"
#include "Informes.h"

#define LONG_NOMBRE 4096

/////////////////////////////////       C  A  R  G  A  CLIENTES      //////////////////////////////////////////////////////

/** \brief Carga los datos de los clientes desde el archivo (modo texto).
 *	Después de las validaciones, abre el archivo en modo lectura y lo parsea.
 *
 * \param path char* |  \param pArrayListCliente LinkedList*
 * \return int |   -1 si los paramentros recibidos son NULL | -2 si no logra abrir el archivo | 0 todo ok (logró parsear)
 *
 */
int cliente_controllerLoadFromText(char* path , LinkedList* pArrayListCliente)
{
	int retorno = -1;
	FILE *pFile;

		if (path != NULL && pArrayListCliente != NULL)
		{
			pFile = fopen(path, "r");
			if (pFile != NULL)
			{
				cliente_parserFromText(pFile, pArrayListCliente);
				fclose(pFile);
				retorno = 0;
			}
			else {
				retorno = -2;
			}
		}
		return retorno;
}
/** \brief Parsea los datos los datos de la estructura pasada por paramentro
 * desde el archivo correspondiente (modo texto), analizará todo como cadena y
 * continuará leyendo mientras se cumpla la regla que se le pasó
 *
 * \param path char* |   \param pArrayListCliente LinkedList*
 * \return int
 *
 */
int cliente_parserFromText(FILE* pFile , LinkedList* pArrayListCliente)
{

	int result = -1;
	Cliente *pCliente;
	char header[LONG_NOMBRE];
	char bufferId[LONG_NOMBRE];
	char bufferNombre[LONG_NOMBRE];
	char bufferApellido[LONG_NOMBRE];
	char bufferCuit[LONG_NOMBRE];
	int scan;

	if (pFile != NULL && pArrayListCliente != NULL)
	{
		fscanf(pFile, "%[^\n]\n", header);
		do
		{
			scan = fscanf(pFile, "%[^,],%[^,],%[^,],%[^\n]\n", bufferId, bufferNombre, bufferApellido, bufferCuit);
			if (scan == 4)
			{
				pCliente = cliente_newParametros(bufferId, bufferNombre, bufferApellido, bufferCuit);
				if (pCliente != NULL)
				{
					ll_add(pArrayListCliente, pCliente);
					result = 0;
				}
			}
			else
			{
				break;
			}
		} while (!feof(pFile));
	}
	return result;
}

/////////////////////////////////       C  A  R  G  A  VENTAS      //////////////////////////////////////////////////////

/** \brief Carga los datos de la estructura pasada por parametro desde un archivo(modo texto).
 *	Después de las validaciones, abre el archivo en modo lectura y lo parsea.
 *
 * \param path char* |  \param  LinkedList* estructura
 * \return int |   -1 si si los paramentros recibidos son NULL | -2 si no logra abrir el archivo | 0 todo ok (logró parsear)
 *
 */
int ventas_controllerLoadFromText(char* path , LinkedList* pArrayListVenta)
{
	int retorno = -1;
	FILE *pFile;

		if (path != NULL && pArrayListVenta != NULL)
		{
			pFile = fopen(path, "r");
			if (pFile != NULL)
			{
				ventas_parserFromText(pFile, pArrayListVenta);
				fclose(pFile);
				retorno = 0;
			}
			else {
				retorno = -2;
			}
		}
		return retorno;
}
/** \brief Parsea los datos los datos de la estructura pasada por paramentro
 * desde el archivo correspondiente (modo texto), analizará todo como cadena y
 * continuará leyendo mientras se cumpla la regla que se le pasó
 *
 * \param path char* |   \param pArrayListCliente LinkedList*
 * \return int
 *
 */
int ventas_parserFromText(FILE* pFile , LinkedList* pArrayListVenta)
{

	int result = -1;
	Venta *pVenta;
	char header[LONG_NOMBRE];
	char b_idCliente[LONG_NOMBRE];
	char b_idVenta[LONG_NOMBRE];
	char b_nombreArchivo[LONG_NOMBRE];
	char b_cantidad[LONG_NOMBRE];
	char b_zona[LONG_NOMBRE];
	char b_estado[LONG_NOMBRE];
	int scan;

	if (pFile != NULL && pArrayListVenta != NULL)
	{
		fscanf(pFile, "%[^\n]\n", header);
		do
		{
			scan = fscanf(pFile, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]\n", b_idCliente, b_idVenta, b_nombreArchivo, b_cantidad,b_estado, b_zona);
			if (scan == 6)
			{
				pVenta = venta_newParametros(b_idVenta, b_idCliente, b_nombreArchivo, b_cantidad,b_estado, b_zona);
				if (pVenta != NULL)
				{
					ll_add(pArrayListVenta, pVenta);
					result = 0;
				}
			}
			else
			{
				break;
			}
		} while (!feof(pFile));
	}
	return result;
}

////////////////////////////////// CLIENTES- G  U   A   R   D  A  R  //////////////////////////////////////

/** \brief Guarda los datos de la estructura pasada por parametro en un archivo (modo texto).
 *	Usa el ll_empty como bandera para asegurarse que hayan datos cargados para guardar, hace validaciones
 *	y abre el archivo en modo escritura, lo parsea y luego cierra el archivo.
 *
 * \param path char*
 * \param pArrayEstructura LinkedList*
 * \return int -1 si parametros son NULL, - 2 si no puede abrir el archivo y 0 si todo ok
 *
 */
int cliente_saveAsText(char* path , LinkedList* pArrayListCliente)
{
	int retorno = -1;
	FILE *pFile;

	if (ll_isEmpty(pArrayListCliente)==0)
	{
		if (path != NULL && pArrayListCliente != NULL)
		{
			pFile = fopen(path, "w");
			if (pFile != NULL)
			{
				parser_ClienteToText(pFile, pArrayListCliente);
				fclose(pFile);
				retorno = 0;
			} else
			{
				retorno = -2;
			}
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más clientes. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Parsea los datos los datos de la estructura pasada por parametro
 *  a un archivo(modo texto).
 *
 * \param path char* | \param pEstructura LinkedList*
 * \return int
 *
 */
int parser_ClienteToText(FILE* pFile , LinkedList* pClientes)
{
	int result = -1;
	Cliente* pCliente;
	int len;
	int bufferId;
	char bufferNombre[LONG_NOMBRE];
	char bufferApellido[LONG_NOMBRE];
	char bufferCuit[LONG_NOMBRE];

	if (pFile != NULL && pClientes != NULL)
	{
		len = ll_len(pClientes);
		fprintf(pFile, "ID, NOMBRE, APELLIDO, CUIT\n");
		for (int i = 0; i < len; i++)
		{
			pCliente = (Cliente*)ll_get(pClientes, i);
			if (pCliente != NULL
					&& cliente_getId(pCliente, &bufferId) == 0
					&& cliente_getNombre(pCliente, bufferNombre) == 0
					&& cliente_getApellido(pCliente, bufferApellido) == 0
					&& cliente_getCuit(pCliente, bufferCuit) == 0)
			{
				fprintf(pFile, "%d,%s,%s,%s\n", bufferId, bufferNombre, bufferApellido, bufferCuit);
				result = 0;
			}
		}
	}
	return result;
}


//////////////////////////////// VENTAS- G  U   A   R   D  A  R  //////////////////////////////////////

/** \brief Parsea los datos los datos de la estructura pasada por parametro
 *  a un archivo(modo texto).
 *
 * \param path char* | \param pEstructura LinkedList*
 * \return int
 *
 */
int parser_VentasEstadoToText(FILE* pFile , LinkedList* pClientes, LinkedList* pVenta, int estado)
{
	int result = -1;
	Cliente *pCliente;
	int len;
	int bufferId;
	char bufferNombre[LONG_NOMBRE];
	char bufferApellido[LONG_NOMBRE];
	char bufferCuit[LONG_NOMBRE];
	int cantidad;

	if (pFile != NULL && pClientes != NULL)
	{
		len = ll_len(pClientes);
		fprintf(pFile, "ID CLIENTE, NOMBRE, APELLIDO, CUIT, TOTAL VENTAS\n");
		for (int i = 0; i < len; i++)
		{
			pCliente = (Cliente*)ll_get(pClientes, i);
			if (pCliente != NULL &&
			   !cliente_getId(pCliente, &bufferId) &&
			   !cliente_getNombre(pCliente ,bufferNombre) &&
			   !cliente_getApellido(pCliente ,bufferApellido) &&
			   !cliente_getCuit(pCliente ,bufferCuit) &&
			   estado_xCliente(pVenta, pClientes, estado, i) > -1 )
			{
				cantidad = estado_xCliente(pVenta, pClientes, estado, i);
				fprintf(pFile, "%d,%s,%s,%s,%d\n", bufferId, bufferNombre, bufferApellido, bufferCuit, cantidad);
				result = 0;
			}
		}
	}
	return result;
}
/** \brief Guarda los datos de la estructura pasada por parametro SEGÚN EL ESTADO BOOLEANO (modo texto).
 *
 *	Usa el ll_empty como bandera para asegurarse que hayan datos cargados para guardar, hace validaciones
 *	y abre el archivo en modo escritura, lo parsea y luego cierra el archivo.
 *
 * \param path char*
 * \param pVentas LinkedList*
 * \return int -1 si parametros son NULL, - 2 si no puede abrir el archivo y 0 si todo ok
 *
 */
int ventasEstado_saveAsText(char* path , LinkedList* pVentas, LinkedList* pClientes, int estado)
{
	int retorno = -1;
	FILE *pFile;

	if (ll_isEmpty(pVentas)==0 && ll_isEmpty(pClientes)==0 && (estado == 0 || estado == 1))
	{
		if (path != NULL && pVentas != NULL && pClientes != NULL)
		{
			pFile = fopen(path, "w");
			if (pFile != NULL)
			{
				parser_VentasEstadoToText(pFile, pClientes, pVentas, estado);
				fclose(pFile);
				retorno = 0;
			} else
			{
				retorno = -2;
			}
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más empleados. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Guarda los datos de la estructura pasada por parametro en el archivo data.csv (modo texto).
 *
 *	Usa el ll_empty como bandera para asegurarse que hayan datos cargados para guardar, hace validaciones
 *	y abre el archivo en modo escritura, lo parsea y luego cierra el archivo.
 *
 * \param path char*
 * \param pVentas LinkedList*
 * \return int -1 si parametros son NULL, - 2 si no puede abrir el archivo y 0 si todo ok
 *
 */
int ventas_saveAsText(char* path , LinkedList* pVentas)
{
	int retorno = -1;
	FILE *pFile;

	if (ll_isEmpty(pVentas)==0)
	{
		if (path != NULL && pVentas != NULL)
		{
			pFile = fopen(path, "w");
			if (pFile != NULL)
			{
				parser_VentasToText(pFile, pVentas);
				fclose(pFile);
				retorno = 0;
			} else
			{
				retorno = -2;
			}
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más empleados. Favor volver a intentar\n");
	}
	return retorno;
}
/** \brief Parsea los datos los datos de la estructura pasada por parametro
 *  a un archivo(modo texto).
 *
 * \param path char* | \param pEstructura LinkedList*
 * \return int
 *
 */
int parser_VentasToText(FILE* pFile,  LinkedList* pVenta)
{
	int result = -1;
	Venta *pVentas;
	int len;
	int bufferIdVenta;
	int bufferIdCliente;
	char bufferNombre[LONG_NOMBRE];
	int cantidad;
	int zona;
	int estado;

	if (pFile != NULL && pVenta != NULL)
	{
		len = ll_len(pVenta);
		fprintf(pFile, "ID VENTA, ID CLIENTE, ARCHIVO, CANTIDAD, ESTADO, ZONA\n");
		for (int i = 0; i < len; i++)
		{
			pVentas = (Venta*)ll_get(pVenta, i);
			if (pVentas != NULL &&
			   !venta_getIdVenta(pVentas, &bufferIdVenta) &&
			   !venta_getIdCliente(pVentas, &bufferIdCliente) &&
			   !venta_getNombreArchivo(pVentas ,bufferNombre) &&
			   !venta_getCantidad(pVentas , &cantidad) &&
			   !venta_getEstado(pVentas , &estado) &&
			   !venta_getZona(pVentas, &zona)   )

			{
				fprintf(pFile, "%d,%d,%s,%d,%d,%d\n", bufferIdVenta, bufferIdCliente, bufferNombre, cantidad, estado, zona);
				result = 0;
			}
		}
	}
	return result;
}
