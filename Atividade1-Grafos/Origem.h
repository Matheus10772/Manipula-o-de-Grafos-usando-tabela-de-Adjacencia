#pragma once
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <vector>

using namespace std;

//class Aresta
//{
//public:
//	int valor;
//	unsigned int id;
//	unsigned int id;
//};

class Vertice
{
public:
	unsigned int id = NULL;
	vector <int> Antecessores;
	vector <int> Sucessores;
	vector <int> Adjacentes;
};


class Grafo
{
public:
	string Direcionado;
	int QuantidadeDeVertices = 0;
	vector<vector<int>> MatrizAdjacencia;
	vector <Vertice> Vertices;
	int QuantidadeDeArestas = 0;
};

class DadosDoArquivo
{
public:
	int origem;
	int destino;
	int valor;
};

void RealocarMatriz(Grafo* _Grafo, unsigned int novoTamanho);
bool checkValoresValidos(char valoresValidos[], char valores[]);
vector <string> split_string(string str, const char* op);
vector<DadosDoArquivo> LerArquivo(string arqName);
Grafo CriaGrafo(string Direcionado, unsigned int QuantidadeDeVertices,  unsigned int QtdArestas);
vector <int> Sucessores(Grafo* _Grafo, unsigned int vertice);
vector <int> Antecessores(Grafo* _Grafo, unsigned int vertice);
void CriaAresta(Grafo* _Grafo, int origem, int destino, int valor);
vector<int> GrauDoVertice(Grafo* _Grafo, int vertice);
vector<vector<int>> adjacentes(Grafo* _Grafo, int vertice);
float DensidadeDoGrafo(Grafo* _Grafo);

vector<float> Sumario(Grafo* _Grafo);
