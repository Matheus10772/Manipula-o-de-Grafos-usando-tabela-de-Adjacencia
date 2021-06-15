#include <string>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <vector>

//using namespace std;

class DadosDoArquivo
{
public:
	int origem;
	int destino;
	int valor;
};

class Vertice
{
public:
	unsigned int id = 0;
	std::vector <int> Antecessores;
	std::vector <int> Sucessores;
	std::vector <int> Adjacentes;
};
class Grafo
{
public:
	std::string Direcionado;
	int QuantidadeDeVertices = 0;
	std::vector<std::vector<int>> MatrizAdjacencia;
	std::vector <Vertice> Vertices;
	int QuantidadeDeArestas = 0;
};
