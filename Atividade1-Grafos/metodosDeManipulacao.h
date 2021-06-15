//#include "metodosDeChecagem.h"
//#include "ArquivoDialogo.h"
#include "Classes.h"
#include <fstream>
#include <iostream>
//#include <iostream>
//#include <string>
//#include <cstdlib>
//#include <fstream>
//#include <stdlib.h>
//#include <cstring>
//#include <vector>

using namespace std;


void RealocarMatriz(Grafo* _Grafo, unsigned int novoTamanho);
Grafo CriaGrafo(string Direcionado, unsigned int QuantidadeDeVertices = 0, unsigned int QtdArestas = 0);
vector <int> Sucessores(Grafo* _Grafo, unsigned int vertice);
vector <int> Antecessores(Grafo* _Grafo, unsigned int vertice);
void CriaAresta(Grafo* _Grafo, int origem, int destino, int valor);
vector<int> GrauDoVertice(Grafo* _Grafo, int vertice);
vector<vector<int>> adjacentes(Grafo* _Grafo, int vertice);
float DensidadeDoGrafo(Grafo* _Grafo);
vector<vector<int>> MenorDistancia_FloydWarshall(Grafo* _Grafo);
vector<float> Sumario(Grafo* _Grafo);
bool checkValoresValidos(string valoresValidos, char valores[]);
vector <string> split_string(string str, const char* op);
vector<DadosDoArquivo> LerArquivo(string arqName);