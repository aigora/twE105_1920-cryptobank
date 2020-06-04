#include "Libreria.h"

int main()
{
	int menu, op, i, j=0; // j contabiliza la cantidad de usuarios registrados
	float cantidad;
	int salida = 0; // INDICA CUANDO DEBE TERMINAR EL PROGRAMA 
	int intentosUsuario = 5, intentosClave = 5; // VECES QUE PUEDE EQUIVOCARSE EL USUARIO AL INTRODUCIR LOS DATOS
	datosUsuario usuarios[N];
	datosCliente cliente1;
	FILE *pf; //PUNTERO PARA EL FICHERO
	
	pf=fopen("Files/usuarios.txt","r"); //ABRIMOS Y ALMACENAMOS LOS DATOS EN VECTORES DE ESTRUCTURAS PARA MANIPULARLOS
        if(pf==NULL)
		{
            printf("Error al abrir fichero.\n");
            return -1;
        }
        else
		{
            while(fscanf(pf,"%[^;];%[^;];%f\n", &usuarios[j].nombre, &usuarios[j].clave, &usuarios[j].saldo)!=EOF)
                j++; // j al final del while es la cantidad de usuarios registrados
    	}
        fclose(pf); //CERRAMOS EL FICHERO
	
	do
	{
		system("cls");
		printf("\n\n\t- Bienvenido a CryptoBank.\n\n\n");
		printf("\t1) Iniciar sesion\n\t2) Registrarse\n\t3) Salir \n\n\tQue desea hacer? ");
			scanf("%i", &menu);
		switch(menu)
		{
			case 1:
				do
				{
					intentosUsuario--;
					system("cls");
					printf("\n\tIntroduzca su nombre de usuario: ");
						scanf("%s", cliente1.nombre);
					// EL USUARIO EXISTE
                    			for(i=0; i<N; i++)
						if(comprobarUsuario(&cliente1, &usuarios[i]) == 0)
						{	
							do
							{
								intentosClave--;
								system("cls");
								printf("\n\tIntroduzca su clave personal: ");
								scanf("%s", cliente1.clave);
								// LA CLAVE ES CORRECTA
								if(comprobarClave(&cliente1, &usuarios[i]) == 0)
								{ 
									system("cls");
									printf("\n\n\tHola %s, bienvenido a tu area personal.\n", usuarios[i].nombre);
									do
									{
                                    	printf("\n\t1) Retirar efectivo\n\t2) Ingresar efectivo\n\t3) Consultar saldo\n\t4) Consultar movimientos\n\t\
5) Cambiar clave personal \n\t6) Cerrar sesion\n\n\tQue desea hacer? ");
                                    	scanf("%i", &op);
										switch(op)
										{
										case 1:
										//RETIRAR EFECTIVO
											system("cls");
										    retirarEfectivo(&cliente1, &usuarios[i]);
											break;

										case 2:
										//INGRESAR EFECTIVO
											system("cls");
										    ingresarEfectivo(&cliente1, &usuarios[i]);
											break;

										case 3:
										//CONSULTAR SALDO
											system("cls");
										    printf("\n\tDispone actualmente de: %.2fE\n", usuarios[i].saldo);
											printf("\n\n\tEspere 3 segundos para continuar. ");
											sleep(3);
											system("cls");
										    break;
										case 4:
										//CONSULTAR MOVIMIENTOS
											printf("FECHA;HORA;CANTIDAD;SALDO");
											imprimeMovimientos (&usuarios[i]);
										    break;
										case 5:
										//CAMBIAR CLAVE
											system("cls");
											cambiarClave(&usuarios[i]);
											break;
										case 6:
										//CERRAR SESION
											system("cls");
											printf("\n\n\tVuelve pronto %s!\n", usuarios[i].nombre);
											sleep(2);
											break;
										default:
											system("cls");
											printf("Opcion incorrecta");
											sleep(1);
										}
									}while(op!=6);
								}
								else
								{
									system("cls");
									printf("\n\tClave incorrecta. Vuelva a intentarlo.");
									sleep(1);
								}
							}while(comprobarClave(&cliente1, &usuarios[i]) != 0 && intentosClave > 0 && op != 6); // CLAVE INCORRECTA E INTENTOS DISPONIBLES
						}
						else if(op != 6)
						{
							system("cls");
							printf("\n\tUsuario no encontrado. Vuelva a intentarlo.\n");
							sleep(1);
						}
				}while(comprobarUsuario(&cliente1, &usuarios[i]) != 0 && intentosUsuario > 0 && op != 6); // USUARIO INCORRECTO E INTENTOS DISPONIBLES
				break;
                
			case 2:
				system("cls");
				printf("\n\tNombre de usuario: ");
				scanf("%s", cliente1.nombre);
				printf("\n\tClave personal: ");
				scanf("%s", cliente1.clave);
				cliente1.cantidad = 0; // LAS CUENTAS EMPIEZAN A CERO
				crearUsuario(&cliente1, &usuarios[j], pf);
				j++;
				system("cls");
				printf("\nTe has registrado correctamente. Reinicia el programa para que se hagan efectivos los cambios.\n");
				salida = 1;
				sleep(2);
				break;
				
			case 3:
				system("cls");
				printf("\n\n\tHasta pronto!\n\n");
				sleep(1);
				salida = 1; // EL USUARIO DESEA SALIR
				break;
			default:
				printf("\nOpcion incorrecta.\n");
				sleep(2);
		}	
	}while(salida != 1);
	
	actualizarFile1(&usuarios[0], pf);
	
	for(i=1;i<j;i++)
		actualizarFile2 (&usuarios[i], pf);
		
	return 0;
}

