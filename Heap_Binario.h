#ifndef HEAP_BINARIO_H_INCLUDED
#define HEAP_BINARIO_H_INCLUDED

#include <iostream>
#include <windows.h>
#include <string>
#include <stdexcept>

using namespace std;


const int MAX = 1000; // tamanho maximo da Heap

template <typename T>
struct Dado {
	int chave;
	T dado;
};

template <typename T>
struct Heap {
	Dado<T> * vet[MAX];
	char tipo;   // 'M' para maximo e 'm' para minimo
	int qtd;
};

template <typename T>
void inicializarHeap(Heap<T> &heap, char tipo) { 
	heap.qtd = 1;
	if (tipo == 'M' or tipo == 'm') {
		heap.tipo = tipo;
	}
	else {
		heap.tipo = 'm'; // default minimo
	}
	for (int i = 0; i < MAX; i++) {
		heap.vet[i] = NULL;
	}
}

template <typename T>       
void removerHeap(Heap<T> &heap) {
	heap.vet[1] = heap.vet[--heap.qtd];
	heap.vet[heap.qtd] = NULL;
	baixoHeap(heap, 1);
}

template <typename T>
bool baixoHeap(Heap<T> &heap, int i) {
	if (heap.vet[i * 2] == NULL) {
		return true;
	}
	if (heap.tipo == 'm') {                      //Troca o pai pelo filho menor no heap min
		if (heap.vet[i * 2 + 1] != NULL) {
			if (heap.vet[i * 2]->chave < heap.vet[i * 2 + 1]->chave) {
				if (heap.vet[i * 2]->chave < heap.vet[i]->chave) {
					swap(heap.vet[i], heap.vet[i * 2]);
					baixoHeap(heap, i * 2);
				}
			}
			else {
				if (heap.vet[i * 2 + 1]->chave < heap.vet[i]->chave) {
					swap(heap.vet[i], heap.vet[i * 2 + 1]);
					baixoHeap(heap, i * 2 + 1);
				}
			}
		}
		else {
			if (heap.vet[i * 2]->chave < heap.vet[i]->chave) {
				swap(heap.vet[i], heap.vet[i * 2]);
				baixoHeap(heap, i * 2);
			}
		}
	}
	else if (heap.tipo == 'M') {              //Troca o pai pelo filho menor no heap min
		if (heap.vet[i * 2 + 1] != NULL) {
			if (heap.vet[i * 2]->chave > heap.vet[i * 2 + 1]->chave) {
				if (heap.vet[i * 2]->chave > heap.vet[i]->chave) {
					swap(heap.vet[i], heap.vet[i * 2]);
					baixoHeap(heap, i * 2);
				}
			}
			else {
				if (heap.vet[i * 2 + 1]->chave > heap.vet[i]->chave) {
					swap(heap.vet[i], heap.vet[i * 2 + 1]);
					baixoHeap(heap, i * 2 + 1);
				}
			}
		}
		else {
			if (heap.vet[i * 2]->chave > heap.vet[i]->chave) {
				swap(heap.vet[i], heap.vet[i * 2]);
				baixoHeap(heap, i * 2);
			}
		}
	}
}


template <typename T>//     o(log n)
bool inserirHeap(Heap<T> &heap, Dado<T> dado) {
	Dado<T> * novo = new Dado<T>;
	if (novo == NULL) {
		return false;
	}
	novo->chave = dado.chave;
	novo->dado = dado.dado;
	if (heap.qtd == MAX) {
		return false;
	}
	heap.vet[heap.qtd] = novo;
	heap.qtd++;
	if (heap.qtd>2) {
		cimaHeap(heap, ((heap.qtd - 1) / 2));
	}
	return true;
}

template <typename T>
bool cimaHeap(Heap<T> &heap, int i) { // o(log n)
	if (i == 0) {
		return true;
	}
	if (heap.tipo == 'm') {                      //Troca o pai pelo filho menor no heap min
		if (heap.vet[i]->chave > heap.vet[i * 2]->chave) {
			swap(heap.vet[i], heap.vet[i * 2]);
		}
		if (heap.vet[i * 2 + 1] != NULL) {
			if (heap.vet[i]->chave > heap.vet[i * 2 + 1]->chave) {
				swap(heap.vet[i], heap.vet[i * 2 + 1]);
			}
		}
	}
	else if (heap.tipo == 'M') {              //Troca o pai pelo filho menor no heap min
		if (heap.vet[i]->chave < heap.vet[i * 2]->chave) {
			swap(heap.vet[i], heap.vet[i * 2]);
		}
		if (heap.vet[i * 2 + 1] != NULL) {
			if (heap.vet[i]->chave < heap.vet[i * 2 + 1]->chave) {
				swap(heap.vet[i], heap.vet[i * 2 + 1]);
			}
		}
	}
	cimaHeap(heap, i / 2);
}
template <typename T>
void atualizar(Heap<T> &heap, T d, int chave) throw(){
	try {
		for (int i = 1; i < heap.qtd; i++) {
			if (heap.vet[i]->dado == d) {
				heap.vet[i]->chave = chave;
				if (heap.tipo = 'm') {
					if (heap.vet[i]->chave < heap.vet[i / 2]->chave) {
						cimaHeap(heap, i);
					}
					else {
						baixoHeap(heap, i);
					}
				}
				else if (heap.tipo = 'M') {
					if (heap.vet[i]->chave < heap.vet[i / 2]->chave) {
						baixoHeap(heap, i);
					}
					else {
						cimaHeap(heap, i);
					}
				}
			}
		}
	}
	catch (exception& e) {
		cout << "Erro de execao: " << e.what() << endl;
	}
}

template <typename T>
void menu(Heap<T> &heap) {
	int opcao = 0;
	Dado<string> d;
	while (true) {
		T dado;
		int chave;
		system("cls");
		cout << "\nEscolha uma opção:\n";
		cout << "\n1...Inserir dado.\n";
		cout << "\n2...Remover topo.\n";
		cout << "\n3...Atualizar heap.\n";
		cout << "\n4...Exibir heap.\n";
		cout << "\n> ";
		cin >> opcao;
		switch (opcao) {
			case 1:
				cout << "\nInforme os dados.\n";
				cout << "\n1.Chave: ";
				cin >> d.chave;
				cout << "\n2.Dado: ";
				cin >> d.dado;
				// d.dado = "Os babacas que se danem - Stiffler";
				inserirHeap(heap, d);
				cimaHeap(heap, (heap.qtd - 1) / 2);
				break;
			case 2:
				removerHeap(heap);
				break;
			case 3:
				cout << "\nInforme os dados.\n";
				cout << "\n1.Nova Chave: ";
				cin >> chave;
				cout << "\n2.Dado: ";
				cin >> dado;
				atualizar(heap, dado, chave);
				break;
			case 4:
				for (int i = 1; i < heap.qtd; i++) {
					cout << "\n" << i << ". " << heap.vet[i]->chave << " - " << heap.vet[i]->dado;
				}
				cout << endl;
				system("pause");
				break;
			default:
				cout << "\nInforme um valor válido!";
				break;
		}
	}
}

#endif 
