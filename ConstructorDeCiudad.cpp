#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

int main()
{
	int const infi=9;
	int m,n; 					// m manzanas horizontales y n manzanas verticales
	int x1,x2,y1,y2;			// ubicación de las avenidas 
	int x1cant,x2cant,y1cant,y2cant;	
	int i,j;
//Inicialización de las dimensiones de la ciudad			
	do{
	cout<<"Ingrese la cantidad de manzanas horizontales que desea tener: ";
	cin>>m;					
	}while(m<=0);
	do{
	cout<<"Ingrese la cantidad de manzanas verticales que desea tener: ";
	cin>>n;
	} while (n<=0);

// Ubicación de las avenidas y su cantidad de carriles
	cout<<"Debe elegir posiciones de avenidas que se encuentren dentro la ciudad."<<endl<<"Una avenida solo puede tener 2 o 3 carriles."<<endl;
	
	do{
		cout<<"Ingrese la ubicacion de la primera avenida horizontal: "<<endl;
		cin>>x1;
		cout<<"Cantidad de carriles: "<<endl;
		cin>>x1cant;
	}while(x1<0||x1>m||(x1cant!=2&&x1cant!=3));
	
	do{
		cout<<"Ingrese la ubicacion de la Segunda avenida horizontal, diferente de la primera: "<<endl;
		cin>>x2;
		cout<<"Cantidad de carriles: "<<endl;
		cin>>x2cant;
	}while(x2<0||x2>m||(x2cant!=2&&x2cant!=3)||x1==x2);
	
	do{
		cout<<"Ingrese la ubicacion de la primera avenida vertical: "<<endl;
		cin>>y1;
		cout<<"Cantidad de carriles: "<<endl;
		cin>>y1cant;
	}while(y1<0||y1>n||(y1cant!=2&&y1cant!=3));
	
	do{
		cout<<"Ingrese la ubicacion de la Segunda avenida vertical, diferente de la primera: "<<endl;
		cin>>y2;
		cout<<"Cantidad de carriles: "<<endl;
		cin>>y2cant;
	}while(y2<0||y2>n||(y2cant!=2&&y2cant!=3)||y1==y2);

// MATRIZ // 	
	int MA[(m+1)*(n+1)][(m+1)*(n+1)];
	for( i=0;i<((m+1)*(n+1));i++)					// Inicializa todos en infi menos la identidad, que le da 0
	{
		for( j=0;j<((m+1)*(n+1));j++)
		{
		if(i==j)
		{
				MA[i][j]=0;
		}
		else MA[i][j]=infi;
		}
	}
	
	
i=0;
while (i<(m+1)*(n+1))
{																			// Ver si es necesario que compruebe doblmente
	if(((i/(n+1))==x1)||((i/(n+1))==x2))   									// pregunta si coincide la ubicacion de la calle con una avenida horizontal
	{
		if((i%(n+1)!=0)&&(i%(n+1)!=n))										// verifica que no este en los extremos
			{
				if(i/(n+1)==x1)												//verifica en cuál avenida está
				{
					MA[i][i+1]=x1cant;									
					MA[i][i-1]=x1cant;
				}
				else
				{
					MA[i][i+1]=x2cant;
					MA[i][i-1]=x2cant;
				}
			}
		else																// está en los extremos
		{
			if((i%(n+1)==0))												//verifica si está en el extremo izquierdo
			{
				if(i/(n+1)==x1)
				{
				MA[i][i+1]=x1cant;
				}
				else
				{
				MA[i][i+1]=x2cant;
				}
			}																// Si esta en el extremo  derecho de la ciudad
			else
			{																
				if(i/(n+1)==x1)
				{
				MA[i][i-1]=x1cant;
				}
				else
				{
				MA[i][i-1]=x2cant;
				}									
			}
		}
	}	
	else																// es una calle horizontal
	{
		if((i/(n+1))%2==0)												// verifica si esta en una fila par o impar
		{
			if(i%(n+1)!=n)											//Se fija que no este en el extremo derecho // modifique por n//
			{
				MA[i][i+1]=1;			
			}															
		}
		else															// Esta e una calle impar impar
		{	if( i%(n+1)!=0)										
			 		MA[i][i-1]=1;
		}
	}
	
	
	if((i%(n+1))==y1||(i%(n+1))==y2)   									// pregunta si coincide la ubicacion de la calle con una avenida vertical
	{
		if((i/(n+1)!=0)&&(i/(n+1)!=m))									// verifica que no este en los extremos
			{
				if(i%(n+1)==y1)											// verifica que sea la primera avenida
				{			
				MA[i][i+(n+1)]=y1cant;
				MA[i][i-(n+1)]=y1cant;
				}
				else
				{
				MA[i][i+(n+1)]=y2cant;
				MA[i][i-(n+1)]=y2cant;	
				}
			}
		else															//se encuentra en uno de los extremos
			{
			if((i/(n+1)==0))											// si esta en el extremo superior de la ciudad
				if(i%(n+1)==y1)
					{	
						MA[i][i+(n+1)]=y1cant;
					}
					else
					{
						MA[i][i+(n+1)]=y2cant;	
					}
			else														// Si esta en el extremo  inferior de la ciudad
				{
				if(i%(n+1)==y1)
					MA[i][i-(n+1)]=y1cant;
				else
					MA[i][i-(n+1)]=y2cant;
				}
			}	
	}	
	else																// Es una calle vertical
	{
		if(i%(n+1)%2==0)												// verifica si esta en una columna par o impar
		{	
			if((i/(n+1)!=m))											// VER si es m o M+1
				MA[i][i+(n+1)]=1;
		}
		else															//columna impar
		{
			if( (i/(n+1)!=0))
			MA[i][i-(n+1)]=1;	
		}
	}
	
	i++;	
}


for( i=0;i<((m+1)*(n+1));i++)
	{
		for( j=0;j<((m+1)*(n+1));j++)
		{
		cout<< MA[i][j];
		}
	cout<<endl<<endl;
	}

string nombre_archivo="plano.txt";
ofstream archivo_sal;
archivo_sal.open(nombre_archivo.c_str());

for( i=0;i<((m+1)*(n+1));i++)				
	{
		for( j=0;j<((m+1)*(n+1));j++)
		{
		cout<< MA[i][j];
		archivo_sal<<MA[i][j];
		}
	cout<<endl<<endl;
	archivo_sal<<endl<<endl;
	}

archivo_sal.close();

return 0;

}
