// ALGO2 IS1 214B LAB03
// Tomasz Kaminski
// kt53661@zut.edu.pl
//
//
#include <iostream>
#include <cstdlib> 

template <typename T>
class Node {
public:
	T data;
	Node* left;
	Node* right;
	Node* parent;


	Node(T x, Node* p, Node* n) : data(x), left(p), right(n) {}



};

template <typename T>
class BST {
public:
	Node<T>* start;
	int size;
	int height;

	BST() {
		size = 0;
		height = 0;
	}

	int getHeight(Node<T>* node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			int leftHeight = getHeight(node->left);
			int rightHeight = getHeight(node->right);
			return 1 + std::max(leftHeight, rightHeight);
		}
	}



	void addElement(T e, int (*comparator)(const T&, const T&)) {
		if (size == 0) {
			Node<T>* newNode = new Node<T>(e, nullptr, nullptr);
			start = newNode;
			size++;
		}
		else {
			Node<T>* temp = start;
			while (temp != nullptr) {
				int comparison = comparator(temp->data, e);
				if (comparison < 0) {
					//e mniejsze od temp
					if (temp->left == nullptr) {
						temp->left = new Node<T>(e, nullptr, nullptr);
						size++;
						break;
					}
					else {
						temp = temp->left;
					}
				}
				else if (comparison > 0) {
					// e wieksze od temp
					if (temp->right == nullptr) {
						temp->right = new Node<T>(e, nullptr, nullptr);
						size++;
						break;
					}
					else {
						temp = temp->right;
					}
				}
				else {
					temp->right = new Node<T>(e, nullptr, nullptr);
					break;
				}
			}
		}
	}


	void printTree(Node<T>* node, int level) {

		if (node != nullptr) {
			printTree(node->right, level + 1);
			for (int i = 0; i < level; i++) {
				std::cout << "    ";
			}
			std::cout << node->data << std::endl;
			printTree(node->left, level + 1);
		}
	}


	Node<T>* searchElement(Node<T>* temp, T data, int (*comparator)(const T&, const T&)) {
		if (temp == nullptr || comparator(temp->data, data) == 0) {
			return temp;
		}

		if (comparator(temp->data, data) < 0) {
			return searchElement(temp->left, data, comparator);
		}
		else {
			return searchElement(temp->right, data, comparator);
		}
	}








	void inOrderTraversal(Node<T>* node) {
		if (node != nullptr) {
			inOrderTraversal(node->left);
			std::cout << node->data << " ";
			inOrderTraversal(node->right);
		}
	}




	void preOrderTraversal(Node<T>* node) {
		if (node != nullptr) {
			std::cout << node->data << " ";
			preOrderTraversal(node->left);
			preOrderTraversal(node->right);
		}
	}


	void removeNode(Node<T>*& node) {
		if (node == nullptr) {
			
			return;
		}

		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			node = nullptr;
		}
		else if (node->left == nullptr) {
			Node<T>* temp = node;
			node = node->right;
			delete temp;
		}
		else if (node->right == nullptr) {
			Node<T>* temp = node;
			node = node->left;
			delete temp;
		}
		else {
			Node<T>* minRight = node->right;
			while (minRight->left != nullptr) {
				minRight = minRight->left;
			}

			node->data = minRight->data;
			removeNode(node->right);

			this->size--;

		}
	} 




	void clearTree(Node<T>* node) {
		if (node != nullptr) {
			clearTree(node->left);
			clearTree(node->right);
			delete node;
		}

		size = 0;
		start = nullptr;
	}
	};


	int compareInt(const int& a, const int& b) {
		if (a > b) {
			return -1;
		}
		if (a == b) {
			return 0;
		}
		if (a < b)
		{
			return 1;
		}
	}





	void start() {
		BST<int> bst;

		std::srand(static_cast<unsigned int>(std::time(nullptr)));

		for (int i = 0; i < 20; i++) {
			int randomValue = std::rand() % 10;
			bst.addElement(randomValue, compareInt);
		}
		int level = bst.getHeight(bst.start);
		bst.printTree(bst.start, level);


		Node<int>* result = bst.searchElement(bst.start, 1, compareInt);
		if (result != nullptr) {
			std::cout << "Znaleziono element: " << result->data << " w adresie " << result << std::endl;
		}
		else {
			std::cout << "Element nie zostal znaleziony." << std::endl;
		}
		bst.removeNode(result);
		bst.printTree(bst.start, level-1);
		std::cout << "iteracja in order: \n";
		bst.inOrderTraversal(bst.start);
		std::cout << "\n";
		std::cout << "iteracja pre order: \n";
		bst.preOrderTraversal(bst.start);
		bst.clearTree(bst.start);
		level = bst.getHeight(bst.start);
		bst.printTree(bst.start, level);



	}


	int main()
	{
		start();

	}

