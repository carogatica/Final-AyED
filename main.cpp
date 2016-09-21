#include <iostream>
#include <math.h> 
#include <iomanip>
#include <time.h>     
#include <stdio.h>
#include <stdlib.h> 
#include <fstream>
#include <sstream>
#include <string> 

using namespace std;

#define N 100						
#define ESQ 81			        	
#define SEM 176    	            	

#include "Esquinas-Cola.cpp"
#include "HeapMinVehiculos.cpp"
#include "Semaforos-Lista.cpp" 
#include "Grafo.cpp"

void play(Grafo*,int,int,int,Listasemaforos*);				//Inicia el trafico en la ciudad.
void simulacion(Grafo*,Listasemaforos*,Vehiculo*);			//Simula hasta que MiAuto llega a su posicion final.				
void verde(Semaforo *,Listasemaforos *);					//Se encarga de que N vehiculos crucen de semaforo a semaforo.
void recalculando(Grafo *, Vehiculo *);


int main(void){
	Grafo *ciudad=new Grafo();
	Listasemaforos *Semaforos=new Listasemaforos();
	int posInAuto;
	int posFinAuto;
	int posAcAuto;
	int nAutos,nAmbulancias,nPatrulleros;
	
	cout<<"  BIENVENIDO A LA SIMULACION DE TRAFICO  "<<endl<<endl;
	cout<<"Ingrese la posicion inicial de su auto: ";
	cin>>posInAuto;
	cout<<endl<<"Ingrese la posicion a la que desea llegar: ";
	cin>>posFinAuto;
	
	while(posInAuto<0||posInAuto>=ESQ||posFinAuto<0||posFinAuto>=ESQ)
	{
		cout<<endl<<"La posicion incial o la final no son validas. Por favor ingresar nuevos valores."<<endl;
		cout<<"Ingrese desde donde desea que inicie su auto: ";
		cin>>posInAuto;
		cout<<endl<<"Ingrese el destino que pretende: ";
		cin>>posFinAuto;
	}
	
	cout<<endl<<"Ingrese la cantidad de AUTOS a crear: ";
	cin>>nAutos;
	while (nAutos<0)
	{
		cout<<"Ingreso un numero de autos negativo."<<endl;
		cout<<endl<<"Ingrese la cantidad de AUTOS a crear: ";
		cin>>nAutos;
	}	
	
	cout<<endl<<"Ingrese la cantidad de PATRULLEROS a crear: ";
	cin>>nPatrulleros;
	while (nPatrulleros<0)
	{
		cout<<"Ingreso un numero de patrulleros negativo."<<endl;
		cout<<endl<<"Ingrese la cantidad de PATRULLEROS a crear: ";
		cin>>nPatrulleros;
	}

	cout<<endl<<"Ingrese la cantidad de AMBULANCIAS a crear: ";
	cin>>nAmbulancias;
	while (nAmbulancias<0)
	{
		cout<<"Ingreso un numero de ambulancias negativo."<<endl;
		cout<<endl<<"Ingrese la cantidad de AMBULANCIAS a crear: ";
		cin>>nAmbulancias;
	}


	Vehiculo *miAuto = new Vehiculo(1000,posInAuto,posFinAuto);      
	
	ciudad->armarCiudad(Semaforos);
	
	play(ciudad,nAutos,nPatrulleros,nAmbulancias,Semaforos);
	
	simulacion(ciudad,Semaforos,miAuto);

	return 0;
}

void play(Grafo *city, int nAutos, int nPatrulleros, int nAmbulancias,Listasemaforos* S)
{
	Nodosemaforo *nodo;
	Semaforo *semAux;
	int capacidadCiudad=0;
	
	nodo = S->get_czo();
	while(nodo!=NULL){
		semAux = nodo->get_dato();
		capacidadCiudad+=semAux->get_capacidad_cola();
		nodo = nodo->get_next();
	}
	cout<<endl<<"Cantidad de vehiculos que pueden circular por la ciudad: "<<capacidadCiudad<<endl;
	cout<<"Cantidad de vehiculos que se quieren crear: "<<nAutos+nPatrulleros+nAmbulancias<<endl;
	
	if(capacidadCiudad>nAutos+nPatrulleros+nAmbulancias)  // Comprueba que los vehiculos a crear sean menos que la capacidad de la ciudad.
	{
		for(int i=0;i<nAutos;i++){
			Vehiculo *a=new Vehiculo("Auto");
			S->ubicarAleatorio(a);
			a->set_camino(city->dijkstra(a->get_posInicial(),a->get_posFinal()));
		}
		
		for(int i=0;i<nPatrulleros;i++){
			Vehiculo *p=new Vehiculo("Patrullero");
			S->ubicarAleatorio(p);
			p->set_camino(city->dijkstra(p->get_posInicial(),p->get_posFinal()));
		}
		
		for(int i=0;i<nAmbulancias;i++){
			Vehiculo *am=new Vehiculo("Ambulancia");
			S->ubicarAleatorio(am);
			am->set_camino(city->dijkstra(am->get_posInicial(),am->get_posFinal()));
		}
		S->ordenar();
		city->actualizarMA(S);
	}
	else {
		cout<<endl<<"No se puede generar tantos vehiculos. Prube con una cantidad menor"<<endl;
		cout<<"           y vuelva a iniciar la simulacion."<<endl;
		exit(1);
	}
}


void simulacion(Grafo *ciudad,Listasemaforos *Semaforos,Vehiculo *miAuto)
{
	Nodosemaforo *nodo;
	Semaforo *semAux;
	int iteracion=0;
	string p;
		
	Semaforos->ubicarMiAuto(miAuto);
	miAuto->set_camino(ciudad->dijkstra(miAuto->get_posInicial(),miAuto->get_posFinal()));
	Semaforos->ordenar();
	
	cout<<endl<<"Estado inicial de miAuto:"<<endl;
	miAuto->printMiAuto();
	
	ostringstream os;
	os << "Inicio de la simulacion"<<endl;
    os << "------------------------Iteracion Nro: " << iteracion << "-------------------------------" << endl;
    p = os.str();
	
	Semaforos->toPrint(p,iteracion);		

	while(miAuto->get_posActual()!=miAuto->get_posFinal())
	{

		nodo = Semaforos->get_czo();
		iteracion++;

		while(nodo!=NULL){
			semAux = nodo->get_dato();
			verde(semAux,Semaforos);
			nodo = nodo->get_next();
		}
		Semaforos->ordenar();
		
		cout<<endl<<"------------------------Iteracion Nro: " << iteracion << "-------------------------------" << endl;
		miAuto->printMiAuto();
		
		os.str(""); os.clear();
		os << endl<<endl<<"------------------------Iteracion Nro: " << iteracion << "-------------------------------" << endl;
		p = os.str();
		Semaforos->toPrint(p,iteracion);
		
		if((iteracion%2)==0&&(miAuto->get_posActual()!=miAuto->get_posFinal())){	//Recalculo el recorrido de mi auto cada 2 iteraciones
		//	cout<<"Recalculando..."<<endl;
			ciudad->actualizarMA(Semaforos);
			recalculando(ciudad,miAuto);
		}
	}
	
	Semaforos->toPrint("\n\nUltima Iteracion \n",iteracion);
}


void verde(Semaforo *semActual,Listasemaforos *S)
{	
	Vehiculo *vehiculo;				//Puntero con el que se manejan los diferentes vehiculos 	
	Semaforo *nextSemaforo;			//Puntero al semaforo al que intenta dirigirse "vehiculo"
	HeapMinVehiculos *colaSem;		//Variable para almacenar un puntereo a la cola del Semaforo actual.
	
	int nextEsq =-1;				//Entero de referencia al proximo nodo del grafo al que quiero moverme
	semActual->resetCont();			//Resetamos el contador del semaforo a 0.
	semActual->desbloquear();	
	
	colaSem = semActual->get_ColaDelSemaforo();
	
	if(colaSem->heap_vacio()||colaSem == NULL){ 	//Si la cola del semaforo no existe o esta vacia:
	semActual->bloquear();							//el semaforo se bloquea para que la simulacion continue.
	} 						

	while((semActual->getContador())<N*(semActual->get_carriles())&&(!semActual->bloqueado())) 
	{	
		vehiculo=colaSem->first(); //Tomo el primer vehiculo de la cola del semaforo
		
		if(vehiculo!=NULL && vehiculo->circulando()){

			if(vehiculo->get_posActual()==vehiculo->get_posInicial()){  //Si todavia no se movio del origen: Primer movimiento
				vehiculo->put_recorrido(vehiculo->get_siguiente()); 	//Cargo el primer elemento (cabeza) en la cola de vertices recorrido
				vehiculo->borrar_cabeza(); 								//borro el primer cabeza para no perder una iteracion 
			}
			
			if(vehiculo->get_posActual()==vehiculo->get_siguiente()){ 	//Si entra aca es porque recalculo dijkstra, y este devuelve la ruta completa, en vez de lo que le falta para destino.
				vehiculo->borrar_cabeza();				
			}
			
			nextEsq=vehiculo->get_siguiente();

			if(nextEsq>=0) {
				nextSemaforo=S->buscar(nextEsq,semActual->get_nroEsquina()); //S->buscar(esquina siguiente, nro de esquina del semaforo)
				
				if(nextSemaforo!=NULL){ 
					if(nextSemaforo->cruzar(vehiculo)){  //Si hay lugar en el siguiente semaforo se encola el vehiculo
						vehiculo = colaSem->extraer(); //Extraigo el vehiculo del semaforo actual
						vehiculo->set_posActual(nextSemaforo->get_nroEsquina());
						vehiculo->put_recorrido(vehiculo->get_siguiente()); //Cargo el elemento en la cola de vertices recorridos
						vehiculo->borrar_cabeza(); //Borro el salto que ya hizo el vehiculo en su camino.
						semActual->incrementarCont();
					}
					else semActual->bloquear(); //El semaforo se bloquea porque rojo devolvio 'false'
				}
				else semActual->bloquear(); //El semaforo estaba lleno
			}
			else semActual->bloquear(); 
		}
		else {
			semActual->bloquear(); //El vehiculo no existe o ya llego a destino
			if(vehiculo != NULL) colaSem->extraer();
		}	
	}
}

void recalculando(Grafo *city, Vehiculo *miAuto)
{
	ColaEsquinas *nuevoCamino;
	nuevoCamino = city->dijkstra(miAuto->get_posActual(),miAuto->get_posFinal());
	cout<<"El nuevo camino es: ";
	nuevoCamino->print();
	cout<<endl;
	miAuto->set_camino(nuevoCamino);
}


