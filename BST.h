#include <queue>
#include <stack>
#include <iostream>
#include <vector>
#include <stdlib.h>

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE

template<class T>
class Stack: public std::stack<T> {
public:
    T pop() { T tmp = std::stack<T>::top(); std::stack<T>::pop(); return tmp; }
};

template<class T>
class Queue: public std::queue<T> {
public:
    T dequeue() { T tmp = std::queue<T>::front(); std::queue<T>::pop(); return tmp; }
    void enqueue(const T& el) { push(el); }
};

template<class T>
class BSTNode {
public:
    BSTNode() { left = right = 0; }
    BSTNode(const T& e, BSTNode<T> *l = 0, BSTNode<T> *r = 0) 
		{ el = e, left = l, right = r; }
	T el;
    BSTNode<T> *left, *right;
};

template<class T>
class BST {
public:
	BST() { root = 0; }
	~BST() { clear(); }
	void clear() { clear(root), root = 0; }
	bool is_empty() const { return root == 0; }
	void preorder() { preorder(root); }
	void inorder() { inorder(root); }
	void postorder() { postorder(root); }
	void insert(const T&);
	T* search(const T& el) const { return search(root, el); }
	void find_and_delete_by_copying(const T&);
	void find_and_delete_by_merging(const T&);
	void breadth_first();
	void balance(std::vector<T>, int, int);
	bool is_balanced() const { return is_balanced(root) >= 0; } 
	int number_of_leaves() const { return number_of_leaves(root); }					
	T* recursive_search(const T& el) const { return recursive_search(root, el); }	
	void recursive_insert(const T& el) { recursive_insert(root, el); }				
protected:
    void clear(BSTNode<T>*);
    T* search(BSTNode<T>*, const T&) const;
    void preorder(BSTNode<T>*);
    void inorder(BSTNode<T>*);
    void postorder(BSTNode<T>*);
    virtual void visit(BSTNode<T>* p) // virtual allows re-definition in derived classes
		{ std::cout << p->el << " "; } 
		void delete_by_copying(BSTNode<T>*&);
		void delete_by_merging(BSTNode<T>*&);
		int is_balanced(BSTNode<T>*) const;					
		int number_of_leaves(BSTNode<T>*) const;		
		void recursive_insert(BSTNode<T>*&, const T&);		
		T* recursive_search(BSTNode<T>*, const T&) const;	

		BSTNode<T>* root;
};

#endif

template<class T>
void BST<T>::clear(BSTNode<T> *p) 
{
    if (p != 0) {
   		clear(p->left);
       	clear(p->right);
    	delete p;
	}
}

template<class T>
void BST<T>::insert(const T& el) 
{   
    BSTNode<T> *p = root, *prev = 0;
    while (p != 0) {  // find a place for inserting new node;
       	prev = p;
        if (el < p->el)
        	p = p->left;
        else 
			p = p->right;
    }
    if (root == 0)    // tree is empty;
       	root = new BSTNode<T>(el);
    else if (el < prev->el)
      	prev->left  = new BSTNode<T>(el);
    else 
		prev->right = new BSTNode<T>(el);
}

template<class T>
T* BST<T>::search(BSTNode<T>* p, const T& el) const 
{
    while (p != 0) {
      	if (el == p->el)
       		return &p->el;
        else if (el < p->el)
          	p = p->left;
        else 
			p = p->right;
	}
    return 0;
}

template<class T>
void BST<T>::inorder(BSTNode<T> *p) 
{
     if (p != 0) {
       	inorder(p->left);
       	visit(p);
       	inorder(p->right);
     }
}

template<class T>
void BST<T>::preorder(BSTNode<T> *p) 
{
    if (p != 0) {
    	visit(p);
        preorder(p->left);
        preorder(p->right);
    }
}

template<class T>
void BST<T>::postorder(BSTNode<T>* p) 
{
    if (p != 0) {
   		postorder(p->left);
        postorder(p->right);
        visit(p);
    }
}

template<class T>
void BST<T>::delete_by_copying(BSTNode<T>*& node) 
{    
    BSTNode<T> *previous, *tmp = node;
  	if (node->right == 0)                  // node has no right child;
    	node = node->left;
	else if (node->left == 0)              // node has no left child;
      	node = node->right; 
	else {
		tmp = node->left;                 // node has both children;
		previous = node;                  
		while (tmp->right != 0) { 		  
			previous = tmp;
			tmp = tmp->right;
		}
		node->el = tmp->el;               
		if (previous == node)
			previous->left  = tmp->left;
		else 
			previous->right = tmp->left;  
     }
     delete tmp;                          
}

// find_and_delete_by_copying() searches the tree to locate the node containing
// el. If the node is located, the function delete_by_copying() is called.
template<class T>
void BST<T>::find_and_delete_by_copying(const T& el) 
{    
	BSTNode<T> *p = root, *prev = 0;
	while (p != 0 && !(p->el == el)) {
		prev = p;
		if (el < p->el)
			p = p->left;
	 	else p = p->right;
	}
	if (p != 0 && p->el == el) {
		if (p == root)
 			delete_by_copying(root);
  	 		else if (prev->left == p)
         		delete_by_copying(prev->left);
       		else 
				delete_by_copying(prev->right);
	}
    else if (root != 0)
		std::cout << "el " << el << " is not in the tree" << std::endl;
    else 
		std::cout << "the tree is empty" << std::endl;
}

template<class T>
void BST<T>::delete_by_merging(BSTNode<T>*& node) 
{   
	BSTNode<T> *tmp = node;
    if (node != 0) {
  		if (!node->right)           // node has no right child: its left
       		node = node->left;      // child (if any) is attached to its parent;
        else if (node->left == 0) // node has no left child: its right
       		node = node->right;     // child is attached to its parent;
        else {                    // be ready for merging subtrees;
        	tmp = node->left;       // move left
           	while (tmp->right != 0) // and then right as far as possible;
           		tmp = tmp->right;
           	tmp->right =          // establish the link between the
             	node->right;        // the rightmost node of the left
                                  // subtree and the right subtree;
             tmp = node;            
             node = node->left;     
        }
        delete tmp;                
	}
}

template<class T>
void BST<T>::find_and_delete_by_merging(const T& el) 
{    
 	BSTNode<T> *node = root, *prev = 0;
    while (node != 0) {
  		if (node->el == el)
       		break;
        prev = node;
        if (el < node->el)
        	node = node->left;
        else 
			node = node->right;
    }
    if (node != 0 && node->el == el) {
    	if (node == root)
        	delete_by_merging(root);
       	else if (prev->left == node)
          	delete_by_merging(prev->left);
       	else 
			delete_by_merging(prev->right);
	}
    else if (root != 0)
     	std::cout << "el " << el << " is not in the tree" << std::endl;
    else 
		std::cout << "the tree is empty" << std::endl;
}

template<class T>
void BST<T>::breadth_first() 
{    
  	Queue<BSTNode<T>*> queue;
 	BSTNode<T> *p = root;
    if (p != 0) {
   		queue.enqueue(p);
        while (!queue.empty()) 
		{
       		p = queue.dequeue();
            visit(p);
            if (p->left != 0)
				queue.enqueue(p->left);
            if (p->right != 0)
            	queue.enqueue(p->right);
        }
    }
}

template<class T>
void BST<T>::balance (std::vector<T> data, int first, int last) 
{
    if (first <= last) {
  		int middle = (first + last)/2;
        insert(data[middle]);
        balance(data,first,middle-1);
        balance(data,middle+1,last);
    }
}

template<class T>
void BST<T>::recursive_insert(BSTNode<T>*& p, const T& el) 
{
 	if (p == 0)		 									// Anchor case, tail recursion
  		p = new BSTNode<T>(el);
    else if (el < p->el)
      	recursive_insert(p->left, el);
    else 
		recursive_insert(p->right, el);
}

template<class T>
T* BST<T>::recursive_search(BSTNode<T>* p, const T& el) const 
{
	if (p != 0) {				
  		if (el == p->el)								// Anchor case, tail recursion
      		return &p->el;
   		else if (el < p->el)
           	return recursive_search(p->left, el);
      	else 
			return recursive_search(p->right, el);
	}
  	else 
		return 0;
}
// Q1
template<class T>
int BST<T>::number_of_leaves(BSTNode<T>* p) const
{
	if(p == 0)
	// No leaves					
		return 0;
	else if (p->left == 0 && p->right == 0)
	// leaf node occurs when both left and right child nodes are null
		return 1;
	else
	// Return the sum of all leaves by recursively calling number of leaves nodes for left and right subtrees
		return number_of_leaves(p->left) + number_of_leaves(p->right);
}
// Q2
template<class T>
int BST<T>::is_balanced(BSTNode<T>* p) const
{
	// Anchor case
	if(p == 0)
	// Height balanced							
		return 0;
	else {
		int left = is_balanced(p->left);
		int right = is_balanced(p->right);
		// if left or right is -1 as a result of recursion it implies the BT is unbalanced
		if (left == -1 || right == -1) 
			return -1;
		// Not balanced if left and right have a difference in height of more than 1
		if (abs(left-right) > 1) 
			return -1;
		// If left tree is bigger than right it must be only 1 bigger
		if (left > right) 
			return left+1;
		else
		// otherwise right tree is only 1 bigger
			return right+1;
	}
}
