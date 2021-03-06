
#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <assert.h>
#include <cstdlib>

#include "HashTable.h"
#include "BinaryTree.cpp"
#include "LinkedListDouble.cpp"
#include "LinkedList.cpp"
#include "TreeAVL.cpp"
#include "Stack.h"


using namespace std;


void testStack() {
	Stack myStack;

	for (int i = 0; i < 10; i++) {
		myStack.push(i);
	}

	for (int i = 0; i < 10; i++) {
		cout << myStack.pop() << endl;
	}
}

void testBinaryTree() {

	BinaryTree<int> myTree;

	for (int i = 0; i < 10; i++) {
		myTree.insert(myTree.root, rand() % 100);
	}

	cout << myTree << endl;
}

void testLinkedListDouble() {
	LinkedListDouble<int> myList;

	for (int i = 0; i < 10; i++) {
		myList.append(rand() % 100);
	}

	myList.insert(50, 3);
	cout << myList << endl;

	myList.selectionSort(myList.head);
	cout << myList << endl;
}

template <class T>
int tertiarySearchReversed(T *A, T value, int low, int high) {
	int offset = (high - low) / 3;

	// Base cases: check points of interest
	if (A[low] == value) return low;
	if (A[low + offset] == value) return low + offset;
	if (A[high - offset] == value) return high - offset;
	if (A[high] == value) return high;

	// Return if nothing is found
	if (low >= high) return -1;

	// Recurse down portion of array via indice adjustments
	if (A[low + offset] < value) return tertiarySearchReversed(A, value, low + 1, low + offset - 1);
	if (A[high - offset] > value) return tertiarySearchReversed(A, value, high - offset + 1, high - 1);
	return tertiarySearchReversed(A, value, low + offset + 1, high - offset - 1);
}


void testLinkedList() {
	int length = 30;
	int bound = 100;
	int known_value = rand() % bound;

	int nonexistent_value = rand() % (bound - 1);
	if (nonexistent_value == known_value) nonexistent_value++;

	// Create the initial list without the nonexistent value
	LinkedList<int> myList;
	int i = 0;
	while (i < length - 1) {
		int newValue = rand() % bound;
		if (newValue != nonexistent_value) {
			myList.prepend(newValue);
			i++;
		}
	}

	// Insert the known value at a random spot in the list
	myList.insert(known_value, rand() % (length - 1));

	cout << "Original list: " << myList << endl;

	// Sort the list in reversed order
	myList.selectionSortReversed(myList.head);
	cout << "Sorted list:   " << myList << endl;

	// Convert to an array
	int* myArray = myList.to_array();

	// Find index of the known value
	int known_value_index = tertiarySearchReversed(myArray, known_value, 0, length);

	assert(myArray[known_value_index] == known_value);
	cout << "Known value " << known_value << " is at index " << known_value_index << "." << endl;

	// Find index of non-existent element
	int nonexistent_value_index = tertiarySearchReversed(myArray, nonexistent_value, 0, length);
	assert(nonexistent_value_index == -1);
	cout << "Nonexistent value " << nonexistent_value << " was not found in the array." << endl << endl;
}

void testTreeAVL() {
	// # elements to add to tree
	long int length = 1000;

	// inputs restricted to interval: [0, bound)
	long int bound = RAND_MAX;

	TreeAVL<int> myTree;
	//int zigCase1[] = { 88, 29, 64 };
	//int zigCase2[] = { 88, 29, 64, 19, 34, 63 };
	//int zigCase3[] = { 88, 29, 64, 19, 34, 33 };

	for (int i = 0; i < length; i++) {
		//myTree.insert(zigCasex[i]);
		myTree.insert(rand() % bound);
	}

	int lastValue = rand() % bound;
	myTree.insert(lastValue);
	NodeAVL<int>* lastNode = myTree.findValue(myTree.root, lastValue);

	//cout << "Inorder traversal: " << myTree << endl;
	cout << length << " nodes in the interval [0, " << bound << ")" << endl;
	cout << "Last inserted value: " << lastValue << endl;

	// I implemented the AVL tree using balance factors. 
	// The benefit of balance factors is that an AVL tree may be constructed using only two additional bits of memory overhead compared to a binary search tree.
	// I still use the algorithm discussed in class, but I have to fiddle with offsets instead of heights.

	// Unfortunately, this means heights aren't stored in the nodes, so I must compute heights here in the validation.
	while (lastNode != nullptr) {
		cout << "<" << lastNode->value << ">" << " Left height: " << myTree.height(lastNode->left) << " Right height: " << myTree.height(lastNode->right) << endl;
		lastNode = lastNode->parent;
	}
	cout << endl;
}


void testHashTable(string mode) {
	int initialSize = 53;
	int alphabetSize = 26;
	float loadFactor = 0.5;

	HashTable* table = new HashTable(mode, initialSize, alphabetSize, loadFactor);

	cout << "----" << mode << " hash table construction ----" << endl;
	cout << "Initial size: " << initialSize << endl;

	string line;
	ifstream myfile("word_list.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			table->insert(line);
		}
		myfile.close();
	}

	cout << "Collisions: " << table->collisions << endl;

	string input = "";
	cout << endl  << "Type 'Q' to escape." << endl;

	while (true) {
		cout << "Spell check a word: ";
		getline(cin, input);

		if (input == "Q" || input == "q") break;

		if (table->has(input)) cout << input << " is in the hash table." << endl << endl;
		else cout << input << " is not in the hash table." << endl << endl;
	}

	cout << endl;
}


int main() {
	srand(time(NULL));
	//testLinkedList()
	//testTreeAVL();
	//testHashTable("linear");
	//testHashTable("quadratic");
	system("PAUSE");
    return 0;
}