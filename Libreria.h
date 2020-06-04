#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define N 20

typedef struct // MOVIMIENTOS DE CLIENTES
{
	char fechayhora[16];
	float cantidad;
}datosMovimientos;

typedef struct{ // DATOS DE CLIENTES GUARDADOS
	char nombre[20];
	char clave[20];
	float saldo;
	datosMovimientos movimientos[20];
}datosUsuario;

typedef struct{ // DATOS DE CLIENTES NUEVOS
	char nombre[20];
	char clave[20];
	float cantidad;
}datosCliente;

// Usar punteros permite a las funciones acceder a las estructuras sin necesidad de usar variables globales
int comprobarUsuario (datosCliente *cliente, datosUsuario *usuario); 
int comprobarClave (datosCliente *cliente, datosUsuario *usuario);
void crearUsuario (datosCliente *cliente, datosUsuario *usuario, FILE *pf);
int actualizarFile1 (datosUsuario *usuario, FILE *pf); // SOBRESCRIBE EL FILE ANTERIOR
int actualizarFile2 (datosUsuario *usuario, FILE *pf); // AÑADE INFORMACION AL FILE DESPUES DE SER CREADO
int retirarEfectivo (datosCliente *cliente, datosUsuario *usuario);
int imprimeMovimientos (datosUsuario *usuario);
int ingresarEfectivo (datosCliente *cliente, datosUsuario *usuario);
void cambiarClave (datosUsuario *usuario);
void fechayhora(datosMovimientos *movimientos);
