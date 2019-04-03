/*Programa que registra los tiempos de 10 aviones en un aeropuerto, cuyos numeros de vuelo van del 1 al 10.
El menú principal del programa proporciona las siguientes opciones:

1.	Registrar tiempo de un avion.
2.	Lista de resultados
3.	Clasificación de los aterrizajes y despegues
4.	Tiempo medio de aterrizaje y/o despegue

La opción 1 debe registrar el tiempo de un avion en horas minutos y segundos, indicando su numero de vuelo.
La opción 2 muestra la lista de mejor a peor tiempo.
La opción 4 indica la media de tiempos de todos los aviones que han finalizado el despegue y/o el aterrizaje

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0//Defino los valores a devolver por cada una de las funciones
#define ERROR -1//Uso OK y ERROR en lugar de 0 ó 1 pues es mucho más visual




typedef enum//Defino el tipo boolean porque necesito variables y funciones
 {
        FALSE = 0,//que devuelvan un valor que toman solo 2 opciones (0 y 1 normalmente en C)
        TRUE = 1//pero en todos los códigos y lenguajes está la opción de un tipo bool
} bool;//que devuelve true y false





/*declaración de funciones*/

int pintaMenu();
int main ()
{
    


int leido=-1; //Variable para el menú


	while (leido!=5)//Mientras no seleccione el 5(salir)
	{
 		leido=pintaMenu();//Sale el menú.
			switch(leido)//Analizo la opción
		{
           case ERROR://Error en la inseción de datos
           printf ("Ha habido un problema.\n");
           system ("pause");
           break;   
			case 1://Si se marca 1: se registra un vuelo
           				break;
			case 2://Si se marca 2: se lista panel de estado de vuelos
           				break;
			case 3://Si se marca 3: se muestra la clasificación
            				break;	
			case 4://Si se marca 4: se saca la media
    				break;
			default://Cualquier otra opción: no vale
				break;
		}
	}
	
	system("PAUSE");
}
	
	
	int pintaMenu()//Función que muestra el menú y captura la opción del usuario
{
	int option=0,cde;
    system("cls");//Para limpiar la pantalla 

	printf("---------------------------------------\n");
	printf("Programa gestion de un aeropuerto:\n");
	printf("\t1. Registrar tiempo de un avion.\n");
	printf("\t2. Panel de aterrizajes y despegues.\n");
	printf("\t3. Clasificacion.\n");
	printf("\t4. Tiempo medio.\n");
	printf("\t5. Salir.\n");
	printf("---------------------------------------\n");
	printf("\nIndique su opcion: ");

	cde=scanf("%d", &option);//Se saca el cursor para que el usuario pueda meter una opción
	

	if (cde==0)//Control de errores
		return ERROR;
	else
		return option;
		
	return OK;     
}
