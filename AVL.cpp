#include "AVL.h"

// Constructor fara parametri
AVL::AVL() {
	root = NULL;
	count = 0;
}

// Contructor cu un parametru
AVL::AVL(int x) {
	root = new Node;
	root->key = x;
	root->height = 0;
	count = 1;
}

// Constructor de copiere 
AVL::AVL(const AVL &a) {
	root = NULL;
	count = 0;
	Node **stack = new Node*[a.count];
	int stack_size = 0;
	stack[stack_size++] = a.root;
	while (stack_size > 0) {
		Node *p = stack[--stack_size];
		insert(p->key);
		if (p->right != NULL)
			stack[stack_size++] = p->right;
		if (p->left != NULL)
			stack[stack_size++] = p->left;
	}
	delete[] stack;
	count = a.count;
}

// Destructorul ce elibereaza memoria
AVL::~AVL() {
	clear(root);
}

// Metoda pentru inserarea unui nod intr-un arbore AVL
AVL::Node* AVL::insert(int x, Node* t) {
	
	// Inseram nodurile ca la un BST, iar apoi vedem daca arborele este echilibrat
	if (t == NULL) {
		t = new Node;
		t->key = x;
		t->height = 0;
		t->left = t->right = NULL;
		count++;
	}
	else if (x < t->key) {
		t->left = insert(x, t->left);
		if (getHeight(t->left) - getHeight(t->right) == 2) {
			if (x < t->left->key)
				t = singleRightRotate(t);
			else
				t = doubleRightRotate(t);
		}
	}
	else if (x > t->key) {
		t->right = insert(x, t->right);
		if (getHeight(t->right) - getHeight(t->left) == 2) {
			if (x > t->right->key)
				t = singleLeftRotate(t);
			else
				t = doubleLeftRotate(t);
		}
	}
	
	// Actualizam inaltimea nodului stramos
	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
	return t;
}

// Metoda pentru stergerea unui nod dintr-un arbore AVL
AVL::Node* AVL::remove(int x, Node* t) {
	Node* temp;

	// Elementul nu a fost gasit
	if (t == NULL)
		return NULL;

	// Cautam elementul
	else if (x < t->key)
		t->left = remove(x, t->left);
	else if (x > t->key)
		t->right = remove(x, t->right);

	//Daca elementul are 2 fii
	else if (t->left && t->right)
	{
		temp = findMin(t->right);
		t->key = temp->key;
		t->right = remove(t->key, t->right);
	}
	// Daca elementul are un fiu sau 0
	else
	{
		temp = t;
		if (t->left == NULL)
			t = t->right;
		else if (t->right == NULL)
			t = t->left;
		delete temp;

	}
	if (t == NULL)
		return t;


	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;

	// Daca arborele nu este echilibrat
	// Daca nodul din stanga este sters
	if (getHeight(t->left) - getHeight(t->right) == 2)
	{
		// right right case
		if (getHeight(t->left->left) - getHeight(t->left->right) == 1)
			return singleLeftRotate(t);
		// right left case
		else
			return doubleLeftRotate(t);
	}
	// Daca nodul din dreapta este sters
	else if (getHeight(t->right) - getHeight(t->left) == 2)
	{
		// left left case
		if (getHeight(t->right->right) - getHeight(t->right->left) == 1)
			return singleRightRotate(t);
		// left right case
		else
			return doubleRightRotate(t);
	}

	return t;
}

// Metoda pentru cautarea unui nod intr-un arbore
// returneaza true -> daca este gasit
// false -> in caz contrar
bool AVL::search(int x, Node *t) {
	if (t == NULL)
		return false;

	if (x > t->key)
		return search(x, t->right);
	
	if (x < t->key)
		return search(x, t->left);
	
	return true;
}

AVL::Node* AVL::singleRightRotate(Node* &t) {
	
	// Rotim arborele
	Node* u = t->left;
	t->left = u->right;
	u->right = t;
	
	// Actualizam inaltimea
	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
	u->height = max(getHeight(u->left), t->height) + 1;

	// Returnam noua radacina
	return u;
}

AVL::Node* AVL::singleLeftRotate(Node* &t) {
	// Rotim arborele
	Node* u = t->right;
	t->right = u->left;
	u->left = t;
	
	// Actualizam inaltimea
	t->height = max(getHeight(t->left), getHeight(t->right)) + 1;
	u->height = max(getHeight(t->right), t->height) + 1;
	
	// Returnam noua radacina
	return u;
}

AVL::Node* AVL::doubleLeftRotate(Node* &t) {
	t->right = singleRightRotate(t->right);
	return singleLeftRotate(t);
}

AVL::Node* AVL::doubleRightRotate(Node* &t) {
	t->left = singleLeftRotate(t->left);
	return singleRightRotate(t);
}

// Metode pentru gasirea valorii minimale si maximale dintr-un nod

// 1. Pentru valoarea minimala, cautam cel mai din stanga nod
AVL::Node* AVL::findMin(Node* t) {
	if (t == NULL)
		return NULL;
	else if (t->left == NULL)
		return t;
	else
		return findMin(t->left);
}

// 2. Pentru valoarea maximala, cautam cel mai din dreapta nod
AVL::Node* AVL::findMax(Node* t) {
	if (t == NULL)
		return NULL;
	else if (t->right == NULL)
		return t;
	else
		return findMax(t->right);
}

int AVL::getHeight(Node* t) {
	return (t == NULL ? -1 : t->height);
}

int AVL::getCount() {
	return count;
}

// Functie pentru gasirea maximului intre 2 numere intregi
int AVL::max(int a, int b) {
	return (a > b) ? a : b;
}

// Metoda pentru golirea arborelui
void AVL::clear(Node* t) {
	if (t == NULL)
		return;
	clear(t->left);
	clear(t->right);
	delete t;
}

void AVL::insert(int x) {
	root = insert(x, root);
}

void AVL::remove(int x) {
	root = remove(x, root);
	count--;
}

bool AVL::search(int x) {
	return search(x, root);
}

// Metode pentru parcurgerile in :
// 1. Preordine
void AVL::preOrder(Node *t) {
	if (t != NULL) {
		cout << t->key << " ";
		preOrder(t->left);
		preOrder(t->right);
	}
}

void AVL::preOrder() {
	preOrder(root);
}

// 2. Postordine
void AVL::postOrder(Node *t) {
	if (t != NULL) {
		postOrder(t->left);
		postOrder(t->right);
		cout << t->key << " ";
	}
}

void AVL::postOrder() {
	postOrder(root);
}

// 3. Inordine
void AVL::inOrder(Node *t) {
	if (t != NULL) {
		inOrder(t->left);
		cout << t->key << " ";
		inOrder(t->right);
	}

}

void AVL::inOrder() {
	inOrder(root);
}

// Metoda pentru transformarea unui arbore intr-un vector
// printr-o parcurgere in preordine
int* AVL::avlToArray() {
	if (root == NULL) {
		return NULL;
	}
	Node** stack = new Node*[count];
	int *vector = new int[count], vector_size = 0;
	unsigned stack_size = 0;   

	// Inseram radacina in stiva
	stack[stack_size++] = root;           
	while (stack_size > 0) { 
		// Cat timp stiva nu este vida
		// Inseram valoarea nodului intr-un vector
		Node* p = stack[--stack_size];         
		vector[vector_size++] = p->key;    
		
		// In cazul in care nodul are fiu stang sau drept ii inseram 
		// in stiva in ordinea : mai intai cel drept, iar apoi cel stang,
		// incat cel stang(avand valoarea mai mica) este primul scos din stiva
		if (p->right != NULL)            
			stack[stack_size++] = p->right;    
		
		if (p->left != NULL) {                 
			stack[stack_size++] = p->left;     
		}                                      
	}
	delete[] stack;  
	//returnam vectorul ce contine elementele in preordine
	return vector;
}


// Supraincarcarea operatorilor : 
// "=" -> copiaza continutul altui arbore
AVL AVL::operator=(AVL a) {
	clear(root);
	
	Node **stack = new Node*[a.count];
	int stack_size = 0;
	stack[stack_size++] = a.root;
	while (stack_size > 0) {
		Node*p = stack[--stack_size];
		insert(p->key);
		if (p->right != NULL)
			stack[stack_size++] = p->right;
		if (p->left != NULL)
			stack[stack_size++] = p->left;
	}
	delete[] stack;
	count = a.count;

	return *this;
}

// "+" -> realizeaza reuniunea intre doi arbori, fara duplicate
AVL AVL::operator+(AVL a) {
	AVL temp(a);
	int *v = avlToArray();
	for (int i = 0; i < count; i++)
		temp.insert(v[i]);

	delete[] v;
	return temp;
}

// "-" -> realizeaza diferenta intre doi arbori
AVL AVL::operator-(AVL a) {
	AVL temp(*this);

	int *v = avlToArray();
	for (int i = 0; i < count; i++)
	
		temp.remove(v[i]);
	
	delete[] v;
	return temp;
}

// "<" -> true daca elementul maximal al primului arbore este mai mic
//		decat elementul maximal al celui de al doilea arbore
//	 -> false in caz contrar
bool AVL::operator<(AVL a) {
	return findMax(root)->key < a.findMax(a.root)->key;
}

// ">" -> true daca elementul maximal al primului arbore este mai mare
//		  decat elementul maximal al celui de al doilea arbore
// 	   -> false in caz contrar
bool AVL::operator>(AVL a) {
	return findMax(root)->key > a.findMax(a.root)->key;
}

// << -> scrie elementele unui arbore
ostream &operator<<(ostream &out, AVL &a) {
	if (a.count == 0) {
		cout << "Arbore vid \n";
		return out;
	}

	cout << "Arborele este : \n";
	a.preOrder();
	return out;

}

// >> -> citeste elementele arborelui de la tastatura
istream &operator>>(istream &in, AVL &a) {
	a.clear(a.root);
	
	int x, nr;
	cout << "Numarul de noduri este : ";
	cin >> nr;

	for (int i = 0; i < nr; i++) {
		cin >> x;
		a.insert(x);
	}
	return in;

}
