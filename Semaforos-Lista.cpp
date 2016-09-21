/*
Listasemaforos es una lista que se ordena en función de la congestión de los semáforos.
El semáforo mas congestionado se ubica primero en la lista.
*/

#include "Semaforo.cpp"		

class Nodosemaforo{
    private:
            Semaforo* dato;
            Nodosemaforo *next;
    public:
           Nodosemaforo(Semaforo* a) {dato=a; next=NULL;};  //este constructor se utiliza al añadir elementos
           void set_dato(Semaforo* a) {dato=a;};            //setea la variable dato del Nodosemaforo en cuestion
           void set_next(Nodosemaforo *n) {next=n;};        //recibe la direccion a la que apunta czo y la guarda en el next de nuevo
           Semaforo* get_dato() {return dato;};             //devuelve el campo dato del Nodosemaforo desde que se llamo a este metodo
           Nodosemaforo* get_next() {return next; };        //devuelve la direccion de memoria a la que apunta el puntero a Nodosemaforo next
};

class Listasemaforos{ 
    protected:
            Nodosemaforo *czo;
    public:
            Listasemaforos() {czo=NULL;};                          //constructor para la creacion de la Listasemaforos
            ~Listasemaforos(void);                                 //destructor de la Listasemaforos
            void insertar(Semaforo* d);                             //agrega un elemento a la Listasemaforos
            void eliminar(void);                                   //elimina la cabeza de la Listasemaforos
            bool esvacia(void);										//devuelve 1 si es vacia y cero si no lo es
            Nodosemaforo *get_czo(){return czo;};                                    
            
            Semaforo* cabeza(void);                                //devuelve la cabeza de la Listasemaforos
            Semaforo* buscar(int, int);                            //devuelve el puntero al semaforo buscado a partir de el número de esquina
            													   // y de la esquina anterior
            Semaforo* buscar(int);                  //recibe un numero aleatorio de la posicion en la lista a buscar
            Semaforo* buscar(Nodosemaforo*, int);   //metodo recursivo que llega hasta un Nodosemaforo y devuelve su semaforo
            void ordenar();                                        //se utiliza para ordenar la lista de semaforos mediante una implementacion de insert-sort...
            
            int get_congestion(int i);    						   //Devuelve la congestion del semaforo i de la lista. Si este no existe, devuelve -1.
			void ubicarAleatorio(Vehiculo*); 
			void ubicarMiAuto(Vehiculo *v);
			
            void toPrint(string,int);
            
            void print();										   //Imprime todos los semaforos

            void print_ArchivoSemaforos(void);                     //imprime en un archivo la lista de semaforos completa
            
};

Listasemaforos::~Listasemaforos(void)
{
    while(czo != NULL) //elimina la cabeza de la lista mientras que czo no apunte a NULL
    this->eliminar();
}

void Listasemaforos::insertar(Semaforo* d)
{  
    Nodosemaforo* nuevo=new Nodosemaforo(d);
    nuevo->set_next(czo);
    czo = nuevo;
}

void Listasemaforos::eliminar()
{
    Nodosemaforo *aux;
    aux = czo;
    czo = czo->get_next();
    delete aux;
}

bool Listasemaforos::esvacia(void)
{   
    return czo==NULL;
    srand(time(NULL));
}

Semaforo* Listasemaforos::cabeza(void)
{
    return czo->get_dato();
}



Semaforo* Listasemaforos::buscar(int u, int a)
{
    Nodosemaforo *nodo = czo;
    Semaforo *aux = NULL;
    while(nodo != NULL)
    {
        if(((nodo->get_dato())->get_nroEsquina() == u) && ((nodo->get_dato())->get_EsqAnterior() == a))
        aux = nodo->get_dato();
        nodo = nodo->get_next();
    }
    return aux;
}

Semaforo* Listasemaforos::buscar(int x)
{
    if(x>=0 && x<SEM)
    return buscar(czo, x);
    else return NULL;
}

Semaforo* Listasemaforos::buscar(Nodosemaforo* c, int x)
{
    Semaforo* aux;
    if(x > 0) aux = buscar(c->get_next(), x-1);
    else if(x == 0) aux = c->get_dato();
    return aux;
}

void Listasemaforos::ordenar()
{
    Semaforo* aux[SEM];
    Semaforo* temp;
    int i, j;
    for(i=0 ; i<SEM ; i++)
    {
        aux[i] = czo->get_dato();		//Copio la cabeza de ListaSemaforos en aux[i]
        this->eliminar();				//Elimino el nodo de ListaSemaforos
    }
    
    for(i=1 ; i<SEM ; i++) //Implementamos una busqueda por insercion (n2)
    {
        j=i-1;
        while(j>=0)
        {
            if(((aux[j+1])->get_cantidadDeVehiculos()) <= ((aux[j])->get_cantidadDeVehiculos()))
            {
                temp = aux[j+1];
                aux[j+1]=aux[j];
                aux[j]=temp;
            }
            j--;
        }
    }
    for(i=0 ; i<SEM ; i++)
    this->insertar(aux[i]);
}

int Listasemaforos::get_congestion(int i)
{
	Semaforo *aux;
	
	aux=buscar(i);
	
	if(aux!=NULL) return aux->congestion();
	else return -1;
	
}

void Listasemaforos::ubicarAleatorio(Vehiculo *v)
{ 
	
	int rnd = rand()%SEM;
	Semaforo *aux;
	aux=buscar(rnd);
	
	while(aux->get_nroEsquina() == v->get_posFinal()){ //
		rnd= rand()%SEM;
		aux=buscar(rnd);
	}
	
	if(aux != NULL) {
		if(aux->cruzar(v)) { //Si 'v' se pudo encolar en la cola de 'aux':
			v->set_posInicial(aux->get_nroEsquina()); //Seteo pos inicial y actual en relacion a la esquina
			v->set_posActual(aux->get_nroEsquina());
		}
		else cout<<"La calle estaba llena y no se pudo insertar el vehiculo mat.: "<<v->get_matricula()<<endl;			
	}
}

void Listasemaforos::ubicarMiAuto(Vehiculo *v)
{ 	
	Nodosemaforo *nodo = czo;
    Semaforo *aux = NULL;
    
    while((nodo != NULL)&&(aux==NULL))
    {
        if(nodo->get_dato()->get_nroEsquina() == v->get_posInicial()){
			aux = nodo->get_dato();
		}
        nodo = nodo->get_next();
    }
	if(aux != NULL) {
		if(!aux->cruzar(v)) cout<<"La calle estaba llena y no se pudo insertar Mi Auto: "<<v->get_matricula()<<endl;		
	}
	else cout<<"Error en la busqueda del semaforo."<<endl;

}

void Listasemaforos::print()
{ 
    Nodosemaforo *nodo = czo;
    int cont=0;
    while(nodo != NULL)
    {	
		cont++;
		cout<<cont<<"  ";
        nodo->get_dato()->print();
        nodo = nodo->get_next();
    }
}

void Listasemaforos::toPrint(string p,int iter)
{ 
    ofstream salida;
    salida.open("Ranking.txt", std::ofstream::out | std::ofstream::app);
    
    if (salida.fail())
    {
    	cout<<"No se pudo crear el archivo de salida con el Ranking."<<endl<<endl;
	}
    
    Nodosemaforo *aux;
    aux = czo;
	std::ostringstream stm;
	int cont=0;
    
    stm << p; //Agrego el string que recibió como parámetro

    while(aux != NULL)
    {
		cont++;
		stm << endl << setw(11) << setiosflags(ios::left) << "Semaforo N°: "<<cont
		                                                  <<"   Iteracion: "<<iter<<endl; 
		stm << setw(11) << setiosflags(ios::left) << "| Esquina " 
			<< setw(14) << setiosflags(ios::left) << "| Anterior " 
			<< setw(11) << setiosflags(ios::left) << "| Carriles " 
			<< setw(11) << setiosflags(ios::left) << "| Congestión %"
			<< setw(11) << setiosflags(ios::left) << "| N° de Vehiculos ";
		stm << endl <<endl;
		
        stm << "| " << setw(7) << setiosflags(ios::left) << (aux->get_dato())->get_nroEsquina();
        stm << "  | " << setw(11) << setiosflags(ios::left) << (aux->get_dato())->get_EsqAnterior();
        stm << " | " << setw(8) << setiosflags(ios::left) << (aux->get_dato())->get_carriles();
        stm << " | " << setw(11) << setiosflags(ios::left) << (aux->get_dato())->congestion();
        stm << " | " << setw(3) << setiosflags(ios::left) << (aux->get_dato())->get_cantidadDeVehiculos()<<endl;
        stm << aux->get_dato()->printAutos_Archivo();
        aux = aux->get_next();
        
    }
    
    salida << stm.str();

    salida.close();
       
     
}

void Listasemaforos::print_ArchivoSemaforos()
{ 
    ofstream printSem;
    printSem.open("Ranking.txt");
    if (printSem.fail())
    {
    	cout<<"No se pudo generar correctamente el archivo de salida"<<endl;
	}
    Nodosemaforo *aux;
    aux = czo;
    printSem << setw(11) << setiosflags(ios::left) << "|| Esquina " 
			<< setw(11) << setiosflags(ios::left) << "|| Anterior " 
			<< setw(11) << setiosflags(ios::left) << "|| Carriles " 
			<< setw(11) << setiosflags(ios::left) << "|| Saturacion ";
    printSem<< endl<<endl<<endl;
    while(aux != NULL)
    {
        printSem<< " || " << setw(7) << setiosflags(ios::left) << (aux->get_dato())->get_nroEsquina();
        printSem << " || " << setw(11) << setiosflags(ios::left) << (aux->get_dato())->get_EsqAnterior();
        printSem << " || " << setw(8) << setiosflags(ios::left) << (aux->get_dato())->get_carriles();
        printSem << " || " << setw(3) << setiosflags(ios::left) << (aux->get_dato())->congestion()<<endl;
        
        aux = aux->get_next();
    }
    printSem.close();
}
