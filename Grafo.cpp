
#include <limits>
#include "HeapMinEsquinas.cpp"

int inf = std::numeric_limits<int>::max();

class Grafo{
	private:
		int MA[ESQ][ESQ];		                //Matriz de Adyacencia del Grafo que representa la ciudad.
		HeapMinEsquinas *colaPrioridad;			//Cola de prioridad (peso) donde almaceno temporalmente nodos adyacentes para trabajarlos. 
		ColaEsquinas *ColaE;					//Cola de vertices que voy a retornar como resultado del algoritmo, 
											//con el camino óptimo de 'posInicial' a 'posFinal'
		int distancia[ ESQ ];      	//distancia[ u ] distancia de la esquina inicial a la u
		bool visitados[ ESQ ];      		
		int previo[ ESQ ];         
		
		void inicio();						//Inicializa los valores de las estructuras de datos usadas en dijkstra()
		void actualizarDist( int,int,int);		//Actualiza distancias[i] haciendo el acumulado de distancias desde el origen
		void ruta( int);					//Almacena en ColaE* la ruta optima a seguir desde la posicion inicial a la final
	public:
		Grafo(){}; 
		void armarCiudad(Listasemaforos*);		//Inicializa la "ciudad" leyendo la config. desde un archivo.
		ColaEsquinas* dijkstra( int, int);	//Algoritmo de Dijkstra. Recibe la posicion inicial y final y retorna la ruta óptima 
		void actualizarMA(Listasemaforos*);	//Recibe la lista de semaforos y actualiza los pesos de los arcos del grafo según la
											//congestión de cada semáforo. 
											
		void print();
	
};


/*
 * Este método lee un archivo que contiene la configuración de la ciudad y carga esos datos en memoria en la matriz de adyacencia
 * MA. Si no hay camino, se setea como "infinito" el peso de la arista correspondiente.
*/
void Grafo::armarCiudad(Listasemaforos* s)
{     
  	
    FILE *ciudad;
    ciudad = fopen("plano.txt", "r");
    int dato = fgetc(ciudad);
    
    if (ciudad==NULL)
    {
    	cout<<"No se pudo abrir el archivo exitosamente."<<endl;
    	exit(1);
	}

    for(int i=0 ; i<ESQ ; i++){
        for(int j=0 ; j<ESQ ; dato = fgetc(ciudad)) 				
        {	
        	switch(dato){
        		case 48:			
        			MA[i][j] = 0;
					j++;
					break;
				case 49:			
					MA[i][j] = 1;
					s->insertar(new Semaforo(1,j,i)); 
					j++;
					break;
				case 50:			
					MA[i][j] = 1;
					s->insertar(new Semaforo(2,j,i));
					j++;
					break;
				case 51:			
					MA[i][j] = 1;
					s->insertar(new Semaforo(3,j,i));
					j++;
					break;
				case 57:
					MA[i][j] = inf;
					j++;
					break;
				case 10:
					break;
				default:
					cout<<endl<<"Se encontro en el archivo un dato no valido"<<endl;
					exit(1);
			}
        }
    }
    fclose(ciudad);
  
}

//función de inicialización de variables para usar en dijkstra()
void Grafo::inicio()
{
	if(colaPrioridad != NULL) delete colaPrioridad;
	if(ColaE!= NULL) delete ColaE;
	
	colaPrioridad=new HeapMinEsquinas();	
	ColaE=new ColaEsquinas();	
	
    for( int i = 0 ; i <ESQ ; ++i ){
        distancia[ i ] = inf; 
        visitados[ i ] = false; 
        previo[ i ] = -1;      
    }
}

//Paso de actualizar distancia
//entre todos los vértices adyacentes, buscamos el que esté más cerca de nuestro punto origen, lo tomamos como punto intermedio
// y vemos si podemos llegar más rápido a través de este vértice a los demás. Después escogemos al siguiente más cercano 
//(con las distancias ya actualizadas) y repetimos el proceso. 
void Grafo::actualizarDist( int actual , int adyacente , int peso ){
    //Si la distancia del origen a la esquina actual + el peso de su arista es menor a la distancia del origen a la esquina adyacente
    if( distancia[ actual ] + peso < distancia[ adyacente ] ){
        distancia[ adyacente ] = distancia[ actual ] + peso;  //relajamos el vertice actualizando la distancia
        previo[ adyacente ] = actual;                         //a su vez actualizamos el vertice previo
        colaPrioridad->insertar( new Esquina(adyacente,distancia[adyacente])); //agregamos adyacente a la cola de prioridad
    }
}

void Grafo::ruta( int dest){
    if( previo[ dest ] != -1 )    		//si aun poseo una esquina previa
        ruta( previo[ dest ]);  		//uso recursividad 
    ColaE->agregar(dest);      				//terminada la recursion, agrego los elementos a la cola de esquinas
}


ColaEsquinas* Grafo::dijkstra( int origen,  int destino)
{											
    inicio(); 											//inicializamos los arreglos
    
    colaPrioridad->insertar( new Esquina(origen,inf)); 			//Insertamos la esquina inicial en la Cola de Prioridad (si ponemos 0 se queda en varias iteraciones en 
    															//la misma calle)
    distancia[ origen ] = 0;      						//Este paso es importante, inicializamos la distancia del inicial como 0
    int actual , adyacente , peso;
    while( !colaPrioridad->empty() ){                   	//Mientras cola no este vacia
        actual = colaPrioridad->extraer()->get_dato();      //Obtengo de la cola el nodo con menor peso, en un comienzo será el inicial. Elimino el elemento de la cola.
        if( visitados[ actual ] ) continue; 			//Si el vértice actual ya fue visitados entonces sigo sacando elementos de la cola
        visitados[ actual ] = true;         			//Marco como visitados el vértice actual

        for( int j = 0 ; j <ESQ ; j++ ){ 			//reviso sus adyacentes del vertice actual; fila[actual] de MA
            if(MA[actual][j]>0 && MA[actual][j]<inf){ 		//Si es 0 es el elemento actual, si es inf no hay arco.
            	adyacente = j;   							//id del vertice adyacente 	
            	peso = MA[actual][j];        				//peso de la arista que une actual con adyacente ( actual , adyacente )
            	if( !visitados[ adyacente ] ){        		//si el vertice adyacente no fue visitados
					actualizarDist( actual , adyacente , peso ); 	//realizamos el paso de relajacion
            	}
			}   
        }
    }
	ruta(destino);
	
	return ColaE;
    
}

void Grafo::actualizarMA(Listasemaforos *S)
{	
	Nodosemaforo *nodo = S->get_czo();
	Semaforo *aux=NULL;

	while(nodo!=NULL)
	{
		aux = nodo->get_dato();
		if(aux->congestion()!= 0) MA[aux->get_EsqAnterior()][aux->get_nroEsquina()]=aux->congestion(); 
		nodo = nodo->get_next();
		
	}	
		
}


void Grafo::print()
{
	cout<<"La Matriz de Adyacencia del grafo es:"<<endl<<endl;
//	int inf = std::numeric_limits<int>::max();
	for(int i=0;i<ESQ;i++){
		for(int j=0;j<ESQ;j++) {
			if(MA[i][j]==inf) cout<<setw(5)<<setiosflags(ios::internal)<<"inf";
			else {
				
				cout<<setw(5)<<setiosflags(ios::internal)<<MA[i][j];
			}
		}
		cout<<endl;
	}	
	
	system ("pause");
}

