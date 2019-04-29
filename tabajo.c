/*Programa que registra los tiempos de 10 aviones en un aeropuerto, cuyos numeros de vuelo van del 1 al 10.
El menú principal del programa proporciona las siguientes opciones:

1.	Registrar tiempo de aterrizaje de un avion.
2.	Lista de resultados
3.	Clasificación de los aterrizajes y despegues
4.	Tiempo medio de aterrizaje y/o despegue

La opción 1 debe registrar el tiempo de un avion en horas minutos y segundos, indicando su numero de vuelo.
La opción 2 muestra la lista de mejor a peor tiempo.
La opción 3 una tabla con los horarios de aterrizajes y despegues.
La opción 4 indica la media de tiempos de todos los aviones que han finalizado el despegue y/o el aterrizaje


NOTA:
-No todos los aviones tienen por qué llegar a la terminal.
-El menú principal y cada una de las opciones se realizarán mediante funciones separadas.
-El código debe ser fácilmente adaptable a un aeropuerto de un número diferente de vuelos.
-Es obligatorio el uso de vectores de estructuras.
-Es obligatorio el uso de ficheros.  <------------HE PUESTO ASTERISCOS (*) PARA QUE SE VEA DÓNDE LOS HE USADO

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#define NUM_VUELOS 15//Vuelos previstos en un día.
#define OK 0//Defino los valores a devolver por cada una de las funciones
#define ERROR -1//Uso OK y ERROR en lugar de 0 ó 1 pues es mucho más visual




typedef enum//Defino el tipo boolean porque necesito variables y funciones
 {
        FALSE = 0,//que devuelvan un valor que toman solo 2 opciones (0 y 1 normalmente en C)
        TRUE = 1//pero en todos los códigos y lenguajes está la opción de un tipo bool
} bool;//que devuelve true y false

typedef struct{ // Estructura para guardar el tiempo de aterrizaje.
	int horas;//Horas que tarda en aterrizar.
	int minutos;//Minutos que tarda en aterrizar.
	int segundos;//Segundos que tarda en aterrizar.
	int total;//Segundos totales.
}Tiempo;

typedef struct{ //Estructura anidada de cada avión.
	
	int numeroVuelo; //Número propio de cada vuelo
	char compania[50]; //Compañia de vuelo de cada avión.
	Tiempo aterrizaje; //Duración del aterrizaje.
	bool finish; //Sirve para saber si el aterrizaje ya ha terminado.
}Avion;


typedef struct//Estructura del aterrizaje
{
	bool refresh;//Flag para actualizar la clasificación
	int finished;//Número de aviones que han aterrizado
	Avion lista[NUM_VUELOS];//Vector de aviones
	int clasif[NUM_VUELOS];//Vector con posiviones de la tabla de aterrizajes
}Aterrizaje;
		


/*declaración de funciones*/

void inicializaAterrizaje (Aterrizaje *tabla);//!!!!!!!!!!!!!!
int pintaMenu();
int registraAvion(Aterrizaje *tabla, FILE *);//*****
int listaAterrizaje(Avion *tabla);
int ordenarAterrizaje(Aterrizaje *tabla);//*****
int mediaAterrizaje(Avion *tabla, int n);


int main ()
{
	Aterrizaje tablaAterrizaje;//Objeto principal   

int leido=-1; //Variable para el menú
	FILE *pcorref;//***********
	char avionesFile[50], clasificacionFile[50]; //Ficheros para guardar los aviones y la clasificacion ************
	
	printf("Diga el nombre del fichero para guardar los aviones\n");
	
	gets(avionesFile);//Se recoge el nombre del fichero
	
	pcorref = fopen(avionesFile, "a+");//********
	
	

inicializaAterrizaje(&tablaAterrizaje);//Llamo a la función que inicializa los valores

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
			registraAvion(&tablaAterrizaje, pcorref);
           				break;
			case 2://Si se marca 2: se lista panel de estado de vuelos
			listaAterrizaje(tablaAterrizaje.lista);
           				break;
			case 3://Si se marca 3: se muestra la clasificación
			ordenarAterrizaje(&tablaAterrizaje);
            				break;	
			case 4://Si se marca 4: se saca la media
			mediaAterrizaje(tablaAterrizaje.lista, tablaAterrizaje.finished);
    				break;
			default://Cualquier otra opción: no vale
				break;
		}
	}
	fclose(pcorref);//*****
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

int registraAvion(Aterrizaje*tabla, FILE*pcorref)//Función que registra un avión.{


	int numeroVuelo, horas,minutos, segundos;
	char compania[50];
	bool correct=FALSE;

	printf("\n Proceso de registro de un vuelo.\n");
	printf("Indique el numero de vuelo y el tiempo del mismo.\n);
	printf("\t\t Numero de vuelo Horas Minutos Segundos\n\n");
	printf("Por ejemplo:\n");
	printf("\t\t 0000 10 30 10\n");
	
	scanf("%d %d %d %d",&numeroVuelo,&horas,&minutos,&segundos);
	
	while(correct==FALSE)//Control de errores para comprobar que las cosas introducidas están de acuerdo a lo pedido.
	{
		if((numeroVuelo<NUM_VUELOS)&&(numeroVuelo>0) && (horas>=0) && (minutos>=0) && (minutos<=59) && (segundos>=0) && (segundos<=59))
			correct=TRUE;//Se cumplen todas las sentencias.
		else//Seguirá preguntando hasta que los datos estén correctos.
		{
		  
			
		}
		
	
	       
	       

	}




	
