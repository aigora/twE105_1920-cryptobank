#include <stdio.h>
#include <string.h>

int comprobarUsuario (char cliente[], char usuario[]);
int comprobarClave (char claveCliente[], char claveUsuario[]);

typedef struct{ // DATOS DE CLIENTES GUARDADOS
	char usuario[20];
	char clave[20];
	double saldo;
}datosUsuario;

typedef struct{ // DATOS DE CLIENTES NUEVOS
	char usuario[20];
	char clave[20];
}datosCliente;

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
					printf("\n\n\tIntroduce tu nombre de usuario: ");
						scanf("%s", cliente1.usuario);
					// EL USUARIO EXISTE	
					if(comprobarUsuario(usuario1.usuario, cliente1.usuario) == 0){ 
						printf("\n\tHola %s!",usuario1.usuario);
						do{
							intentosClave--;
							printf("\n\n\tIntroduce tu clave personal: ");
							scanf("%s", cliente1.clave);
							// LA CLAVE ES CORRECTA
							if(comprobarClave(usuario1.clave, cliente1.clave) == 0){ 
								printf("\n\tHola %s, bienvenido a tu area personal.", usuario1.usuario);
								do{
                                    printf("\n\n\t\t1) Retirar efectivo\n\t\t2) Ingresar efectivo\n\t\t3) Consultar saldo\n\t\t4) Consultar movimientos\n\t\t5) Cambiar pin \n\t");
                                    scanf("%i", &op);
                                    switch(op){
                                        case 1:
                                        //RETIRAR EFECTIVO
                                            printf("\nIntroducir cantidad a retirar: ");
                                            scanf("%f", &cantidad);
                                            if(cantidad<= usuario1.saldo){
                                                //retirar la cntidad del saldo 
                                                printf("\nRetirada de %.2f E realizada correctamente", cantidad);
                                                usuario1.saldo = usuario1.saldo - cantidad;
                                                printf("\nDispone de: %.2f", usuario1.saldo);
                                            }else
                                                printf("\nNo dipone de la cantidad introducida");
                                        break;
                                        
                                        case 2:
                                        //INGRESAR EFECTIVO
                                            printf("\nIntroducir la cantidad a introducir: ");
                                            scanf("%f", &cantidad);
                                            printf("\nIngreso de %.2f E realizado correctamente", cantidad);
                                            usuario1.saldo = usuario1.saldo + cantidad;
                                            printf("\nDispone de: %.2f", usuario1.saldo);
                                        break;
                                        
                                        case 3:
                                        //CONSULTAR SALDO
                                            printf("\nDispone de: %.2f", usuario1.saldo);
                                            break;
                                            
                                            
                                    }
                                }while(op!=6);
							}
							else{
								printf("\n\tClave incorrecta. Vuelva a intentarlo.");
								//system("cls");
							}
								
						}while(comprobarClave(usuario1.clave, cliente1.clave) != 0 && intentosClave > 0); // CLAVE INCORRECTA E INTENTOS DISPONIBLES
					}
					else{
						printf("\n\tUsuario no encontrado. Vuelva a intentarlo.");
						//system("cls");
					}
				}while(comprobarUsuario(usuario1.usuario, cliente1.usuario) != 0 && intentosUsuario > 0); // USUARIO INCORRECTO E INTENTOS DISPONIBLES
					
				
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

int comprobarUsuario (char cliente[], char usuario[]){
	return strcmp(cliente, usuario); // SI SON IGUALES DEVUELVE 0
}
int comprobarClave (char claveCliente[], char claveUsuario[]){
	return strcmp(claveCliente, claveUsuario); // SI SON IGUALES DEVUELVE 0
}


