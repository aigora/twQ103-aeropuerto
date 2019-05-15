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



#define NUM_VUELOS 10//Vuelos previstos en un día.
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
	int clasif[NUM_VUELOS];//Vector con posiciones de la tabla de aterrizajes
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
	return OK;
}
	

void inicializaAterrizaje (Aterrizaje *tabla)//Función que inicializa la estructura del aterrizaje
{
	int i;	
	tabla->refresh=FALSE;//No hay inserciones->no es necesario ordenación si preguntan la clasificación                        
    tabla->finished=0;//Nadie ha acabado->contador de aviones finalizados = 0
	                            
	for (i=0;i<NUM_VUELOS;i++)//Se recorre la lista de vuelos
	{
		tabla->lista[i].numeroVuelo=i+1;//Se sabe el numero de vuelo
		tabla->lista[i].finish=FALSE;//No ha terminado
		tabla->lista[i].aterrizaje.horas=-1;//Tiempo
		tabla->lista[i].aterrizaje.minutos=-1;
		tabla->lista[i].aterrizaje.segundos=-1;
		tabla->lista[i].aterrizaje.total=-1;
		tabla->clasif[i]=0;//Se rellena la lista que llevará el orden
	}
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

int registraAvion(Aterrizaje*tabla, FILE*pcorref)//Función que registra un avión.
{


	int numeroVuelo, horas,minutos, segundos;
	char compania[50];
	bool correct=FALSE;

	printf("\n Proceso de registro de un vuelo.\n");
	printf("Indique el numero de vuelo y el tiempo del mismo.\n");
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
			printf("\tLos datos introducidos presentan algún error por favor intoduzcalos de nuevo.\n");
			scanf("%d %d %d %d",&numeroVuelo,&horas,&minutos,&segundos);
		}
	}

	//Se añade el Avión.
	       
	tabla->refresh=TRUE;//Hay que ir actualizando los aviones que salen y entran, si es que no estaban ya registrados.
	if(tabla->lista[numeroVuelo-1].finish=FALSE)
	tabla->finished++;//Incrementamos el numero de aviones que tenemos.
	       
	getchar( ); 
	printf("Introduzca el nombre de la compania aerea.\n");
	gets(compania);
	
	
//El numero de vuelo siempre estará 1 por encima de la posición del vector
//Es decir: que en la posición 0 del vector, estará almacenado el dorsal 1 

	tabla->lista[numeroVuelo-1].numeroVuelo=numeroVuelo;
	tabla->lista[numeroVuelo-1].finish=TRUE;
	strcpy(tabla->lista[numeroVuelo-1].compania,compania);
	tabla->lista[numeroVuelo-1].aterrizaje.horas=horas;
	tabla->lista[numeroVuelo-1].aterrizaje.minutos=minutos;
	tabla->lista[numeroVuelo-1].aterrizaje.segundos=segundos;
	tabla->lista[numeroVuelo-1].aterrizaje.total=horas*60*60+minutos*60+segundos;//Tiempo en segundos
	fprintf(pcorref,"%d  %d %d %d %d %s", numeroVuelo, 1, horas, minutos, segundos, compania);
  	return OK;     

}


int listaAterrizaje(Avion *tabla)//Función que muestra el estado del vuelo
{
    int i;
    printf("Listado de vuelo:\n");
	printf("\tNumero de vuelo\tTiempo (hh:mm:ss)\n");
	
    for (i=0;i<NUM_VUELOS;i++)//Se recorre la lista mostrando los datos
    {
        if(tabla[i].finish==TRUE)//Si ha finalizado se muestra el tiempo
        printf("\t%d\t%d:%d:%d\n",tabla[i].numeroVuelo,tabla[i].aterrizaje.horas,tabla[i].aterrizaje.minutos,tabla[i].aterrizaje.segundos);
        else//Si no ha finalizado se muestra el mensaje
        printf("\t%d\tNo finalizado.\n",tabla[i].numeroVuelo);
     }
        
       system("pause");
      return OK;    
}
	
	
	
       
int ordenarAterrizaje(Aterrizaje *tabla)//Función que ordena el vector de aviones
{
    int i, j, tam;
    FILE  *pclasif;//  *********************
    char clasificacionFile[50];
    
    fflush(stdin);      
	printf("Diga el nombre del fichero para guardar la clasificacion\n");//Se recoge el nombre del fichero    ***********
    gets(clasificacionFile);//  *****************
   
    pclasif = fopen(clasificacionFile,"w+");//  ********************
    int corrIzq, corrDer;
    int posicionAvion;
    tam=tabla->finished;//Se saca el tamaño de los que han acabado
    
    if(tabla->refresh==TRUE)//Si se ha hecho alguna inserción
    {//Se recrea el vector con las posiciones de los aviones según el ORDEN del NUMERO DE VUELO
    i=0;
    for (j=0;j<NUM_VUELOS;j++)
    {
        if(tabla->lista[j].finish==TRUE && i<tam)
        {
            tabla->clasif[i]=j;
            i++;
        }    
     }
     for (i=1; i<tam; i++)//Ahora se recorre el vector ordenando
     {
         for (j=0 ; j<tam - 1; j++)
         {
             corrIzq=tabla->clasif[j];
             corrDer=tabla->clasif[j+1];
             if (tabla->lista[corrIzq].aterrizaje.total > tabla->lista[corrDer].aterrizaje.total)//Si la posición de al lado es menor, se intercambian posiciones
             {
                   tabla->clasif[j] = corrDer;//Se mete la menor a la izquierda
                   tabla->clasif[j+1] = corrIzq;//Se mete a la derecha el valor que había en la inzquiera
            }
          }  
     }              
   }

printf("Clasificacion de Aterrizaje\n\tPuesto\tNumero de vuelo\tTiempo\tcompania aerea\n");

for(i=0;i<tam;i++)//Ahora se recorre el vector de manera habitual
  
	{
       posicionAvion=tabla->clasif[i];           
       fprintf(pclasif,"%d [%d] %d:%d:%d %s",i+1,tabla->lista[posicionAvion].numeroVuelo,tabla->lista[posicionAvion].aterrizaje.horas,
       tabla->lista[posicionAvion].aterrizaje.minutos,tabla->lista[posicionAvion].aterrizaje.segundos, tabla->lista[posicionAvion].compania); 
	   printf("\t%d \t[%d] \t%d:%d:%d \t%s\n",i+1,tabla->lista[posicionAvion].numeroVuelo, tabla->lista[posicionAvion].aterrizaje.horas,
       tabla->lista[posicionAvion].aterrizaje.minutos,tabla->lista[posicionAvion].aterrizaje.segundos, tabla->lista[posicionAvion].compania);
    }
	
	
    
    fclose(pclasif);//  *********************

system("pause");
}	

	
	
int mediaAterrizaje(Avion *tabla, int n)//Función que calcula la media de los finalizados
{
	float media=0.0;
	int i;
	int hr,sec,min;
    if (n>0)//Si hay algún vuelo que ha finalizado
    {
                 for(i=0;i<NUM_VUELOS;i++)//Se suman todos los segundos totales de los aviones
                 {
                              if(tabla[i].finish==TRUE)
                              media+=tabla[i].aterrizaje.total;
                 }
                 media=media/n;//Se hace la media
                 sec=media;//Se pasan los segundos a horas, minutos y segundos
                 hr = sec / (60*60);//Se sacan las horas que no caben, que está almacenado en un entero.
                 sec %= 60*60;//Resto que ha quedado
                 min = sec / 60;//Minutos completos que se pueden sacar
                 sec %= 60;//Resto, que son los segundos
    }
    else//Si no hay ningún finalizado
    {
             media=0.0;
             hr=0;
             min=0;
             sec=0;
    }
    
	printf("\nMedia del aterrizajen: %d:%d:%d (%d finalizados de %d participantes)\n", hr,min,sec , n, NUM_VUELOS);
	
 system("pause");
	return OK;
}
	
