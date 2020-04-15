#include <stdio.h>
#include <string.h>

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
void retirarEfectivo (datosCliente *cliente, datosUsuario *usuario);
void imprimeMovimientos (datosUsuario *usuario);
void ingresarEfectivo (datosCliente *cliente, datosUsuario *usuario);
void cambiarClave (datosUsuario *usuario);

int main(){
	int menu, op;
    float cantidad;
	int salida = 0; // INDICA CUANDO DEBE TERMINAR EL PROGRAMA 
	int intentosUsuario = 5, intentosClave = 5; // VECES QUE PUEDE EQUIVOCARSE EL USUARIO AL INTRODUCIR LOS DATOS
	datosUsuario usuario1 = {"abel", "1234", 100}; // DECLARACION DE CLIENTE PARA REALIZAR PRUEBA DEL PROGRAMA
	datosCliente cliente1;
	
	do{
		printf("\n\n - Bienvenido a CryptoBank.\n\n");
		printf("\t1) Iniciar sesion\n\t2) Registrarse\n\t3) Salir \n\t");
			scanf("%i", &menu);
		switch(menu){
			case 1:
				do{
					intentosUsuario--;
					printf("\nIntroduce tu nombre de usuario: ");
						scanf("%s", cliente1.nombre);
					// EL USUARIO EXISTE	
					if(comprobarUsuario(&cliente1, &usuario1) == 0){
						do{
							intentosClave--;
							printf("\nIntroduce tu clave personal: ");
							scanf("%s", cliente1.clave);
							// LA CLAVE ES CORRECTA
							if(comprobarClave(&cliente1, &usuario1) == 0){ 
								system("cls");
								printf("\n\nHola %s, bienvenido a tu area personal.\n", usuario1.nombre);
								do{
                                    printf("\n\t1) Retirar efectivo\n\t2) Ingresar efectivo\n\t3) Consultar saldo\n\t4) Consultar movimientos\n\t\
5) Cambiar clave personal \n\t6) Cerrar sesion\n\t");
                                    scanf("%i", &op);
                                    switch(op){
                                        case 1:
                                        //RETIRAR EFECTIVO
                                            retirarEfectivo(&cliente1, &usuario1);
                                        break;
                                        
                                        case 2:
                                        //INGRESAR EFECTIVO
                                            ingresarEfectivo(&cliente1, &usuario1);
                                        break;
                                        
                                        case 3:
                                        //CONSULTAR SALDO
                                        	system("cls");
                                            printf("\nDispone actualmente de: %.2fE", usuario1.saldo);
                                            break;
                                        case 4:
                                        //CONSULTAR MOVIMIENTOS
                                        	imprimeMovimientos (&usuario1);
                                            break;
										case 5:
										//CAMBIAR CLAVE
											cambiarClave(&usuario1); 
                                    }
                                }while(op!=6);
							}
							else{
								system("cls");
								printf("\n\tClave incorrecta. Vuelva a intentarlo.\n");
							}
								
						}while(comprobarClave(&cliente1, &usuario1) != 0 && intentosClave > 0); // CLAVE INCORRECTA E INTENTOS DISPONIBLES
					}
					else{
						system("cls");
						printf("\n\tUsuario no encontrado. Vuelva a intentarlo.\n");
					}
				}while(comprobarUsuario(&cliente1, &usuario1) != 0 && intentosUsuario > 0); // USUARIO INCORRECTO E INTENTOS DISPONIBLES
					
				
				break;
			case 2:
				break;
			case 3:
				salida = 1; // EL USUARIO DESEA SALIR
				break;
			default:
				printf("\nOpcion incorrecta.\n");
		}	
	}while(salida != 1);
	
	return 0;
}

int comprobarUsuario (datosCliente *cliente, datosUsuario *usuario){
	return strcmp(cliente->nombre, usuario->nombre); // SI SON IGUALES DEVUELVE 0
}

int comprobarClave (datosCliente *cliente, datosUsuario *usuario){
	return strcmp(cliente->clave, usuario->clave); // SI SON IGUALES DEVUELVE 0
}

void retirarEfectivo (datosCliente *cliente, datosUsuario *usuario){
	int operacion_valida = 0;
	do{
		printf("\nIntroducir cantidad a retirar: ");
        scanf("%f", &cliente->cantidad);
        if(cliente->cantidad <= usuario->saldo){
        	operacion_valida = 1;
        	system("cls");
            printf("\nRetirada de %.2f E realizada correctamente.\n", cliente->cantidad);
            usuario->saldo -= cliente->cantidad;
            int i;
			usuario->movimientos[0] = -cliente->cantidad;
            for(i=6;i>=1;i--)
			{
				usuario->movimientos[i] = usuario->movimientos[i-1];
			}
			usuario->movimientos[0] = 0;
			
            printf("\nDispone actualmente de: %.2f E.\n", usuario->saldo);
        }else{ //No hay dinero suficiente
        	system("cls");
            printf("\nNo dipone de la cantidad introducida. Introduzca un importe valido.\n\n");
    	}
	}while(operacion_valida != 1);
}

void ingresarEfectivo (datosCliente *cliente, datosUsuario *usuario){
	printf("\nIntroducir cantidad a ingresar: ");
    scanf("%f", &cliente->cantidad);
    system("cls");
    printf("\nIngreso de %.2f E realizado correctamente.\n", cliente->cantidad);
    usuario->saldo += cliente->cantidad;
	int i;
	usuario->movimientos[0] = cliente->cantidad;
	for(i=6;i>=1;i--)
	{
		usuario->movimientos[i] = usuario->movimientos[i-1];
	}
	usuario->movimientos[0] = 0;
	
	printf("\nDispone actualmente de: %.2f E.\n", usuario->saldo);
}

void imprimeMovimientos (datosUsuario *usuario)
{
	int i;
	system("cls");
	if(usuario->movimientos[1]==0)
 	{
 		printf("\nTodavia no se han realizado movimientos en su cuenta\n");
	}
	else
	printf("Sus ultimos movimientos han sido.\n");
	for(i=1;i<6;i++)
	{
		if (usuario->movimientos[i]<0)
		{
			printf("\n%.2fE\n", usuario->movimientos[i]);
		}
		else if (usuario->movimientos[i]>0)
		{
			printf("\n+%.2fE\n", usuario->movimientos[i]);
		}
 	}
}

void cambiarClave (datosUsuario *usuario){
	char clave_anterior[20], clave_nueva[20];
	printf("\nIntroduzca su clave actual:\n");
		scanf("%s", clave_anterior);
	if (strcmp(clave_anterior, usuario->clave) == 0){
		printf("Introduzca su nueva clave:\n");
			scanf("%s", clave_nueva);
		strcpy(usuario->clave, clave_nueva); // Cambio clave antigua por la nueva
		printf("Su clave se ha cambiado correctamente\n");
	}
	else
		printf("\nClave incorrecta.\n");
}
