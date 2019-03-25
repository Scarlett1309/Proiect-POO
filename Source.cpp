#include"AVL.h"
#include <cassert>

int main() {
	AVL AVLTree;
	assert(AVLTree.getCount() == 0);

	AVLTree.insert(10);
	AVLTree.insert(20);
	AVLTree.insert(30);
	AVLTree.insert(40);
	AVLTree.insert(50);
	AVLTree.insert(25);
	assert(AVLTree.getCount() == 6);
	

	AVLTree.remove(30);
	assert(AVLTree.getCount() == 5);
	
	assert(AVLTree.search(20) == true);
	assert(AVLTree.search(7) == false);

	AVLTree.insert(10);
	assert(AVLTree.getCount() == 5);

	AVL Obj;
	Obj.insert(10);
	Obj.insert(20);
	Obj.insert(40);
	Obj.insert(50);
	Obj.insert(25);
	assert(Obj.getCount() == 5);

	assert(Obj.getCount() == AVLTree.getCount());
	
	AVL Sum;
	Sum = AVLTree + Obj;
	assert(Sum.getCount() == 5);
	AVLTree.insert(70);
	assert(AVLTree > Obj == true);
	assert(AVLTree < Obj == false);


	system("pause");
}