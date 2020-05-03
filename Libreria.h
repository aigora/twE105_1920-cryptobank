#include <stdio.h>
#include <string.h>

#define N 20

typedef struct{ // DATOS DE CLIENTES GUARDADOS
	char nombre[20];
	char clave[20];
	float saldo;
	float movimientos[6];
}datosUsuario;

typedef struct{ // DATOS DE CLIENTES NUEVOS
	char nombre[20];
	char clave[20];
	float cantidad;
}datosCliente;

// Usar punteros permite a las funciones acceder a las estructuras sin necesidad de usar variables globales
int comprobarUsuario (datosCliente *cliente, datosUsuario *usuario); 
int comprobarClave (datosCliente *cliente, datosUsuario *usuario);
int crearUsuario (datosCliente *cliente, FILE *pf);
int actualizarFile1 (datosUsuario *usuario, FILE *pf); // SOBRESCRIBE EL FILE ANTERIOR
int actualizarFile2 (datosUsuario *usuario, FILE *pf); // AÑADE INFORMACION AL FILE DESPUES DE SER CREADO
void retirarEfectivo (datosCliente *cliente, datosUsuario *usuario);
void imprimeMovimientos (datosUsuario *usuario);
void ingresarEfectivo (datosCliente *cliente, datosUsuario *usuario);
void cambiarClave (datosUsuario *usuario);

