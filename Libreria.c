#include "Libreria.h"

void fechayhora(datosMovimientos *movimientos)
{
	time_t t;
	struct tm *tm;
	char fecha[10] = {0}, hora[5] = {0}, fechayhora[16] = {0};
	t = time(NULL);
	tm = localtime(&t);
	strftime(fecha, 11, "%d/%m/%Y", tm);
	strftime(hora, 6, "%H:%M", tm);
	strcat(fechayhora, fecha);
	strcat(fechayhora, ";");
	strcat(fechayhora, hora);
	strcpy(movimientos->fechayhora,fechayhora);
}

int comprobarUsuario (datosCliente *cliente, datosUsuario *usuario)
{
	return strcmp(cliente->nombre, usuario->nombre); // SI SON IGUALES DEVUELVE 0
}

int comprobarClave (datosCliente *cliente, datosUsuario *usuario)
{
	return strcmp(cliente->clave, usuario->clave); // SI SON IGUALES DEVUELVE 0
}

void crearUsuario (datosCliente *cliente, datosUsuario *usuario, FILE *pf)
{
    strcpy(usuario->nombre,cliente->nombre);
    strcpy(usuario->clave,cliente->clave);
    usuario->saldo = cliente->cantidad;
    FILE *pf2;
	char ruta[] = "Files/Movimientos/";
	char nombre_usuario[20];
	strcpy(nombre_usuario,cliente->nombre);
	strcat(ruta, nombre_usuario);
	strcat(ruta, ".txt");
	
	pf2 = fopen(ruta,"w");
	if(pf2==NULL)
	{
        printf("Error al abrir fichero.\n");
    }
    
    fclose(pf);
}

int actualizarFile1 (datosUsuario *usuario, FILE *pf)
{
	pf = fopen("c:Files/usuarios.txt","w"); // PRIMERO SOBRESCRIBIMOS EL FILE
	if(pf==NULL)
	{
		printf("\nError al abrir el fichero.");
		return -1;
	}
	else
		fprintf(pf,"%s;%s;%.2f\n", usuario->nombre, usuario->clave, usuario->saldo);
	fclose(pf);	
}

int actualizarFile2 (datosUsuario *usuario, FILE *pf)
{
	pf = fopen("c:Files/usuarios.txt","a"); // AÑADIMOS 
	if(pf==NULL)
	{
		printf("\nError al abrir el fichero.");
		return -1;
	}
	else
		fprintf(pf,"%s;%s;%.2f\n", usuario->nombre, usuario->clave, usuario->saldo);
	fclose(pf);
}

int retirarEfectivo (datosCliente *cliente, datosUsuario *usuario)
{
	int i, operacion_valida = 0;
	do
	{
		printf("\n\tIntroducir cantidad a retirar: ");
        scanf("%f", &cliente->cantidad);
        if(cliente->cantidad <= usuario->saldo)
		{
        	operacion_valida = 1;
        	system("cls");
            printf("\n\tRetirada de %.2f E realizada correctamente.\n", cliente->cantidad);
            usuario->saldo -= cliente->cantidad;
			usuario->movimientos->cantidad = -cliente->cantidad;
            printf("\n\tDispone actualmente de: %.2f E.\n", usuario->saldo);
            printf("\n\n\tEspere 3 segundos para continuar. ");
			sleep(3);
			system("cls");
            		
            fechayhora(usuario->movimientos);
            FILE *pf;
			char ruta[] = "Files/Movimientos/";
			char nombre_usuario[20];
			strcpy(nombre_usuario,usuario->nombre);
			strcat(ruta, nombre_usuario);
			strcat(ruta, ".txt");
			pf = fopen(ruta,"a");
			if(pf==NULL)
			{
				printf("Error al abrir fichero.\n");
				return -1;
    		}
			else
				fprintf(pf,"%s;%.2f;%.2f\n", usuario->movimientos->fechayhora, usuario->movimientos->cantidad, usuario->saldo);
				
			 fclose(pf);
        }
		else
		{ //No hay dinero suficiente
        	system("cls");
        	printf("\nNo dipone de la cantidad introducida. Introduzca un importe valido.\n\n");
    	}
	}while(operacion_valida != 1);
}

int ingresarEfectivo (datosCliente *cliente, datosUsuario *usuario)
{
	int i;
	printf("\n\tIntroducir cantidad a ingresar: ");
    	scanf("%f", &cliente->cantidad);
    	system("cls");
    	printf("\n\tIngreso de %.2f E realizado correctamente.\n", cliente->cantidad);
    	usuario->saldo += cliente->cantidad;
		usuario->movimientos->cantidad = cliente->cantidad;
		printf("\n\tDispone actualmente de: %.2f E.\n", usuario->saldo);
		printf("\n\n\tEspere 3 segundos para continuar. ");
		sleep(3);
		system("cls");
		
		fechayhora(usuario->movimientos);
		FILE *pf;
		char ruta[] = "Files/Movimientos/";
		char nombre_usuario[20];
		strcpy(nombre_usuario,usuario->nombre);
		strcat(ruta, nombre_usuario);
		strcat(ruta, ".txt");
		pf = fopen(ruta,"a");
		if(pf==NULL)
		{
			printf("\nError al abrir fichero.\n");
			return -1;
    	}
    	else
    		fprintf(pf,"%s;%.2f;%.2f\n", usuario->movimientos->fechayhora, usuario->movimientos->cantidad, usuario->saldo);
    		
   		fclose(pf);
}

int imprimeMovimientos (datosUsuario *usuario)
{
	FILE *pf;
	char linea[40];
	char ruta[] = "Files/Movimientos/";
	char nombre_usuario[20];
	strcpy(nombre_usuario,usuario->nombre);
	strcat(ruta, nombre_usuario);
	strcat(ruta, ".txt");
	pf = fopen(ruta, "r");
	if (pf == NULL)
	{
		printf("\nError al abrir el fichero.\n");
		return -1;
	}
	else 
	{
		system("cls");
		printf("\n\tFECHA;HORA;CANTIDAD;SALDO\n\n\n");
    	while (fgets(linea, 40, (FILE*) pf))
			printf("\t%s\n", linea);
		printf("\n\n\tEspere 5 segundos para continuar. ");
		sleep(5);
		system("cls");	
    }
    fclose(pf);
	return 0;
}

void cambiarClave (datosUsuario *usuario)
{
	char clave_anterior[20], clave_nueva[20];
	printf("\n\tIntroduzca su clave actual: ");
		scanf("%s", clave_anterior);
	if (strcmp(clave_anterior, usuario->clave) == 0)
	{
		system("cls");
		printf("\n\tIntroduzca su nueva clave: ");
			scanf("%s", clave_nueva);
		strcpy(usuario->clave, clave_nueva); // Cambio clave antigua por la nueva
		printf("\n\tSu clave ha sido cambiada correctamente.");
		printf("\n\n\tEspere 3 segundos para continuar. ");
		sleep(3);
		system("cls");
	}
	else
		printf("\nClave incorrecta.\n");
}


