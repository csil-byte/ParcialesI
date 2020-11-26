/*
 * Informes.c
 *
 *  Created on: 26 nov. 2020
 *      Author: user
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "LinkedList.h"
//#include "utn.h"
//#include "Cliente.h"
#include "Ventas.h"
#include "Informes.h"

//////////// FUNCIONES CRITERIOS

int estado_xCliente(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int estado, int id)
{
	int contador = -1;


	if (ll_reduceCondicion(pArrayListVenta,  pArrayListCliente, totalVentas_porCliente, &contador, id, estado) > -1)
	{
		return contador;
	}
	else
	{
		contador= -1;
	}
	return contador;
}
int totalVentas_porCliente(void* id_venta, void* id_cliente, int estado )
{
	int retorno = -1;
	Venta* bufferVentas;
	Cliente* bufferClientes;
	bufferVentas = (Venta*) id_venta;
	bufferClientes = (Cliente*) id_cliente;

	if (bufferVentas != NULL && bufferClientes != NULL)
	{
		if (bufferVentas->idCliente == bufferClientes->id && bufferVentas->estado == estado )
			{
				retorno = bufferVentas->cantidad;
			}
		else
			{
				retorno = 0;
			}
	}
	return retorno;
}
int criterioMaxMin_porQty(void* id_venta, int estado )
{
	//////// funcion criterio para ll_1Lista_maxmin, si se cumple una condicion -> devolver un valor número
	///////  	para acumular.

	int retorno = -1;
	Venta* bufferVentas;
	bufferVentas = (Venta*) id_venta;

	if (bufferVentas != NULL && bufferVentas != NULL)
	{
		if (bufferVentas->estado == estado )
			{
				retorno = bufferVentas->cantidad;
			}
		else
			{
				retorno = 0;
			}
	}
	return retorno;
}

////////////// MAX MIN

int clientes_max_min(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int estado, int limite)
{
	Cliente* bufferCliente;
	int retorno = -1;
	int cantidad;

	bufferCliente = (Cliente*)ll_2Listas_maxmin(pArrayListVenta,  pArrayListCliente, estado_xCliente, &cantidad, estado, limite);
	printf("Total de afiches: %d\n", cantidad);
	printf("==============   El cliente es:   Nombre: %s | Apellido: %s | CUIT: %s |      ============== \n", bufferCliente->nombre, bufferCliente->apellido, bufferCliente->cuit);

	return retorno;
}
int ventas_max_min(LinkedList* pArrayListVenta, LinkedList* pArrayListCliente, int estado, int limite)
{
	Venta* bufferVenta;
	int retorno = -1;
	int cantidad;
	int id;

	bufferVenta = (Venta*)ll_1Lista_maxmin(pArrayListVenta, criterioMaxMin_porQty, &cantidad, 0, estado, limite);
	venta_getIdCliente(bufferVenta, &id);
	//printf("ID CLIENTE: %d \n", id);
	//printf("\n[1======VENTABUSCADORLIMITES]Total de afiches: %d\n", cantidad);
	//printf("==============   El cliente es:  ID: %d | Nombre: %s | Apellido: %s | CUIT: %s |      ============== \n", bufferCliente->id, bufferCliente->nombre, bufferCliente->apellido, bufferCliente->cuit);

	printf("==============   ID Cliente: %d | Id Venta: %d | Cantidad: %d |   ============== \n",bufferVenta->idCliente, bufferVenta->idVenta, bufferVenta->cantidad);
	cliente_PrintById(pArrayListCliente, id);
	return retorno;
}

/////////// SORT

/** \brief Ordenar ventas
 *	Usa ll_isEmpty como flag para verificar que se hayan cargado los datos de algún archivo. Luego utilizando el ll_sort,
 *		pasandole la función criterio auxiliar creada, se imprimen todos los ventas para facilitar
 *		revisión del ordenamiento.
 *
 * \param pArrayListVenta LinkedList*
 * \return int -1 si hay errores | 0 si todo ok
 *
 */
/*int controller_sortVenta(LinkedList* pArrayListVenta)
{
	int retorno = -1;
	if (ll_isEmpty(pArrayListVenta)==0)
	{
		if (ll_sort(pArrayListVenta, employee_funcionCriterio, 0) != -1)
		{
			controller_ListVenta(pArrayListVenta);
			retorno = 0;
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más ventas. Favor volver a intentar\n");
	}
	return retorno;
}*/
////////// falta funcion criterio

/** \brief Ordenar clientes
 *	Usa ll_isEmpty como flag para verificar que se hayan cargado los datos de algún archivo. Luego utilizando el ll_sort,
 *		pasandole la función criterio auxiliar creada, se imprimen todos los clientes para facilitar
 *		revisión del ordenamiento.
 *
 * \param pArrayListCliente LinkedList*
 * \return int -1 si hay errores | 0 si todo ok
 *
 */
/*int controller_sortCliente(LinkedList* pArrayListCliente)
{
	int retorno = -1;
	if (ll_isEmpty(pArrayListCliente)==0)
	{
		if (ll_sort(pArrayListCliente, cliente_funcionCriterio, 0) != -1)
		{
			controller_ListCliente(pArrayListCliente);
			retorno = 0;
		}
	}
	else
	{
		printf("Error, deberá cargar un archivo antes de agregar más clientes. Favor volver a intentar\n");
	}
	return retorno;
}*/
////////// falta funcion criterio
