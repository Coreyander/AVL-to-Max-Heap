#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <random>
#include <time.h>
#include <chrono>
using namespace std;
using namespace std::chrono;

class TreeNode {
public:
	int data;
	TreeNode* left;
	TreeNode* right;
	TreeNode() {
		data = 0;
		left = nullptr;
		right = nullptr;
	}
};

// AVL DATA STRUCTURE =================================================================================================================
class AVL {
public:
	
	AVL() {}
	TreeNode* RLRotate(TreeNode* node);
	TreeNode* RRRotate(TreeNode* node);
	TreeNode* LRRotate(TreeNode* node);
	TreeNode* LLRotate(TreeNode* node);
	int height(TreeNode* node);
	int imbalanceFactor(TreeNode* node);
	TreeNode* balance(TreeNode* node);
	TreeNode* insertion(int data, TreeNode* root);
	void traversal(int value, TreeNode* node);
	TreeNode* deletion(int value, TreeNode* node);
	TreeNode* removeSuccessor(TreeNode* node);
	
};

TreeNode* AVL::RLRotate(TreeNode* node) {
	TreeNode* temp;
	TreeNode* leftChild;

	temp = node->left;
	leftChild = temp->right;
	temp->right = NULL;
	leftChild->left = temp;
	node->left = leftChild;
	node = LLRotate(node);
	return node;
}
TreeNode* AVL::RRRotate(TreeNode* node) { 
	
	TreeNode* rightChild = new TreeNode;
	rightChild = node->right;
	node->right = rightChild->left;
	rightChild->left = node;
	return rightChild;
}
TreeNode* AVL::LRRotate(TreeNode* node) {
	TreeNode* temp;
	TreeNode* rightChild;

	temp = node->right;
	rightChild = temp->left;
	temp->left = NULL;
	rightChild->right = temp;
	node->right = rightChild;
	node = RRRotate(node);
	return node;

}
TreeNode* AVL::LLRotate(TreeNode* node) {
	TreeNode* leftChild;
	leftChild = node->left;
	node->left = leftChild->right;
	leftChild->right = node;
	return leftChild;
}
int AVL::height(TreeNode* node) {
	TreeNode* pointer;
	pointer = node;
	int right_height = 0;
	int left_height = 0;
	if (pointer != NULL) {
		while (pointer->left != nullptr) {
			++left_height;
			pointer = pointer->left;
		}
		pointer = node;
		while (pointer->right != nullptr) {
			++right_height;
			pointer = pointer->right;

		}
		if (right_height >= left_height) {
			right_height++;
			return right_height;
		}
		else if (left_height >= right_height) {
			left_height++;
			return left_height;
		}
	}
	else
		return 0;
}
int AVL::imbalanceFactor(TreeNode* node) {
	int imbalance = 0;
	int left_balance = 0;
	int right_balance = 0;
	if (node->left != nullptr)
		left_balance = height(node->left);
	if (node->right != nullptr)
	    right_balance = height(node->right);
	imbalance = left_balance - right_balance;
	return imbalance;
}
TreeNode* AVL::balance(TreeNode* node) {
	int imbalance = imbalanceFactor(node);

	if (imbalance < -1) {
		if (imbalanceFactor(node->right) >= 0)
			node = LRRotate(node);
		else                                   
			node = RRRotate(node);
	}
	else if (imbalance > 1) {
		if (imbalanceFactor(node->left) >= 0) 
			node = LLRotate(node);
		else {                                  
			node = RLRotate(node);
		}
	}
	return node;
}
TreeNode* AVL::insertion(int data, TreeNode* node) {
	//If NULL Root
	if (node == NULL) {
		TreeNode* node = new TreeNode;
		node->data = data;
		return node;
	}
	else if (node->data == NULL) {
		TreeNode* node = new TreeNode;
		node->data = data;
		return node;
	}

	//If Less Than
	else if (data < node->data) {
		node->left = insertion(data, node->left);
		node = balance(node);
	}

	//If Greater Than
	else if (data >= node->data) {
		node->right = insertion(data, node->right);
		node = balance(node);
	}
}
void AVL::traversal(int value, TreeNode* node) {
	if (value == node->data) {
		cout << node->data << " ";
		return;
	}
	if (node->left != NULL && (value < node->data)) {
		traversal(value, node->left);
		return;
	}

	if (node->right != NULL && (value > node->data)) {
		traversal(value, node->right);
		return;
	}
}
TreeNode* AVL::deletion(int value, TreeNode* node) {

	if (node == NULL)
		return node;
	if (value < node->data) {
		node->left = deletion(value, node->left);
		node = balance(node);
	}
	if (value > node->data) {
		node->right = deletion(value, node->right);
		node = balance(node);
	}
	if (value == node->data) {
		if (node->left == NULL && node->right == NULL) {
			node = NULL;
			return node;
		}
		else if (node->left != NULL && node->right == NULL) {
			node->data = node->left->data;
			node->left = NULL;
			return node;
		}
		else {
			node = removeSuccessor(node);
			return node;
		}
	}
}
TreeNode* AVL::removeSuccessor(TreeNode* node) {
	TreeNode* s;
	s = node->right;

	while (s->left != NULL) {
		s = s->left;
	}
	node->data = s->data;
	s = NULL;
	return node;



}
// ====================================================================================================================================





// MAX HEAP DATA STRUCTURE ============================================================================================================
class MaxHeap {
private:
	vector<int> heap;
public: 
	MaxHeap() {}
	void insertion(int value);
	void heapify();
	void swap(int parent, int child);
	int parent(int node);
	int leftChild(int node);
	int rightChild(int node);
	void traversal(int node);
	void deletion(int node);

};

void MaxHeap::insertion(int value) {

	if (heap.empty()) {
		heap.push_back(value);
	}
	else if (!heap.empty()) {
		heap.push_back(value);
		heapify();
	}
}
void MaxHeap::traversal(int node) {
	int level = 0;
	if (heap.empty())
		return;
	else {
		for (unsigned int i = 0; i < heap.size(); ++i) {
			if (node == heap.at(i)) {
				cout << heap.at(i) << " ";
				return;
			}
		}
		cout << "Value " << node << " not found in Max Heap." << endl;
	}
}
void MaxHeap::deletion(int node) {
	if (heap.empty()) {
		cout << "Heap has been fully deleted or is empty." << endl;
		return;
	}
	else {
		for (unsigned int i = 0; i < heap.size(); ++i) {
			if (node == heap.at(i)) {
				heap.erase(heap.begin() + i);
				heapify();
				return;
			}
		}
	}

}
void MaxHeap::heapify() {
	bool heapified = false;
	bool swapHappened = false;
	int level = heap.size() - 1; //returns level order position of the last node;
	int p;                       //p handles long parentLevels access and cleans the code;
	vector<int> parentLevels;
	while (level >= 0) {
		parentLevels.push_back(parent(level));
		level = level - 2;
	}

	//get a list of parents.
	//check the children of this list for greater than values.
	//make a new list of swapped children i.e. if a child receives a new value, add it to the list.
	//if no swap occurs, remove from the list. Continue until the list is empty, i.e every node in the heap has max heap properties.
	//Special cases: the heap is empty, the heap has only one parent.

	if (heap.size() == 0) { heapified == true; } //special case, nothing to heapify!
	while (!heapified) {
		
		for (unsigned int i = 0; i < parentLevels.size(); ++i) {
			p = parentLevels.at(i);

			if (rightChild(p) < heap.size()) {
				if (heap.at(rightChild(p)) > heap.at(p)) {
					swap(rightChild(p), p);
					parentLevels.push_back(rightChild(p));
					swapHappened = true;
				}
			}
			if (leftChild(p) < heap.size()) {
				if (heap.at(leftChild(p)) > heap.at(p)) {
					swap(leftChild(p), p);
					parentLevels.push_back(leftChild(p));
					swapHappened = true;
				}
			}
			if (!swapHappened)
				parentLevels.erase(parentLevels.begin() + i);
			swapHappened = false;

			if (heap.size() < 4) { //special case, the algorithm does not needlessly run if the heap has only 1 parent.
				i = heap.size();
				heapified = true;
			}
		}
		if (parentLevels.size() == 0) { heapified = true; }

	}
}
void MaxHeap::swap(int childIndex, int parentIndex) {
	int temp = heap.at(parentIndex);
	heap.at(parentIndex) = heap.at(childIndex);
	heap.at(childIndex) = temp;
}
int MaxHeap::parent(int node) {
	int parent;
	parent = (node - 1) / 2;
	return parent;
	}
int MaxHeap::leftChild(int node) {
	int leftChild;
	leftChild = (node * 2) + 1;
	return leftChild;
}
int MaxHeap::rightChild(int node) {
	int rightChild;
	rightChild = (node * 2) + 2;
	return rightChild;
}
// ====================================================================================================================================





void generateFiles();
void testAVL(string fileName, AVL avl, TreeNode* node);
void testMaxHeap(string filename, MaxHeap h);

int main() {
    MaxHeap h;
	AVL avl;
	TreeNode* node = new TreeNode;
	int input;
	cout << "Please choose a test: " << endl << endl;
	cout << "1. Enter 1 to test Large files only." << endl;
	cout << "2. Enter 2 to test ALL files." << endl;
	cout << endl << "Please note: running test 2 will produce all 54 run times and generate the necessary files on your computer." << endl
		<< "Running test 1 will produce no files. A copy of Large files can be found attached to this project in Canvas!" << endl;
	cin >> input;

	switch (input) {
	case 1:
		testAVL("LargeAscending.txt", avl, node);
		testAVL("LargeDescending.txt", avl, node);
		testAVL("LargeRandom.txt", avl, node);

		testMaxHeap("LargeAscending.txt", h);
		testMaxHeap("LargeDescending.txt", h);
		testMaxHeap("LargeRandom.txt", h);
		break;
	case 2:
		generateFiles();

		testAVL("SmallAscending.txt", avl, node);
		testAVL("MediumAscending.txt", avl, node);
		testAVL("LargeAscending.txt", avl, node);

		testAVL("SmallDescending.txt", avl, node);
		testAVL("MediumDescending.txt", avl, node);
		testAVL("LargeDescending.txt", avl, node);

		testAVL("SmallRandom.txt", avl, node);
		testAVL("MediumRandom.txt", avl, node);
		testAVL("LargeRandom.txt", avl, node);

		testMaxHeap("SmallAscending.txt", h);
		testMaxHeap("MediumAscending.txt", h);
		testMaxHeap("LargeAscending.txt", h);

		testMaxHeap("SmallDescending.txt", h);
		testMaxHeap("MediumDescending.txt", h);
		testMaxHeap("LargeDescending.txt", h);

		testMaxHeap("SmallRandom.txt", h);
		testMaxHeap("MediumRandom.txt", h);
		testMaxHeap("LargeRandom.txt", h);
		break;
	}

}

void testAVL(string fileName, AVL avl, TreeNode* node) {
	//For debugging: chrono auto variables_1 are for insertion, variables_2 are for traversal, variables_3 are for deletion.

	ifstream file;
	string str = "0";
	int data;
	
	file.open(fileName);
	if (!file.is_open()) {
		cout << "File " << fileName << " not found!" << endl;
		return;
	}
	cout << endl << "Beginning AVL insertion test on " << fileName << endl << endl;
	auto start_1 = high_resolution_clock::now();
	while (!file.eof()) {
		getline(file, str, ' ');
		if (str.empty())
			break;
		else
			data = stoi(str);
		node = avl.insertion(data, node);
	}
	auto stop_1 = high_resolution_clock::now();
	auto duration_1 = duration_cast<microseconds>(stop_1 - start_1);
	cout << endl << endl << "AVL insertion complete!" << endl;
	file.close();

	file.open(fileName);
	cout << endl << "Beginning AVL traversal test on " << fileName << endl << endl;
	auto start_2 = high_resolution_clock::now();
	while (!file.eof()) {
		getline(file, str, ' ');
		if (str.empty())
			break;
		else
			data = stoi(str);
		avl.traversal(data, node);
	}
	auto stop_2 = high_resolution_clock::now();
	auto duration_2 = duration_cast<microseconds>(stop_2 - start_2);
	cout << endl << endl << "AVL traversal complete!" << endl;
	file.close();

	file.open(fileName);
	cout << endl << "Beginning AVL deletion test on " << fileName << endl << endl;
	auto start_3 = high_resolution_clock::now();
	while (!file.eof()) {
		getline(file, str, ' ');
		if (str.empty())
			break;
		else
			data = stoi(str);
		node = avl.deletion(data, node);
	}
	auto stop_3 = high_resolution_clock::now();
	auto duration_3 = duration_cast<microseconds>(stop_3 - start_3);
	cout << endl << endl << "AVL deletion complete!" << endl;
	file.close();

	cout << endl << "Summary for AVL structure on " << fileName << endl;
	cout << "Time for AVL insertion on " << fileName << " data: " << duration_1.count() << " microseconds." << endl;
	cout << "Time for AVL traversal on " << fileName << " data: " << duration_2.count() << " microseconds." << endl;
	cout << "Time for AVL deletion on " << fileName << " data: " << duration_3.count() << " microseconds." << endl;
}

void testMaxHeap(string fileName, MaxHeap h) {
	//For debugging: chrono auto variables_1 are for insertion, variables_2 are for traversal, variables_3 are for deletion.

	ifstream file;
	string str = "0";
	int data;

	file.open(fileName);
	if (!file.is_open()) {
		cout << "File " << fileName << " not found!" << endl;
		return;
	}
	cout << endl << "Beginning Max Heap insertion test on " << fileName << endl << endl;
	auto start_1 = high_resolution_clock::now();
	while (!file.eof()) {
		getline(file, str, ' ');
		if (str.empty())
			break;
		else
			data = stoi(str);
		h.insertion(data);

	}
	auto stop_1 = high_resolution_clock::now();
	auto duration_1 = duration_cast<microseconds>(stop_1 - start_1);
	cout << endl << endl << "Max Heap insertion complete!" << endl;
	file.close();

	file.open(fileName);
	cout << endl << "Beginning Max Heap traversal test on " << fileName << endl << endl;
	auto start_2 = high_resolution_clock::now();
	while (!file.eof()) {
		getline(file, str, ' ');
		if (str.empty())
			break;
		else
			data = stoi(str);
		h.traversal(data);
	}
	auto stop_2 = high_resolution_clock::now();
	auto duration_2 = duration_cast<microseconds>(stop_2 - start_2);
	cout << endl << endl << "Max Heap traversal complete!" << endl;
	file.close();

	file.open(fileName);
	cout << endl << "Beginning Max Heap deletion test on " << fileName << endl << endl;
	auto start_3 = high_resolution_clock::now();
	while (!file.eof()) {
		getline(file, str, ' ');
		if (str.empty())
			break;
		else
			data = stoi(str);
		h.deletion(data);
	}
	auto stop_3 = high_resolution_clock::now();
	auto duration_3 = duration_cast<microseconds>(stop_3 - start_3);
	cout << endl << endl << "Max Heap deletion complete!" << endl;
	file.close();

	cout << endl << "Summary for Max Heap structure on " << fileName << endl;
	cout << "Time for Max Heap insertion on " << fileName << " data: " << duration_1.count() << " microseconds." << endl;
	cout << "Time for Max Heap traversal on " << fileName << " data: " << duration_2.count() << " microseconds." << endl;
	cout << "Time for Max Heap deletion on " << fileName << " data: " << duration_3.count() << " microseconds." << endl;
}

void generateFiles() {
	srand(time(NULL));
	ofstream file;
	unsigned int randomNumber;
	unsigned int ascendingNumber = 0;
	unsigned int descendingNumber = 1000;

	file.open("SmallRandom.txt");
	for (unsigned int i = 0; i < 100; ++i) {
		randomNumber = rand() % 100 + 1;
		file << randomNumber << " ";

	}
	file.close();
	file.open("MediumRandom.txt");
	for (unsigned int i = 0; i < 1000; i++) {
		randomNumber = rand() % 100 + 1;
		file << randomNumber << " ";

	}
	file.close();
	file.open("LargeRandom.txt");
	for (unsigned int i = 0; i < 10000; i++) {
		randomNumber = rand() % 100 + 1;
		file << randomNumber << " ";

	}
	file.close();
	file.open("SmallAscending.txt");
	for (unsigned int i = 0; i < 100; i++) {
		ascendingNumber = ascendingNumber + 10;
		file << ascendingNumber << " ";

	}
	file.close();
	ascendingNumber = 0;
	file.open("MediumAscending.txt");
	for (unsigned int i = 0; i < 1000; i++) {
		ascendingNumber = ascendingNumber + 10;
		file << ascendingNumber << " ";

	}
	file.close();
	ascendingNumber = 0;
	file.open("LargeAscending.txt");
	for (unsigned int i = 0; i < 10000; i++) {
		ascendingNumber = ascendingNumber + 10;
		file << ascendingNumber << " ";

	}
	file.close();
	ascendingNumber = 0;
	file.open("SmallDescending.txt");
	for (unsigned int i = 0; i < 100; i++) {
		descendingNumber = descendingNumber - 10;
		file << descendingNumber << " ";

	}
	file.close();
	descendingNumber = 10000;
	file.open("MediumDescending.txt");
	for (unsigned int i = 0; i < 1000; i++) {
		descendingNumber = descendingNumber - 10;
		file << descendingNumber << " ";

	}
	file.close();
	descendingNumber = 100000;
	file.open("LargeDescending.txt");
	for (unsigned int i = 0; i < 10000; i++) {
		descendingNumber = descendingNumber - 10;
		file << descendingNumber << " ";

	}
	file.close();

}