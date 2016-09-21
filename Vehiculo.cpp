class Vehiculo{
    private:
            string tipo;
            int matricula;
            bool prioridad;
            int posInicial;
            int posFinal;
            int posActual;
            ColaEsquinas* recorrido;				//Recorrido hecho por el vehículo.								
            ColaEsquinas* camino;                  //Camino a recorrer
            
           
    public:
            Vehiculo(int , int , int);              		//constructor para la creacion de Mi auto
            Vehiculo(string);                             			//constructor aleatorio para tipo de vehículo específico
            ~Vehiculo(void){};                                      //destructor del vehiculo
            
			bool set_prioridad(string tipo); 						//Retorna true si pudo setear correctamente la prioridad al vehiculo.      
			bool get_prioridad(void) {return prioridad;};
			
			int get_matricula(void) {return matricula;};       
			
			int get_posInicial(void) {return posInicial;};
			void set_posInicial(int o) {posInicial = o;};      
			   
			int get_posActual(void) {return posActual;};   
			void set_posActual(int p) {posActual = p;};
			
			int get_posFinal(void) {return posFinal;};  
			
			string get_tipo(void) {return tipo;};        
			
            void set_camino(ColaEsquinas*);                         //setea la lista de esquina a seguir para llegar a destino
            ColaEsquinas* get_camino() {return camino;};			// devuelve el puntero camino
            
            void put_recorrido(int p) {recorrido->agregar(p);};     //agrega una esquina al recorrido ya hecho por el vehiculo
            ColaEsquinas* get_recorrido() {return recorrido;};		//devuelve el puntero a la cola de esquinas recorridas
			
			int get_siguiente(void) {return camino->cabeza();};     //devuelve la siguiente posicion a la que se debe dirigir el vehiculo 
			bool borrar_cabeza(void) {return camino->eliminar();};      	//borra del camino el frente de la cola, dejando el 2do elemento como posicion a seguir por el vehiculo								
            bool circulando() {return  !camino->esvacia();};		//Si camino no es vacía (false) entonces el vehiculo esta circulando...			                
            
            void printDatos(void); 
            void printMiAuto(void);
			void print_encabezado(); 
			string printMiAuto_Archivo();		
            void print_recorrido(void);                             //imprime en pantalla el camino ya recorrido por el vehiculo
            void print_camino(void);                                //imprime en pantalla el camino que debe recorrer el vehiculo
            string printCamino_Archivo();
            string printRecorrido_Archivo();
};

Vehiculo::Vehiculo(int mat, int pi, int pf)
{
    tipo = "Auto";
    prioridad=false;
    matricula=mat;

    posInicial=pi;
    posActual=pi;
    posFinal=pf;

	recorrido = new ColaEsquinas();
}

Vehiculo::Vehiculo(string t)
{
	 
    if(!set_prioridad(t)){
    	cout<<"No pudo crearse el vehiculo."<<endl;
	}
	else{
		tipo = t;
    	matricula = (rand()%10000 + 1001); 	//Matricula aleatoria entre 1001 y 9999.
    	posFinal=rand()%ESQ;
    	posActual = posInicial = -1; //Cuando ubico el vehiculo seteo estos campos
		recorrido = new ColaEsquinas();
   		camino = new ColaEsquinas();
	}

}

bool Vehiculo::set_prioridad(string t)
{
	if(t=="Auto"){ prioridad=false; return true;}
    if(t=="Patrullero"||t=="Ambulancia") {prioridad=true; return true;}
    else return false;
}

void Vehiculo::set_camino(ColaEsquinas* aux)
{
	camino = new ColaEsquinas();
	
	Esquina *nodo = aux->get_comienzo();	
    while(nodo != NULL){
		camino->agregar(nodo->get_dato());
		nodo = nodo->get_next();
	}
}


void Vehiculo::printDatos()
{
	if(this!=NULL){
    cout << endl 
    << setw(15) << setiosflags(ios::left) << tipo
    <<"    "
    << setw(11) << setiosflags(ios::left) << matricula
    <<"    "
    << setw(11) << prioridad;
	}
	else cout<<endl<<"El vehiculo no es valido"<<endl;
}

void Vehiculo::printMiAuto()
{
	if(this!=NULL){
    cout << endl 
    << setw(10) << tipo
    << setw(10) << matricula
    << setw(7) << posInicial
    << setw(7) <<posFinal
    << setw(7) << posActual<<endl;
    cout<<"El camino por recorrer es: ";
    this->print_camino();
    cout<<"El camino ya realizado es: ";
	this->print_recorrido();
	}
	else cout<<endl<<"El vehiculo no es valido"<<endl;
}

string Vehiculo::printMiAuto_Archivo()
{
	std::ostringstream stm;
	
	if(this!=NULL){
    stm << endl 
    << setw(10) << tipo
    << setw(10) << matricula
    << setw(7) << posInicial
    << setw(7) << posFinal
    << setw(7) << posActual<<endl;
    stm<<"El camino por recorrer es: ";
    stm<<printCamino_Archivo();
    stm<<"El camino ya realizado es: ";
	stm<<printRecorrido_Archivo();
	}
	else stm<<endl<<"El vehiculo no es valido"<<endl;
	
	return stm.str();
}

void Vehiculo::print_encabezado()
{
    cout << endl << setw(10) << setiosflags(ios::left) 
	<< "Tipo " << setw(11) << setiosflags(ios::left) 
	<< " | Matricula " << setw(11) << setiosflags(ios::left) 
	<< " | Origen " << setw(11) << setiosflags(ios::left)
	<< " | Posicion Actual " << setw(11) << setiosflags(ios::left) 
	<< " | Destino " << setw(11) << setiosflags(ios::left) 
	<< " | Estado ";

}

void Vehiculo::print_recorrido()
{
    if(this->recorrido->esvacia()) cout << endl << " --> En ORIGEN" << endl;
    else recorrido->print();
}

void Vehiculo::print_camino()
{
    if(this->camino->esvacia()) cout << endl << " Se llego a la posicion final deseada."<<endl
											 <<"Se da por finalizada la simulacion."<< endl;
    else camino->print();
}

string Vehiculo::printRecorrido_Archivo()
{
	std::ostringstream stm;
    if(this->recorrido->esvacia()) stm << endl << " --> En  " << endl;
    else stm<<recorrido->print_file();
    
    return stm.str();
}

string Vehiculo::printCamino_Archivo()
{
	std::ostringstream stm;
    if(this->camino->esvacia()) stm << endl << "Se llego a la posicion final deseada."<<endl
											 <<"Se da por finalizada la simulacion."<< endl;
    else stm<<camino->print_file();
    
    return stm.str();
}
