#include "BST.h" 
using namespace std;

int main()
{
	BST<int> a;
	cout << "Empty tree is height balanced? (Yes)" << endl;
	if (a.is_balanced() == true)
		cout << "Answer: Yes." << endl;
	else
		cout << "Answer: No." << endl;
	
	a.insert(4);
	cout << "Single node is height balanced? (Yes)" << endl;
	if (a.is_balanced() == true)
		cout << "Answer: Yes." << endl;
	else
		cout << "Answer: No." << endl;

	a.insert(3);
	cout << "Linked list of two nodes is height balanced? (Yes)" << endl;
	if (a.is_balanced() == true)
		cout << "Answer: Yes." << endl;
	else
		cout << "Answer: No." << endl;

	a.insert(2);
	cout << "Linked list of three nodes is height balanced? (No)" << endl;
	if (a.is_balanced() == true)
		cout << "Answer: Yes." << endl;
	else
		cout << "Answer: No." << endl;

	a.insert(5); a.find_and_delete_by_merging(2);
	cout << "Full binary tree of three nodes is height balanced? (Yes)" << endl;
	if (a.is_balanced() == true)
		cout << "Answer: Yes." << endl;
	else
		cout << "Answer: No." << endl;

	a.insert(6); 
	cout << "Previous tree plus one node is height balanced? (Yes)" << endl;
	if (a.is_balanced() == true)
		cout << "Answer: Yes." << endl;
	else
		cout << "Answer: No." << endl;

	a.insert(7); 
	cout << "Previous tree plus one node is height balanced? (No)" << endl;
	if (a.is_balanced() == true)
		cout << "Answer: Yes." << endl;
	else
		cout << "Answer: No." << endl;
	
	return 0;
}
