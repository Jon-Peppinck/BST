#include "BST.h" 
#include <iostream>
using namespace std;

int main()
{
	BST<int> a;
	cout << "Empty tree has 0 leaf nodes. Answer: " << a.number_of_leaves() << endl;

	a.insert(4);
	cout << "Single node has 1 leaf node. Answer: " << a.number_of_leaves() << endl;

	a.insert(2);
	cout << "Linked list of 2 nodes has 1 leaf node. Answer: " 
			<< a.number_of_leaves() << endl;

	a.insert(6);
	cout << "Full binary tree of 3 nodes has 2 leaf nodes. Answer: " 
			<< a.number_of_leaves() << endl;

	a.insert(3), a.insert(1), a.insert(5), a.insert(7);
	cout << "Full binary tree of 7 nodes has 4 leaf nodes. Answer: " 
			<< a.number_of_leaves() << endl;

	a.find_and_delete_by_merging(7);
	cout << "Deleting one leaf node from the previous tree," << endl; 
	cout <<  "3 leaf nodes remain. Answer: " 
		 << a.number_of_leaves() << endl;

	a.find_and_delete_by_merging(5);
	cout << "Deleting one leaf node from the previous tree," << endl; 
	cout <<  "3 leaf nodes remain. Answer: " 
		 << a.number_of_leaves() << endl;

	a.find_and_delete_by_merging(6);
	cout << "Deleting one leaf node from the previous tree," << endl; 
	cout <<  "2 leaf nodes remain. Answer: " 
		 << a.number_of_leaves() << endl;

	return 0;
}
