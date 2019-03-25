#pragma once
#include <iostream>
using namespace std;

class AVL {
	struct Node{
		int key;
		Node *left, *right;
		int height;
	};
	Node* root;
	int count;

	void clear(Node*);
	int max(int, int);
	int getHeight(Node*);
	Node* findMin(Node*);
	Node* findMax(Node*);
	
	Node* insert(int, Node*);
	Node* remove(int, Node*);
	bool search(int, Node*);
	
	Node* singleRightRotate(Node*&);
	Node* singleLeftRotate(Node*&);
	Node* doubleLeftRotate(Node*&);
	Node* doubleRightRotate(Node*&);
	
	void preOrder(Node*);
	void postOrder(Node*);
	void inOrder(Node*);

	int* avlToArray();

public:
	//constructori + destructor 
	AVL();
	AVL(int);
	AVL(const AVL&);
	~AVL();
	
	void insert(int);
	void remove(int);
	bool search(int);
	int getCount();

	//parcurgerile SDR, SRD, RSD 
	void preOrder();
	void postOrder();
	void inOrder();

	//supraincarcarea operatorilor
	AVL operator=(AVL);
	AVL operator+(AVL);
	AVL operator-(AVL);
	bool operator<(AVL);
	bool operator>(AVL);
	friend ostream &operator<<(ostream&, AVL&);
	friend istream &operator>>(istream&, AVL&);

};