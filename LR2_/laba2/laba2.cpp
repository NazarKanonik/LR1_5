#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <string>

using namespace std;

struct Node
{
	int inf;
	Node *next;
};

//============================Stack==============================

void push(Node *&st, int dat)
{  // Загрузка числа в стек

	Node *el = new Node;
	el->inf = dat;
	el->next = st;
	st = el;
}

int pop(Node *&st)
{       // вилучення зі стеку

	int value = st->inf;
	Node *temp = st;
	st = st->next;
	delete temp;

	return value;
}

int peek(Node *st)
{     // отримання числа без його вилучення
	return st->inf;
}

//==============================================================

Node **graph;   // Масив списків суміжності
const int vertex = 1; // Перша вершина

void add(Node*& list, int data)
{  //Додавання суміжної вершини

	if (!list) { list = new Node; list->inf = data; list->next = 0; return; }

	Node *temp = list;
	while (temp->next)temp = temp->next;
	Node *elem = new Node;
	elem->inf = data;
	elem->next = NULL;
	temp->next = elem;
}

void del(Node* &l, int key)
{ // видалення вершини key зі списку

	if (l->inf == key) { Node *tmp = l; l = l->next; delete tmp; }
	else
	{
		Node *tmp = l;
		while (tmp)
		{
			if (tmp->next) // є наступна вершина
				if (tmp->next->inf == key)
				{  // і це шукана вершина
					Node *tmp2 = tmp->next;
					tmp->next = tmp->next->next;
					delete tmp2;
				}
			tmp = tmp->next;
		}
	}
}

int eiler(Node **gr, int num)
{ // визначення ейлеровості графа

	int count;
	for (int i = 0; i<num; i++)
	{  //проходимо всі вершини

		count = 0;
		Node *tmp = gr[i];

		while (tmp)
		{       // рахуємо степінь
			count++;
			tmp = tmp->next;
		}
		if (count % 2 == 1)return 0; // степінь непарний
	}
	return 1;   // все степені парні
}

void eiler_path(Node **gr)
{ //побудова циклу

	Node *S = NULL;// Стек для  пройдених вершин
	int v = vertex;// 1ша вершина (довільна)
	int u;

	push(S, v); //зберігаємо її в стек
	while (S)
	{  //доки стек не пустий
		v = peek(S); // поточна вершина
		if (!gr[v]) { // якщо немає інцидентних ребер
			v = pop(S);
			cout << v + 1 << "   "; //виводимо вершину  (відлік від 1, поэтому +1)
		}
		else
		{
			u = gr[v]->inf; push(S, u);  //проходимо в наступну вершину
			del(gr[v], u); del(gr[u], v); //видаляємо пройдене ребро
		}
	}
}

int main()
{
	setlocale(LC_ALL, "Russian");
	system("CLS");
	cout << "Кiлькiсть вершин:  "; int n; cin >> n; // Кiлькiсть вершин
	int zn, mas[20];// поточне значение
	
	ifstream file;
		file.open("lab2.txt");
	graph = new Node*[n];
	for (int i = 0; i<n; i++)graph[i] = NULL;
	for (int i = 0; i<n; i++)   // заповнюємо масив списків

		for (int j = 0; j<n; j++)
		{
			file >> zn;
			if (j == 0) {
				cout << "\n";
				cout << zn;
			}
			else {
				cout << " ";
				cout << zn;
			}

			if (zn) {
				add(graph[i], j);
				
			}

		}

	cout << "\n\nРЕЗУЛЬТАТ  ";

	if (eiler(graph, n))eiler_path(graph);
	else cout << "Граф не є Ейлерiв.";

	cout << endl;
	cin.get();
	cin.get();
	return(0);

}
