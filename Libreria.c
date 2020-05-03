#include "Libreria.h"

int comprobarUsuario (datosCliente *cliente, datosUsuario *usuario){
	return strcmp(cliente->nombre, usuario->nombre); // SI SON IGUALES DEVUELVE 0
}

int comprobarClave (datosCliente *cliente, datosUsuario *usuario){
	return strcmp(cliente->clave, usuario->clave); // SI SON IGUALES DEVUELVE 0
}

int crearUsuario (datosCliente *cliente, FILE *pf){
    pf=fopen("usuarios.txt","a"); //ABRIMOS Y ESCRIBIMOS EL FICHERO
    if(pf==NULL){
        printf("Error al abrir fichero.\n");
        return -1;
    }
    else
        fprintf(pf,"%s;%s;%.2f\n", cliente->nombre, cliente->clave, cliente->cantidad);
    fclose(pf);
    return 1;
}

int actualizarFile1 (datosUsuario *usuario, FILE *pf){
	pf = fopen("usuarios.txt","w"); // PRIMERO SOBRESCRIBIMOS EL FILE
	if(pf==NULL){
		printf("\nError al abrir el fichero.");
		return -1;
	}
	else
		fprintf(pf,"%s;%s;%.2f\n", usuario->nombre, usuario->clave, usuario->saldo);
	fclose(pf);	
}

int actualizarFile2 (datosUsuario *usuario, FILE *pf){
	pf = fopen("usuarios.txt","a"); // AÑADIMOS 
	if(pf==NULL){
		printf("\nError al abrir el fichero.");
		return -1;
	}
	else
		fprintf(pf,"%s;%s;%.2f\n", usuario->nombre, usuario->clave, usuario->saldo);
	fclose(pf);
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
