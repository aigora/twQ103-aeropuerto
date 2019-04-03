/*Programa que registra los tiempos de 10 aviones en un aeropuerto, cuyos numeros de vuelo van del 1 al 10.
El men� principal del programa proporciona las siguientes opciones:

1.	Registrar tiempo de un avion.
2.	Lista de resultados
3.	Clasificaci�n de los aterrizajes y despegues
4.	Tiempo medio de aterrizaje y/o despegue

La opci�n 1 debe registrar el tiempo de un avion en horas minutos y segundos, indicando su numero de vuelo.
La opci�n 2 muestra la lista de mejor a peor tiempo.
La opci�n 4 indica la media de tiempos de todos los aviones que han finalizado el despegue y/o el aterrizaje

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0//Defino los valores a devolver por cada una de las funciones
#define ERROR -1//Uso OK y ERROR en lugar de 0 � 1 pues es mucho m�s visual




typedef enum//Defino el tipo boolean porque necesito variables y funciones
 {
        FALSE = 0,//que devuelvan un valor que toman solo 2 opciones (0 y 1 normalmente en C)
        TRUE = 1//pero en todos los c�digos y lenguajes est� la opci�n de un tipo bool
} bool;//que devuelve true y false





/*declaraci�n de funciones*/

int pintaMenu();
int main ()
{
    


int leido=-1; //Variable para el men�


	while (leido!=5)//Mientras no seleccione el 5(salir)
	{
 		leido=pintaMenu();//Sale el men�.
			switch(leido)//Analizo la opci�n
		{
           case ERROR://Error en la inseci�n de datos
           printf ("Ha habido un problema.\n");
           system ("pause");
           break;   
			case 1://Si se marca 1: se registra un vuelo
           				break;
			case 2://Si se marca 2: se lista panel de estado de vuelos
           				break;
			case 3://Si se marca 3: se muestra la clasificaci�n
            				break;	
			case 4://Si se marca 4: se saca la media
    				break;
			default://Cualquier otra opci�n: no vale
				break;
		}
	}
	
	system("PAUSE");
}
	
	
	int pintaMenu()//Funci�n que muestra el men� y captura la opci�n del usuario
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

	cde=scanf("%d", &option);//Se saca el cursor para que el usuario pueda meter una opci�n
	

	if (cde==0)//Control de errores
		return ERROR;
	else
		return option;
		
	return OK;     
}
