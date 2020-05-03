#include <stdio.h>
#include "Libreria.h"

int main(){
	int menu, op, j=0;
    float cantidad;
	int salida = 0; // INDICA CUANDO DEBE TERMINAR EL PROGRAMA 
	int intentosUsuario = 5, intentosClave = 5; // VECES QUE PUEDE EQUIVOCARSE EL USUARIO AL INTRODUCIR LOS DATOS
	datosUsuario usuarios[N];
	datosCliente cliente1;
    FILE *pf; //PUNTERO PARA EL FICHERO
	
	do{
		printf("\n\n - Bienvenido a CryptoBank.\n\n");
		printf("\t1) Iniciar sesion\n\t2) Registrarse\n\t3) Salir \n\t");
			scanf("%i", &menu);
		switch(menu){
			case 1:
                pf=fopen("usuarios.txt","r"); //ABRIMOS Y LEEMOS EL FICHERO
                if(pf==NULL)
                {
                    printf("Error al abrir fichero.\n");
                    return -1;
                }
                else
                {
                    while(fscanf(pf,"%[^;];%[^;];%f  \n", &usuarios[j].nombre, &usuarios[j].clave, &usuarios[j].saldo)!=EOF)
                    {
                        j++;
                    }
                }
                fclose(pf); //CERRAMOS EL FICHERO
                
				do{
					intentosUsuario--;
					printf("\nIntroduce tu nombre de usuario: ");
						scanf("%s", cliente1.nombre);
					// EL USUARIO EXISTE
                    for(j=0; j<N; j++)
					if(comprobarUsuario(&cliente1, &usuarios[j]) == 0){
                        system("cls");
						do{
							intentosClave--;
							printf("\nIntroduce tu clave personal: ");
							scanf("%s", cliente1.clave);
							// LA CLAVE ES CORRECTA
							if(comprobarClave(&cliente1, &usuarios[j]) == 0){ 
								system("cls");
								printf("\n\nHola %s, bienvenido a tu area personal.\n", usuarios[j].nombre);
								do{
                                    printf("\n\t1) Retirar efectivo\n\t2) Ingresar efectivo\n\t3) Consultar saldo\n\t4) Consultar movimientos\n\t\
5) Cambiar clave personal \n\t6) Cerrar sesion\n\t");
                                    scanf("%i", &op);
                                    switch(op){
                                        case 1:
                                        //RETIRAR EFECTIVO
                                            retirarEfectivo(&cliente1, &usuarios[j]);
                                        break;
                                        
                                        case 2:
                                        //INGRESAR EFECTIVO
                                            ingresarEfectivo(&cliente1, &usuarios[j]);
                                        break;
                                        
                                        case 3:
                                        //CONSULTAR SALDO
                                        	system("cls");
                                            printf("\nDispone actualmente de: %.2fE", usuarios[j].saldo);
                                            break;
                                        case 4:
                                        //CONSULTAR MOVIMIENTOS
                                        	imprimeMovimientos (&usuarios[j]);
                                            break;
										case 5:
										//CAMBIAR CLAVE
											cambiarClave(&usuarios[j]);
										case 6:
										//CERRAR SESION
											system("cls");
											break;
                                    }
                                }while(op!=6);
							}
							else{
								system("cls");
								printf("\n\tClave incorrecta. Vuelva a intentarlo.\n");
							}
								
						}while(comprobarClave(&cliente1, &usuarios[j]) != 0 && intentosClave > 0); // CLAVE INCORRECTA E INTENTOS DISPONIBLES
					}
					else if(op != 6){
						system("cls");
						printf("\n\tUsuario no encontrado. Vuelva a intentarlo.\n");
					}
				}while(comprobarUsuario(&cliente1, &usuarios[j]) != 0 && intentosUsuario > 0 && op != 6); // USUARIO INCORRECTO E INTENTOS DISPONIBLES
					
				break;
                
			case 2:
                printf("\nNombre: ");
                scanf("%s", cliente1.nombre);
                printf("\nClave: ");
                scanf("%s", cliente1.clave);
                printf("\nSaldo: ");
                scanf("%f", &cliente1.cantidad);
                pf=fopen("usuarios.txt","a"); //ABRIMOS Y ESCRIBIMOS EL FICHERO
                if(pf==NULL)
                {
                    printf("Error al abrir fichero.\n");
                    return -1;
                }
                else
                {
                    fprintf(pf,"%s;%s;%.2f  \n", cliente1.nombre, cliente1.clave, cliente1.cantidad);
                }
                fclose(pf); //CERRAMOS EL FICHERO
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

