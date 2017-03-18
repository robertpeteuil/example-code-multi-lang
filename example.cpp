// Rotate_Matrix.cpp : Defines the entry point for the console application.
//Rotates a matrix 90 degrees

#include "stdafx.h"
#include <iostream>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char **mat;
	int size = 3;
	mat = new char*[size];
	for (int i = 0; i < size; i++)
	{
		mat[i] = new char[size * 4];
		for (int j = 0; j < size; j++)
		{
			mat[i][j * 4] = j + 48 + (i * size);
			mat[i][(j * 4) + 1] = j + 48 + (i * size);
			mat[i][(j * 4) + 2] = j + 48 + (i * size);
			mat[i][(j * 4) + 3] = j + 48 + (i * size);
			mat[i][(j * 4) + 4] = 0;
		}
	}

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size * 4; j++)
		{
			if (j == 0)
				cout << "(";
			else if (j % 4 == 0)
				cout << ")(";
			cout << mat[i][j];
		}
		cout << ")" << endl;
	}
	cout << endl << "Rotated 90 degrees."<<endl<<endl;
	for (int i = size-1; i >= 0; i--)
	{
		for (int j = (size * 4)-1; j >=0; j--)
		{
			if (j == (size * 4) - 1)
				cout << "(";
			else if ((j+1) % 4 == 0)
				cout << ")(";
			cout << mat[i][j];
		}
		cout << ")" << endl;
	}

	cout << "Termine." << endl;
	getchar();
	return 0;
}


// Simple_Linked_List.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Node
{
public:
	int Value;
	Node *Next;

	Node(int value)
	{
		Value = value;
		Next = NULL;
	}
};

class Simple_Linked_List
{
public:
	Node *Start;

	Simple_Linked_List()
	{
		Start = NULL;
	}

	void Add_First(int n)
	{
		if (Start == NULL)
		{
			Start = new Node(n);
		}
		else
		{
			Node *node = new Node(n);
			node->Next = Start;
			Start = node;
		}
	}

	void Add_End(int n)
	{
		Node *a = Start;
		if (Start == NULL)
		{
			Start = new Node(n);
		}
		else
		{
			while (a->Next != NULL)
				a = a->Next;
			a->Next = new Node(n);
		}
	}

	void Remove_Duplicates()
	{
		Node *a = Start;
		Node *b;
		while (a->Next != NULL)
		{
			b = a->Next;
			while (b != NULL)
			{
				if (a->Value == b->Value)
				{
					Delete(b);
				}
				else
				{
					b = b->Next;
				}
			}
			a = a->Next;
		}

	}

	Node* Detect_Bucle()
	{
		//Returns the node where the bucle starts
		Node *a = Start;
		Node *b;
		Node *res = NULL;
		while (a->Next != NULL)
		{
			b = a->Next;
			while (b != NULL)
			{
				if (a->Value == b->Value)
				{
					res = a;
					break;
				}
				else
				{
					b = b->Next;
				}
			}
			if (res != NULL)
				break;
			a = a->Next;
		}
		return res;
	}

	Node* Reverse()
	{
		Simple_Linked_List l = Simple_Linked_List();
		Node *a = Start;
		while (a != NULL)
		{
			l.Add_First(a->Value);
			a = a->Next;
		}
		return l.Start;
	}

	Node* Find_nth_to_End(int n)
	{
		Node *a = Reverse();
		while (n != 0&&a!=NULL)
		{
			a = a->Next;
			n--;
		}

		return a;
	}

	void Delete(Node *n)
	{
		if (n != NULL)
			*n = *n->Next;
	}

	Node* Add_Numbers(Simple_Linked_List number1, Simple_Linked_List number2)
	{
		Node *a = number1.Start;
		Node *b = number2.Start;
		Node *t;
		Start = NULL;

		int tmp = 0;
		while (a != NULL&&b != NULL)
		{
			int sum = a->Value + b->Value + tmp;
			Add_End(sum % 10);
			tmp = sum / 10;
			a = a->Next;
			b = b->Next;
		}
		t = a == NULL ? b : a;
		while (t != NULL)
		{
			int sum = t->Value + tmp;
			Add_End(sum % 10);
			tmp = sum / 10;
			t = t->Next;
		}
		if (tmp != 0)
		{
			Add_End(tmp);
			tmp = 0;
		}

		return Start;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	Simple_Linked_List l1 = Simple_Linked_List();
	Simple_Linked_List l2 = Simple_Linked_List();
	Simple_Linked_List l3 = Simple_Linked_List();

	l1.Add_First(9);
	l1.Add_First(3);
	l1.Add_First(5);
	l1.Add_First(1);
	l1.Add_First(3);

	l1.Detect_Bucle();

	l2.Add_First(2);
	l2.Add_First(9);
	l2.Add_First(5);

	l3.Add_Numbers(l1, l2);

	cout << "Termine." << endl;
	getchar();
	return 0;
}
