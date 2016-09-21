/*
* HeapMin de Esquinas. 
* Se usa como cola de prioridad para utilizar en el algoritmo de dijkstra.
* El esquina adyacente con el menor peso ocupa la cima del heap.
*/
class HeapMinEsquinas{
    protected:
            Esquina *Esquinas[ESQ];											
            int ptr;					//puntero (índice) al último elemento insertado. (-1) cuando está vacío. 
										
			int hDer(int);				//Mediante aritmética de índices devuelven el respectivo "pariente" del indice del argumento
			int hIzq(int);
			int padre(int);  
			bool esHijoDer(int);
			void swap(int, int);		//intercambia dos elementos del arreglo. Recibe sus indices como argumentos.      

    public:
            HeapMinEsquinas();                                   				//constructor heap vacío
            HeapMinEsquinas(Esquina*);                      					//constructor heap con primer elemento
            ~HeapMinEsquinas(void){};                                           //destructor del heap
            bool insertar(Esquina *);              					//recibe un Vehiculo y lo inserta en el heap según su prioridad. Devuelve true si pudo hacerlo.
            Esquina *extraer(); 										//Devuelve el elemento de mayor prioridad y re-construye el heap.  
			                                        
            bool heap_lleno(void) {return ptr==(ESQ-1);};              //devuelve 1 si el heap está lleno. 0 si tiene al menos un lugar.
            bool empty(void) {return ptr==-1;};
			Esquina *get_cima(void) {return Esquinas[0];};  
			void print_heap();  
			            
					
};

HeapMinEsquinas::HeapMinEsquinas(){
	for(int i=0;i<ESQ;i++) Esquinas[i]=NULL;
	ptr=-1; 
}

HeapMinEsquinas::HeapMinEsquinas(Esquina *n){

	for(int i=0;i<ESQ;i++) Esquinas[i]=NULL;
	ptr=-1;		
	insertar(n);
	
}

int HeapMinEsquinas::hDer(int i){
	if(2*i+2<ESQ && i>=0) return 2*i+2;
	else return i;
}
int HeapMinEsquinas::hIzq(int i){
	if(2*i+1<ESQ && i>=0) return 2*i+1;
	else return i;
}
int HeapMinEsquinas::padre(int i){
	if(floor((i-1)/2)<ESQ && i>=0)return floor((i-1)/2);
	else return i;
}              

bool HeapMinEsquinas::esHijoDer(int i){
	float parteDec;
	
	parteDec=(i-1)/2;
	parteDec=parteDec-(int)parteDec;
	
	if(parteDec>0)return true;
	else return false;
}  

void HeapMinEsquinas::swap(int a,int b){
	Esquina *aux;
	
	aux=Esquinas[a];
	Esquinas[a]=Esquinas[b];
	Esquinas[b]=aux;
}

bool HeapMinEsquinas::insertar(Esquina *nuevo){
	int posActual;
	if(heap_lleno()){
		return false;
	}
	else{
		ptr++;		//Incremento el puntero que indica donde está el último elemento en el array
		Esquinas[ptr]=nuevo; 		//Almaceno en esa posicion del array la nueva esquina
		posActual=ptr;			//Guardo en una variable auxiliar el puntero de la posición en el array del Nodo que acabo de guardar	//posición actual del Nodo insertado.
		while(Esquinas[posActual]->get_peso()<Esquinas[padre(posActual)]->get_peso()){ //Mientras la prioridad del Nodo ingresado sea mayor a la de su padre, intercambiar estos y volver a preguntar
			if(esHijoDer(posActual)){			//Si es hijo derecho, hago un doble swap triangular
				swap(posActual,padre(posActual));
				swap(posActual,posActual-1); //hermano izquierdo
				posActual=padre(posActual);		
			}
			else{									//Si es hijo izquierdo, simplemente cambio padre con hijo
 				swap(posActual,padre(posActual));  									
				posActual=padre(posActual);	
			}			
		}
		return true;
	}	
}

Esquina *HeapMinEsquinas::extraer(){
	if(empty()){
		cout<<"No hay Esquinas por extraer"<<endl;
		return NULL;
	}
	else{
		Esquina *cima=Esquinas[0];			//almaceno el elemento a devolver, para hacerlo al finalizar el metodo
		for(int i=0;i<=ptr;i++){
			Esquinas[i]=Esquinas[i+1];
		}
		ptr--;
		return cima;
	}
}

void HeapMinEsquinas::print_heap(){
	if(empty()) cout<<"El Heap esta vacio"<<endl;
	else{
		cout<<"EsquinaS ALMACENADOS EN EL HEAP :"<<endl;
		for(int i=0;i<=ptr;i++)	Esquinas[i]->print();
	}
}
