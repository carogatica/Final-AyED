/* 
 * Cada Esquina representa un nodo del grafo.
 * Los datos que lo componen son el nro. de esquina (dato) y
 * el peso relativo del mismo (peso). El campo next se utiliza para 
 * enlazar los nodos en una cola. 
 * */
class Esquina{
    private:
            int dato;
            int peso;
            Esquina *next;
    public:
		   Esquina() {next=NULL;};  
		   Esquina(int a) {dato=a; next=NULL;};   
		   Esquina(int a, int b) {dato=a; peso=b; next=NULL;};   
		   void set_dato(int a) {dato=a;};            
		   void set_next(Esquina *n) {next=n;};      //recibe la direccion de una esquina y la guarda en el next de nuevo
		   int get_dato() {return dato;};             
		   int get_peso() {return peso;};
		   Esquina *get_next() {return next;};    //devuelve la direccion de memoria a la que apunta el puntero a Esquina next
		   void print();
};

void Esquina::print()
{
	cout<<"ID del nodo: "<<dato<<". Peso de la arista hacia origen :"<<peso<<"."<<endl;
}


/*
* Cola de esquinas que representan los nodos del grafo de la ciudad.
* Se usara esta clase en el Grafo.
*/

class ColaEsquinas{ 
    protected:
            Esquina *czo;
    public:
            ColaEsquinas() {czo=NULL;};                  	
            ~ColaEsquinas(void);                         	
            Esquina *get_comienzo() {return czo;};
            int cabeza(void);  								//Retorna el primer elemento de la cola.
            void agregar(int d);                         	//agrega un elemento a la cola
            void agregar_final(int d);                   	//agrega un dato al final de la cola
            bool eliminar(void);                         	//elimina el frente de la cola. 
            bool buscar(int);                            	//devuelve 1 si una esquina esta en la lista y 0 si no
            void print(void);                            	
            string print_file(void);					
            bool esvacia(void) {return czo==NULL;};      	
            
};

ColaEsquinas::~ColaEsquinas(void)
{
    while(czo != NULL) //elimina el frente de la cola mientras que czo no apunte a NULL
    this->eliminar();
}

bool ColaEsquinas::eliminar()
{
    Esquina *aux;
    aux = czo;
    if(!esvacia()){ 
		czo = czo->get_next();
		delete aux;
		return true;
	}
    else{
		cout<<"ColaEsquinas vacia"<<endl;
		return false;
	}
    
}

int ColaEsquinas::cabeza()
{
	if(esvacia())return -1;
	else return czo->get_dato();

}

void ColaEsquinas::agregar(int d)
{  
    if(czo == NULL)
    {
        Esquina *nuevo=new Esquina(d);
        nuevo->set_next(czo);
        czo = nuevo;
    }
    else this->agregar_final(d);
}

void ColaEsquinas::agregar_final(int d)
{
    Esquina *nuevo=new Esquina(d);
    Esquina *aux;
    aux=czo;
    
    while((aux->get_next()) != NULL) //este while hace avanzar de a un Nodo a aux hasta que next apunte a NULL
    aux = aux->get_next();
    
    aux->set_next(nuevo);
}

bool ColaEsquinas::buscar(int n)
{
    Esquina *aux;
    aux = czo;
    bool bandera = false;
    while((aux != NULL) && (bandera == false))
    {
        if((aux->get_dato()) == n) bandera = true;
        aux = aux->get_next();
    }
    return bandera;
}

void ColaEsquinas::print(void)
{ 
    Esquina *aux;
    aux = czo;
    cout << endl;
    while(aux != NULL)
    {
        cout << " --> " << aux->get_dato();
        aux = aux->get_next();
    }
    cout << endl;
}

string ColaEsquinas::print_file(void)
{
	std::ostringstream stm; 
    Esquina *aux;
    aux = czo;
    stm << endl;
    while(aux != NULL)
    {
        stm << " --> " << aux->get_dato();
        aux = aux->get_next();
    }
    stm << endl;
    
    return stm.str();
}
