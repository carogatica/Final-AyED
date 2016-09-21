class Calle
{
	private:
		HeapMinVehiculos *cola;
		int carriles;
		
	public:
		Calle(int );
		int nCarriles(){return carriles;};
		int capacidad(){return cola->get_capacidad();};
		bool lleno(){return cola->heap_lleno();};
		HeapMinVehiculos *getCola(){return cola;};
		bool insert(Vehiculo *v){cola->insertar(v);};
};

Calle::Calle(int c)
{
	carriles=c;
	cola= new HeapMinVehiculos(3*N*c);
}

class Semaforo{
	private:
			int nroEsquina;
			int EsqAnterior;
			bool locked;
			Calle *colaVehiculos;
			int contador;

	public:
			Semaforo(int,int,int);
			
			int get_nroEsquina(){return nroEsquina;};
			int get_EsqAnterior(){return EsqAnterior;};
			int get_carriles(){return colaVehiculos->nCarriles();};
			int get_capacidad_cola() {return colaVehiculos->capacidad();};
			bool bloqueado() {return locked;};
			void bloquear() {locked = true;};
			void desbloquear() {locked = false;};
			bool is_full(){ return colaVehiculos->lleno();};
			
			HeapMinVehiculos *get_ColaDelSemaforo(){ return colaVehiculos->getCola();};
		
			void resetCont(){contador=0;};
			void incrementarCont(){contador++;};
			int getContador(){return contador;};
			
			int congestion();
			int get_cantidadDeVehiculos();
			void print();
		
			string printAutos_Archivo();
			
			bool cruzar(Vehiculo*);		//Este método es el que recibe los autos para encolarlos, si es que la 
										//capacidad no está colmada.
					
};


Semaforo::Semaforo(int c, int IDnodo, int proc)
{	
		nroEsquina=IDnodo;
		EsqAnterior=proc;
		locked = false;
		contador=0;
		colaVehiculos=new Calle(c);
}


bool Semaforo::cruzar(Vehiculo *v)
{	
	if(this != NULL) return colaVehiculos->insert(v);  
	else return false;
}

//Devuelve un entero que representa el porcentaje sobre 100, de ocupación que presenta la cola del semáforo. 
int Semaforo::congestion()
{
	return (int)(colaVehiculos->getCola()->get_cantVehiculos()*100/colaVehiculos->getCola()->get_capacidad());
}

int Semaforo::get_cantidadDeVehiculos()
{
	if(!colaVehiculos->getCola()->heap_vacio()) return colaVehiculos->getCola()->get_cantVehiculos();
	else return 0;
}

//Imprime la información concerniente al semáforo.
void Semaforo::print()
{	
	if(this != NULL){
		cout<<endl;
		cout<<"Ubicado en la esquina nro :"<<setw(3)<<nroEsquina; 
		cout<<" Esquina Anterior :"<<setw(3)<<EsqAnterior;
		cout<<" Nro Carriles: "<<get_carriles();
		cout<<" Saturacion del Semaforo: "<<setw(3)<<congestion()<<"% ";
		cout<<"Cant. Vehiculos: "<<setw(3)<<get_cantidadDeVehiculos()
		<<endl;
	}
	else cout<<endl<<"El semaforo no es valido"<<endl;
}


//Imprime la información de todos los autos del semaforo
string Semaforo::printAutos_Archivo(){
	
	std::ostringstream stm;
	
	if(!colaVehiculos->getCola()->heap_vacio()){
		stm<<colaVehiculos->getCola()->print_Archivo();
	}
	else stm<<endl<<"El semaforo NO tiene Vehiculos"<<endl;
	
	return stm.str();
}
