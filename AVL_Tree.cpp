// Ready Work.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

using namespace std;

struct node {
	int value;
	node* left;
	node* right;
	int balance;
};

int Height(node* root) {
	if (root == NULL) return 0;
	int hLeft = Height(root->left);
	int hRight = Height(root->right);
	if (hLeft > hRight) return hLeft + 1;
	else return hRight + 1;
}

void SetBalance(node* (&root)) {
	if (root != NULL)
		root->balance = Height(root->right) - Height(root->left);
}

void TurnLeft(node* (&root)) {
	node *rightSubTree, *rightSubTreeLeftSubtree;
	rightSubTree = root->right;
	rightSubTreeLeftSubtree = rightSubTree->left;

	rightSubTree->left = root;
	root->right = rightSubTreeLeftSubtree;
	root = rightSubTree;
	SetBalance(root->left);
	SetBalance(root);
}

void TurnRight(node* (&root)) {
	node* leftSubtree, * leftSubtreeRightSubtree;
	leftSubtree = root->left;
	leftSubtreeRightSubtree = leftSubtree->right;

	leftSubtree->right = root;
	root->left = leftSubtreeRightSubtree;
	root = leftSubtree;
	SetBalance(root->right);
	SetBalance(root);
}

void insert(node* (&root), int d) {
	if (root == NULL) {
		root = new node;
		root->value = d;
		root->balance = 0;
		root->left = NULL;
		root->right = NULL;
	}
	else {
		if (d > root->value) {
			insert(root->right, d);
			if (Height(root->right) - Height(root->left) > 1) {
				if (Height(root->right->right) < Height(root->right->left)) {
					TurnRight(root->right);
				}
				TurnLeft(root);				
			}
		}
		else {
			if (d < root->value) {
				insert(root->left, d);
				if (Height(root->left) - Height(root->right) > 1) {
					if (Height(root->left->left) < Height(root->left->right)) {
						TurnLeft(root->left);
					}
					TurnRight(root);
				}
			}
			
		}
		SetBalance(root);
	}
}

void output(node* p) {
	if (p != NULL) {
		output(p->left);
		cout << p->value << " ";
		output(p->right);
	}
}

void clear(node** p) {
	if ((*p) != NULL) {
		clear(&(*p)->left);
		clear(&(*p)->right);
	}
	delete* p;
	*p = NULL;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	int size;
	cout << "Введите количество чисел:";
	cin >> size;
	int d;
	node* root;
	root = NULL;
	for (int i = 1; i <= size; i++) {
		cout << i << " число" << ":";
		cin >> d;
		insert(root, d);
	}
	
	cout << "Распечатка дерева в симметричном порядке:" << endl;
	output(root);
	clear(&root);
	if (!root) {
		cout << endl << "Дерево успешно очищено" << endl;
	}
	else {
		cout << endl << "Ошибка удаления!" << endl;
		system("pause");
	}
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
