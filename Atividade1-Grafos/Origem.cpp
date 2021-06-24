#pragma warning(disable : 4996)
#include "Origem.h"
#include <iomanip>
#include <locale.h>


int main() {
	setlocale(LC_ALL, "");
#ifdef OS_Windows
	system("chcp 65001");
#endif
	unsigned int opcao = 0;
	string diretorioCaminho;
	vector <DadosDoArquivo> DadosLidos;
	list <Grafo> estruturasDeGrafo;
	Grafo* selecionado = new Grafo;
	
	do
	{
		LimparTela();
		std::cout << endl;
		std::cout

			<< "##############################################################################################\n"
			<< "#                                MANIPULADOR DE GRAFOS                                       #\n"
			<< "#--------------------------------------------------------------------------------------------#\n"
			<< "# 1 - Selecionar Arquivo de texto (.txt) para processamento do grafo                         #\n"
			<< "# 2 - Processar Arquivo de texto (.txt) selecionado em uma estrutura de grafo                #\n"
			<< "# 3 - Criar um novo grafo manualmente                                                        #\n"
			<< "# 4 - Inserir aresta manualmente (ao informar os vertices de origem e destino,               #\n"
			<< "# caso não existam, eles serão criados automaticamente).                                     #\n"
			<< "# 5 - Selecionar grafo                                                                       #\n"
			<< "# 6 - Exibir Sucessores e Antecessroes, ou adjacentes, de um vértice                         #\n"
			<< "# 7 - Exibir Grau de um vértice                                                              #\n"
			<< "# 8 - Exibir Sumário do grafo (número de arestas, vértice e densidade do grafo)              #\n"
			<< "# 9 - Processar e exibir matriz distância usando algoritmo de FloydWarshall(todos para todos)#\n"
			<< "# 10 - Exibir matriz de exentricidade de todos os pares de vértices                          #\n"
			<< "# 11 - Calcular e exibir o raio do grafo                                                     #\n"
			<< "# 12 - Calcular e exibir o diâmetro do grafo                                                 #\n"
			<< "# 13 - Calcular vértices que fazem parte do centro                                           #\n"
			<< "# 14 - Calcular vértices que fazem parte do centróide do grafo                               #\n"
			<< "# 15 - Calcular os vértices que fazem parte da periferia do grafo                            #\n"
			<< "# 0 - Sair do programa                                                                       #\n"
			<< "##############################################################################################\n"
			<< endl;

		std::cin >> opcao;
		LimparTela();
		switch (opcao)
		{
		case 1: {
			string temp = DialogoDeAberturaDeArquivo();
			if (!temp.empty()) {
				diretorioCaminho = temp;
				DadosLidos = LerArquivo(diretorioCaminho);
			}
			else {
				std::cout << "Nenhum arquivo selecionado" << endl;
			}
			Pause();
			break;
		}
		case 2: {
			if (DadosLidos.size() != 0) {
				string direcionado;
				unsigned int escolha;
				std::cout << "O Grafo será criado a partir do arquivo:" << endl;
				std::cout << diretorioCaminho << endl;
				std::cout << "é um grafo direcionado ou não? 1 - para sim 2 - para não";
				std::cout << endl;
				std::cin >> escolha;
				if (escolha == 1)
					direcionado = "Direcionado";
				else if (escolha == 2)
					direcionado = "Não direcionado";
				else {
					std::cout << "Escolha inválida" << endl;
					Pause();
					break;
				}
				estruturasDeGrafo.push_front(CriaGrafo(direcionado));
				for (std::vector<DadosDoArquivo>::iterator indice = DadosLidos.begin(); indice != DadosLidos.end(); indice++) {
					CriaAresta(&(estruturasDeGrafo.front()), (*indice).origem, (*indice).destino, (*indice).valor);
				}
				selecionado = &(estruturasDeGrafo.front());
				std::cout << "Grafo criado e processado com sucesso!" << endl;
				std::cout << selecionado << endl;

				Pause();
			}
			else {
				std::cout << "Você precisa selecionar o arquivo primeiro" << endl;
				Pause();
			}
			break;
		}
		case 3: {
			string direcionado;
			unsigned int escolha;
			std::cout << "O Grafo será criado a partir do arquivo:" << endl;
			std::cout << diretorioCaminho << endl;
			std::cout << "é um grafo direcionado ou não? 1 - para sim 2 - para não";
			std::cout << endl;
			std::cin >> escolha;
			if (escolha == 1)
				direcionado = "Direcionado";
			else if (escolha == 2)
				direcionado = "Não direcionado";
			else {
				std::cout << "Escolha inválida" << endl;
				Pause();
				break;
			}
			estruturasDeGrafo.push_front(CriaGrafo(direcionado));
			selecionado = &(estruturasDeGrafo.front());
			std::cout << "Grafo criado com sucesso!" << endl;
			Pause();
			break;
		}
		case 4: {
			char origem[256];
			char destino[256];
			char valor[256];
			std::cout << "Digite a origem" << endl;
			scanf("%s", origem);
			std::cout << "Digite o destino" << endl;
			scanf("%s", destino);
			std::cout << "Digite o valor da aresta" << endl;
			scanf("%s", valor);
			if (!(checkValoresValidos("0123456789", origem) && checkValoresValidos("0123456789", destino) && checkValoresValidos("0123456789", valor))) {
				std::cout << "Digitação inválida" << endl;
				Pause();
				break;
			}
			CriaAresta(selecionado, stoi(string(origem)), stoi(string((destino))), stoi(string(valor)));
			std::cout << "Aresta criada com sucesso!" << endl;
			Pause();
			break;
		}
		case 5: {
			vector <Grafo*> enderecos(estruturasDeGrafo.size()+1);
			unsigned int numeroGrafo = 0;
			char selecao[256];
			for (std::list<Grafo>::iterator indice = estruturasDeGrafo.begin(); indice != estruturasDeGrafo.end(); indice++) {
				std::cout << "Grafo:" << numeroGrafo << endl;
				Sumario(&(*indice));
				std::cout << endl;
				enderecos[numeroGrafo] = &(*indice);
				numeroGrafo++;
			}
			std::cout << "Digite o número do grafo que deseja selecionar" << endl;
			//std::cin >> selecionado;
			scanf("%s", selecao);
			std::cout << endl;
			if (!checkValoresValidos("0123456789", selecao)) {
				std::cout << "Digitação inválida" << endl;
				Pause();
				break;
			}
			selecionado = enderecos[stoi(string(selecao))];
			std::cout << "Grafo selecionado com sucesso" << endl;
			std::cout << enderecos[stoi(string(selecao))] << endl;

			Pause();
			break;
		}
		case 6: {
			char vertice[256];
			std::cout << "Digite o vértice desejado" << endl;
			//std::cin >> vertice;
			scanf("%s", vertice);
			if (!checkValoresValidos("0123456789", vertice)) {
				std::cout << "Digitação inválida" << endl;
				Pause();
				break;
			}
			vector<vector<int>> adj = adjacentes(selecionado, stoi(string(vertice)));
			if ((*selecionado).Direcionado == "Direcionado") {
				std::cout << "Sucessores" << endl;
				for (int i = 0; i < adj[0].size(); i++) {
					std::cout << adj[0][i] << " ";
				}
				std::cout << endl << "Antecessores" << endl;
				for (int i = 0; i < adj[1].size(); i++) {
					std::cout << adj[1][i] << " ";
				}
				std::cout << endl;
			}
			else {
				std::cout << "Adjacentes" << endl;
				for (int i = 0; i < adj[0].size(); i++) {
					std::cout << adj[0][i] << " ";
				}
				std::cout << endl;
			}
			Pause();
			break;
		}
		case 7: {
			char vertice[256];
			std::cout << "Digite o vertice que deseja ver o grau" << endl;
			scanf("%s", vertice);
			if (!checkValoresValidos("0123456789", vertice)) {
				std::cout << "Digitação inválida" << endl;
				Pause();
				break;
			}
			GrauDoVertice(selecionado, stoi(string(vertice)));
			Pause();
			break;
		}
		case 8: {
			Sumario(selecionado);
			Pause();
			break;
		}
		case 9: {
			vector<vector<int>> matrizDistancia = MenorDistancia_FloydWarshall(selecionado);
			std::cout << "calculado" << endl;
			int colunas = matrizDistancia.size();
			int linhas = 1;
			std::cout << "   ";
			for (int k = 1; k <= colunas; k++) {
				std::cout << std::setfill('0') << std::setw(2) << k << " ";

			}
			std::cout << endl;
			for (int i = 0; i < matrizDistancia.size(); i++) {
				std::cout << std::setfill('0') << std::setw(2) << linhas << " ";
				for (int j = 0; j < matrizDistancia[i].size(); j++) {
					if ((!checarExistenciaVertice(selecionado, i+1)) || (!checarExistenciaVertice(selecionado ,j+1))) {
						std::cout << "-" << "  ";
					}
					else if ((matrizDistancia[i][j] == 0 && i != j))
						std::cout << "-" << "  ";
					else
						std::cout << std::setfill('0') << std::setw(2) << matrizDistancia[i][j] << " ";
				}
				std::cout << endl;
				linhas++;
			}
			Pause();
			break;
		}
		case 10: {
			vector<vector<int>> matrizExcentricidade = ExcentricidadeTodosOsVertices(selecionado);
			int colunas = matrizExcentricidade.size();
			int linhas = 1;
			std::cout << "   ";
			for (int k = 1; k <= colunas; k++) {
				std::cout << std::setfill('0') << std::setw(2) << k << " ";

			}
			std::cout << endl;
			for (int i = 0; i < matrizExcentricidade.size(); i++) {
				std::cout << std::setfill('0') << std::setw(2) << linhas << " ";
				for (int j = 0; j < matrizExcentricidade[i].size(); j++) {
					if ((!checarExistenciaVertice(selecionado, i + 1)) || (!checarExistenciaVertice(selecionado, j + 1))) {
						std::cout << "-" << "  ";
					}
					else if ((matrizExcentricidade[i][j] == 0 && i != j))
						std::cout << "-" << "  ";
					else
						std::cout << std::setfill('0') << std::setw(2) << matrizExcentricidade[i][j] << " ";
				}
				std::cout << endl;
				linhas++;
			}
			Pause();
			break;
		}
		case 11: {
			int raio = Raio(ExcentricidadeTodosOsVertices(selecionado));
			std::cout << endl << "O raio do grafo é: " << raio << endl;
			Pause();
			break;
		}
		case 12: {
			int diametro = Diametro(ExcentricidadeTodosOsVertices(selecionado));
			std::cout << "O diâmetro do grafo é: " << diametro << endl;
			Pause();
			break;
		}
		case 13: {
			vector<vector<int>> matrizExcentricidade = ExcentricidadeTodosOsVertices(selecionado);
			vector<int> verticesCentro = Centro(matrizExcentricidade, Raio(matrizExcentricidade));
			std::cout << "O(s) vértice(s) que faz(em) parte do centro é(são): " << endl;
			for (vector<int>::iterator i = verticesCentro.begin(); i != verticesCentro.end(); i++) {
				std::cout << (*i) << " ";
			}
			Pause();
			break;
		}
		case 14: {
			vector<int> verticesCentroide = centroide(MenorDistancia_FloydWarshall(selecionado));
			std::cout << "O(s) vértice(s) que faz(em) parte do centróide é(são): " << endl;
			for (vector<int>::iterator i = verticesCentroide.begin(); i != verticesCentroide.end(); i++) {
				std::cout << (*i)+1 << " ";
			}
			Pause();
			break;
		}
		case 15: {
			vector<vector<int>> matrizExcentricidade = ExcentricidadeTodosOsVertices(selecionado);
			vector<int> verticesPeriferia = Periferia(matrizExcentricidade, Diametro(matrizExcentricidade));
			std::cout << "O(s) vértice(s) que faz(em) parte da periferia é(são): " << endl;
			for (vector<int>::iterator i = verticesPeriferia.begin(); i != verticesPeriferia.end(); i++) {
				std::cout << (*i)+1 << " ";
			}
			Pause();
			break;
		}
		case 0: {
			exit(0);
		}
		default:
			std::cout << "Opção inválida" << endl;
			Pause();
			break;
		}

	} while (opcao != 0);
} 