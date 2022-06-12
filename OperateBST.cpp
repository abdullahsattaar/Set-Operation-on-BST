#include<iostream>
using namespace std;

class Set
{
	struct bst 
	{
		int value;
		bst* leftChild;
		bst* rightChild;
		bst() 
		{
			value = 0;
			leftChild = 0;
			rightChild = 0;
		}
		
	}
	*root;

public:

	void addElementInOrder(int x) 
	{
		bst* newNode;
		newNode->value = x;
		bst* parent = root;
		bst* child = root;
		while (child) 
		{
			parent = child;
			if (parent->value > x)
				child = child->leftChild;
			else if (parent->value <= x)
				child = child->rightChild;
		}
		if (parent == NULL)
			root = newNode;
		else if (parent->value > x)
			parent->leftChild = newNode;
		else if (parent->value <= x)
			parent->rightChild = newNode;
	} 
	
	void printSet(bst* t)  // RECURSIVE PRINT
	{
		if (t)
		{
			printSet(t->leftChild);
			cout << t->value << " ";
			printSet(t->rightChild);
		}
	}
		// wrappper function
	void printSet()
	{
		printSet(root);
	}

	Set unionbst(const Set& obj) 
	{
		this->mergeTrees(this->root, obj.root, 0, 0);
	}

	Set intersectionbst(Set& obj, bst* root1, bst* root2)
	{
		if (root1 == NULL) {
			//  cout<<"Tree 1 node is null , returning"<<endl;  
			return;
		}
		if (root2 == NULL) {
			//  cout<<"Tree 2 node is null , returning"<<endl;  
			return;
		}
		//cout<<"Comparing tree 1 : "<<root1->data<< "   and tree 2 : " << root2->data<<endl;
		if (root1->value == root2->value) {
			//  cout<<"tree 1 equal to tree 2 "<<endl;
			insert(root1->value);
			//  cout<<"Inserting in new tree : "<<root1->data<<endl;
			intersectionbst(root1->leftChild, root2->leftChild);
			intersectionbst(root1->rightChild, root2->rightChild);
		}
		else if (root1->value > root2->value) {
			//  cout<<"tree 1 > tree 2 "<<endl;
			intersectionbst(root1, root2->rightChild);
			intersectionbst(root1->leftChild, root2);
		}
		else  {
			//  cout<<"tree 1 < tree 2 "<<endl;
			intersectionbst(root1->rightChild, root2);
			intersectionbst(root1, root2->leftChild);
		}
		return obj;
	}
	Set intersectionbst(Set& obj)
	{
		Set obj = intersectionbst(obj, root, this->root);
		return obj;
	}

	Set()
	{
		root = nullptr;
	}
	bst* copyAux(bst* obj) 
	{
		if (!obj)
		{
			this == nullptr;
		}
		root->value = obj->value;
		addElementInOrder(root->value);
		root->leftChild = copyAux(obj->leftChild);
        root->rightChild = copyAux(obj->rightChild);

		return nullptr;
	}
	Set(const Set* obj) 
	{
		this->copyAux(obj->root);
	}//copy constructor


	void Destructor(bst* t)
	{
		if (t) 
		{
			Destructor(t->leftChild);
			Destructor(t->rightChild);
			delete t;
		}
	}
	~Set() // Recursive Destructor
	{
		Destructor(root);
	}
};


int main()
{
	Set s1;
	s1.addElementInOrder(10);
	s1.addElementInOrder(5);
	s1.addElementInOrder(30);
	Set s2;
	s1.addElementInOrder(10);
	s1.addElementInOrder(30);
	s1.addElementInOrder(50);
	s1.printSet(); //prints 5 10 30
	s2.printSet(); // prints 10 30 50
	Set s3 = s1.intersectionbst(s2);
	s3.printSet(); //prints 10 30
	Set s4 = s1.unionbst(s2);
	s4.printSet(); //prints 5 10 30 50
	system("pause");
	return 0;
}