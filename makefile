all: is_balanced_test number_of_leaves_test

is_balanced_test: is_balanced_test.cc BST.h
	g++ -g is_balanced_test.cc -o is_balanced_test

number_of_leaves_test: number_of_leaves_test.cc BST.h
	g++ -g number_of_leaves_test.cc -o number_of_leaves_test

clean:
	rm is_balanced_test number_of_leaves_test
	
