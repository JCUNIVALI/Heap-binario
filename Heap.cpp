// Heap.cpp : define o ponto de entrada para o aplicativo do console.
//

#include "stdafx.h"
#include <iostream>
#include "Heap_Binario.h"
using namespace std;

int main()
{
	setlocale(LC_ALL, "Portuguese_Brazil");
	Dado<string> d;
	Heap<string> heap;
	inicializarHeap(heap, 'm');
	menu(heap);
    return 0;
}

