
#include <iostream>
#include <vector>
using namespace std;

struct etiqueta {	//estructura para manejar las etiquetas
	int posicion;
	int origen;
	int pesoT;
	//int iteracion;
};

int iter = 0;

int const TamGrafo = 11;
int PosAct = 0;
int PosIn;
int PosFin;
int PosObj = 10;
int PorVis = TamGrafo;
int ContEt = 0;
int ContVis = 0;
int EtCreada=0;

vector <int> camino;

vector < pair<int, int>> grafo[TamGrafo];

vector <int> visitados;

vector <etiqueta> Etiquetados;


vector <int> porvisitar;


int EncontrarPeso(int find)
{
	iter = 0;
	for (auto mov = Etiquetados.begin(); mov != Etiquetados.end(); mov++)
	{
		
		if (Etiquetados[iter].posicion == find) {
			int val = Etiquetados[iter].pesoT;
			return val;
		}
		iter++;
	}
}
int DondeEsta(int find)
{
	iter = 0;
	for (auto mov = Etiquetados.begin(); mov != Etiquetados.end(); mov++)
	{

		if (Etiquetados[iter].posicion == find) {
			
			return iter;
		}
		iter++;
	}
}

void Vertice(vector <pair<int, int> > grafo[], int u, int v, int wt)
{
	grafo[u].push_back(make_pair(v, wt));
	grafo[v].push_back(make_pair(u, wt));
}

char obtenerLetra(int numero) {
	switch (numero)
	{
	case 0: return 'A';
	case 1: return 'B';
	case 2: return 'C';
	case 3: return 'D';
	case 4: return 'E';
	case 5: return 'F';
	case 6: return 'G';
	case 7: return 'H';
	case 8: return 'I';
	case 9: return 'J';
	case 10: return 'Z';



	}
}

void printGraph(vector<pair<int, int> > grafo[], int V)
{
	int v, w;
	for (int u = 0; u < V; u++)
	{
		cout << "El nodo " << obtenerLetra(u) << " es adyacente con: \n";
		for (auto it = grafo[u].begin(); it != grafo[u].end(); it++)
		{
			v = it->first;
			w = it->second;
			cout << "\tNodo " << obtenerLetra(v) << " con un peso de: "
				<< w << "\n";
		}
		cout << "\n";
	}
}

void ObtenerCamino() {
	int posCam = Etiquetados[DondeEsta(PosFin)].posicion;
	for (int origen = 0; origen >= 0; origen)
	{
		if (posCam == Etiquetados[DondeEsta(PosIn)].posicion) 
		{
			camino.push_back(posCam);
			return;
		}
		camino.push_back(posCam);
		
		posCam = Etiquetados[DondeEsta(posCam)].origen;

	}


}




int main()
{

	Vertice(grafo, 0, 1, 3);
	Vertice(grafo, 0, 4, 5);
	Vertice(grafo, 0, 7, 4);
	Vertice(grafo, 1, 2, 2);
	Vertice(grafo, 1, 4, 5);
	Vertice(grafo, 1, 5, 7);
	Vertice(grafo, 2, 3, 3);
	Vertice(grafo, 2, 5, 2);
	Vertice(grafo, 2, 6, 6);
	Vertice(grafo, 3, 6, 7);
	Vertice(grafo, 3, 10, 2);
	Vertice(grafo, 4, 5, 4);
	Vertice(grafo, 4, 7, 7);
	Vertice(grafo, 5, 6, 4);
	Vertice(grafo, 5, 7, 5);
	Vertice(grafo, 5, 8, 4);
	Vertice(grafo, 5, 9, 3);
	Vertice(grafo, 6, 10, 6);
	Vertice(grafo, 6, 9, 4);
	Vertice(grafo, 7, 8, 2);
	Vertice(grafo, 8, 9, 6);
	Vertice(grafo, 9, 10, 3);
	cout << "Algoritmo de Dijkstra \n";
	cout << "el grafo es es siguiente:\n";
	printGraph(grafo, TamGrafo);

	cout << "ingresa la posicion inicial en entero 0-10 (donde A=0,B=1,C=2,D=3,E=4,F=5,G=6,H=7,I=8,J=9,Z=10)\n";
	cout << "Nodo Inicial: ";
	cin >> PosIn;
	cout << "\ningresa la posicion Final en entero 0-10 (donde A=0,B=1,C=2,D=3,E=4,F=5,G=6,H=7,I=8,J=9,Z=10)\n";
	cout << "Nodo Final: ";
	cin >> PosFin;
	
	PosAct = PosIn; //sirve para moverse entre el grafo 


	Etiquetados.push_back(etiqueta());
	Etiquetados[0].posicion = PosAct;
	Etiquetados[0].origen = NULL;
	Etiquetados[0].pesoT = 0;
	PorVis--;
	ContEt++;
	for (int NA ; ContVis != TamGrafo; NA)			//ciclo principal, termina cuando no existan mas elementos en el entero PorVisitar
	{

		visitados.push_back(PosAct);		//ingresa el elemento actual a la lista de elementos ya visitados para evitar que se etiqueten de nuevo
		ContVis++;

		for (auto it = grafo[PosAct].begin(); it != grafo[PosAct].end() && PosAct!=PosFin ; it++)			//primer ciclo anidado, encuentra todos los nodos adyacentes de el nodo actual	
		{
			
			int NodoAdy = it->first;
			int Peso = it->second;

			int cont1 = 0;
			int nodovisitado = 0;
			EtCreada = 0;
			for (auto i = visitados.begin(); i != visitados.end(); i++)				//segundo ciclo anidado, compara los nodos adyacentes al nodo seleccionado con la tabla de nodos visitados
			{
				if (NodoAdy == visitados[cont1])	//si el nodo ha sido visitado lo salta
				{
					nodovisitado = 1;
				}
				if (NodoAdy != visitados[cont1] && nodovisitado==0 && EtCreada==0) {										//si el nodo no ha sido visitado  entra a otro ciclo

					//int cont2 = 0;
					int banderaEtiqueta = 0;
					for (int cont2=0; cont2 !=ContEt; cont2++)		//tercer ciclo anidado en el cual se cicla a travez de los elementos en las etiquetas
					{
						
						if(Etiquetados[cont2].posicion==NodoAdy)				//comprueba si el nodo adyacente actual tiene una etiqueta
							{	
							banderaEtiqueta = 1;
							int pesotemp = 0;									// en caso de que tenga etiqueta se compara para obtener la que tenga menor peso
							pesotemp = Peso + EncontrarPeso(PosAct);		//se obtiene el valor temporal de peso de el nodo que se esta comparando-------------
							

							if(pesotemp<Etiquetados[cont2].pesoT)				//compara el peso temporal con el de la etiqueta existente
								{
								Etiquetados[cont2].origen = PosAct;				//en caso de que el peso temporal sea menor que el existente se modifica con los datos de el peso temporal
								Etiquetados[cont2].pesoT = pesotemp;

								}
																				//en caso contrario de que no sea menor no se realiza ninguna accion
							}


					}
					if (banderaEtiqueta==0)
					{
						Etiquetados.push_back(etiqueta());				//en caso de que no exista etiqueta se crea una nueva y se llena con la informacion
						Etiquetados[ContEt].origen = PosAct;
						Etiquetados[ContEt].pesoT = Peso + EncontrarPeso(PosAct); //Etiquetados[Etiquetados[ContEt].origen].pesoT;
						Etiquetados[ContEt].posicion = NodoAdy;
						ContEt++;
						EtCreada = 1;
					}


				}
				cont1++ ;											
				
			}
			
			
			

			
		}
		// para moverse al siguiente nodo evaluamos las etiquetas, descartamos los nodos que ya han sido visitados y encontramos el de menor peso
		for (int i = 0, nodomenortemp=1000; i < ContEt; i++)
		{
			int banderavisitado = 0;
			
			for (int vis = 0; vis != ContVis; vis++) //si el nodo ya ha sido visitado
			{
				if (visitados[vis]==Etiquetados[i].posicion)
				{
					banderavisitado = 1;
				}
			}
			if (banderavisitado==0)
			{
				if (Etiquetados[i].pesoT<nodomenortemp)
				{
					nodomenortemp = Etiquetados[i].pesoT;
					PosAct = Etiquetados[i].posicion;
				}
			}
		}






	}


	cout << "\n---------------------------------------------------------\n";
	cout << "el camino mas corto es: ";
	ObtenerCamino();
	for (auto it = camino.rbegin(); it != camino.rend(); it++)
	{
		cout << obtenerLetra(*it) << " ";
	}
	cout << "\n ";
	
	cout << " Con un costo total de : " << Etiquetados[DondeEsta(PosFin)].pesoT;


	return 0;

}

