//HeapMin de vehículos según las prioridades.

#include "Vehiculo.cpp"
#include <vector> 

class HeapMinVehiculos{
    protected:
            vector<Vehiculo*> Vehiculos;	
								
			int indVIP;					//índice al último vehículo (tipo ambulancio o patrullero) insertado de prioridad 1. 
			int capacidad; 				//capacidad predeterminada para el heap en función del número de carriles
											
    public:
            HeapMinVehiculos(int);               //constructor heap vacío
            HeapMinVehiculos(int,Vehiculo*);     //constructor heap con primer elemento
            ~HeapMinVehiculos(void){};           //destructor del heap
            bool insertar(Vehiculo *);  //recibe un Vehiculo y lo inserta en el heap según su prioridad. Retorna true si pudo hacerlo.
            Vehiculo *extraer(); 		//Devuelve el elemento de mayor prioridad y re-construye el heap.
			Vehiculo *first(); 			//Devuelve el primer elemento del heap sin modificarlo.
		
			string print_Archivo();
						                                        
            bool heap_lleno(void) 
            {return Vehiculos.size()==capacidad;};      //devuelve true si el heap está lleno. false si tiene al menos un lugar.
            
            bool heap_vacio(void) 
            {return Vehiculos.empty();};				//devuelve true si el heap está vacío.

			int get_prioridad(int i);					//Retorna la prioridad del elemento i del heap.
			
			int get_cantVehiculos() 
			{return Vehiculos.size();};   				//Retorna la cantidad de elementos que tiene el heap.
			
			int get_capacidad() 
			{return capacidad;};   						//Devuelve la capacidad seteada del heap.
			
			void print(); 			
};

HeapMinVehiculos::HeapMinVehiculos(int capacidad){
	this->capacidad=capacidad;
	indVIP=-1;
}

HeapMinVehiculos::HeapMinVehiculos(int capacidad, Vehiculo *v){
	this->capacidad=capacidad;
	indVIP=-1;
	insertar(v);	
}

Vehiculo *HeapMinVehiculos::first(){
	if(!heap_vacio()) return Vehiculos[0]; 
	else return NULL;
}

bool HeapMinVehiculos::insertar(Vehiculo *nuevo){

	if(heap_lleno()){
		cout<<"No se pudo insertar el Vehiculo matricula nro. "<<nuevo->get_matricula()<<". El semaforo estaba colmado. "<<endl;
		return false;
	}
	else
	{
		if(nuevo->get_prioridad())
		{
			indVIP++;											//incrementa el indice al ultimo vehículo con prioridad 
			Vehiculos.insert(Vehiculos.begin()+indVIP,nuevo);   //Inserto el vehículo en esa posición.
		}
		else
		{
			Vehiculos.push_back(nuevo);		//Agrego el auto al final del vector	
		}
		return true;
	}
}

Vehiculo *HeapMinVehiculos::extraer(){
	if(heap_vacio()){
		cout<<"No se puede extraer Vehiculos de un heap vacio"<<endl;
		return NULL;
	}
	else{
		Vehiculo *cima=Vehiculos.front();			//almaceno el elemento a devolver, para hacerlo al finalizar el metodo
		vector<Vehiculo*> aux=Vehiculos;			//NO se puede hacer la operacion assign sobre el mismo vector
		Vehiculos.assign(aux.begin()+1,aux.end()); 	//Re-asigno los elementos al vector, excepto el primero
		if(indVIP!=-1)indVIP--; 					//Si hay alguna Ambulancia, decremento en uno su indice
		return cima;								//Devuelvo el vehículo extraído
	}
}

int HeapMinVehiculos::get_prioridad(int i)
{	
		if(i>=0 && i<capacidad && i<get_cantVehiculos())
		return Vehiculos.at(i)->get_prioridad();
		else return -1;
}	


void HeapMinVehiculos::print(){
	int pos=0;
	
	if(heap_vacio()) cout<<"El Heap esta vacio"<<endl;
	else{
		cout << endl
		<< setw(15) << setiosflags(ios::left)<< "Tipo " 
		<<"   "
		<< setw(11) << setiosflags(ios::left)<< "Matricula " 
		<<"   "
		<< setw(11) << setiosflags(ios::left)<< "Prioridad ";		
		for(int i=0;i<Vehiculos.size();i++)	Vehiculos.at(i)->printDatos();
		} 
}

string HeapMinVehiculos::print_Archivo(){
	std::ostringstream stm;
	
	if(heap_vacio()) stm<<"El Heap esta vacio"<<endl;
	else{	
		for(int i=0;i<Vehiculos.size();i++){
		if ((Vehiculos.at(i)->get_matricula())==1000)
		{
			stm<<Vehiculos.at(i)->printMiAuto_Archivo();
		}
		}

		} 
	return stm.str();
}
