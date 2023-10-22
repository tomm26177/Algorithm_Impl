#include <iostream>
#include <string>
#include <algorithm>




template <typename T>
class Node {
public:
	T data;
	Node* previous;
	Node* next;


	Node(T x, Node* p, Node* n) : data(x), previous(p), next(n) {}

	
	
};

template <typename T>
class List {
public:
	Node<T> *Head;
	Node<T> *Tail;
	int size;
public:
 	List(){

		Head = nullptr;
		Tail = nullptr;
		size = 0;
	}

	void addElementToEnd(T e) {
		Node<T>* newNode = new Node<T>(e, nullptr, nullptr);
		if (size == 0) {
			Head = newNode;
			Tail = newNode;
		}
		else
		{
			newNode->next = Tail;
			Tail->previous = newNode;
			Tail = newNode;
			
		}
		size++;
	}


	
	void addElementToBegin(T e) {
		Node<T>* newNode = new Node<T>(e, nullptr, nullptr);
		if (size == 0) {
			Head = newNode;
			Tail = newNode;
		}
		else
		{
			newNode->previous = Head;
			Head->next = newNode;
			Head = newNode;
			
		}
		size++;
	}


	void removeLastElement() {
		if (size == 0) {
			return;
		}

		if (size == 1) {
			delete Head;
			delete Tail;
			Head = nullptr;
			Tail = nullptr;
		}
		else {
			Node<T>* newTail = Tail->next;
			delete Tail;
			newTail->previous = nullptr;
			Tail = newTail;
		}

		size--;

	}

	void removeFirstElement() {
		if (size == 0) {
			return;
		}

		if (size == 1) {
			delete Head;
			delete Tail;
			Head = nullptr;
			Tail = nullptr;
		}
		else {
			Node<T>* newTail = Head->previous;
			delete Head;
			newTail->next = nullptr;
			Head = newTail;
		}

		size--;

	}

	T getElementByIndex(int n) {
		try {
			if (n < 0 || n >= size) {
				throw std::out_of_range("Indeks out of range"); 
			}
			Node<T>* temp = Head;
			for (int i = 0; i < n; i++) {
				temp = temp->previous;
			}
			return temp->data;
		}
		catch (const std::out_of_range& ex) {
			
			std::cerr << "exception w getElementByIndex: " << ex.what() << std::endl;
			
		}
	}
	void setElementByIndex(int n, T e) {
		try {
			if (n < 0 || n >= size) {
				throw std::out_of_range("Indeks out of range");
			}
			Node<T>* temp = Head;
			for (int i = 0; i < n; i++) {
				temp = temp->previous;
			}
			temp->data = e;
		}
		catch (const std::out_of_range& ex) {

			std::cerr << "exception w getElementByIndex: " << ex.what() << std::endl;

		}
	}

	Node<T>* findElement(const T& dataToFind, bool (*comparator)(const T&, const T&)) {
		Node<T>* temp = Head;
		while (temp != nullptr) {
			if (comparator(temp->data, dataToFind)) {
				return temp;
			}
			temp = temp->previous;
		}
		return nullptr; 
	}


	void removeElement(const T& dataToFind, bool (*comparator)(const T&, const T&)) {
		Node<T>* temp = Head;
		for (int i = 0; i < size;i++) {	
			if (comparator(temp->data, dataToFind)) {
				if (i==0)
				{
					this->removeFirstElement();
					return;
				}
				if (i == size-1) {
					this->removeLastElement();
					return;
				}
				Node<T>*  previous = temp->previous;
				Node<T>* next = temp->next;

				
					previous->next = next;			
					next->previous = previous;
					
			
				size--;
				delete temp;
				return;
			}
			temp = temp->previous;
		}
	}

	


	void clear() {
		for (int i = 0; i < size; i++) {
			Node<T>* temp = Head;
			Head = Head->previous;
			delete temp;
		}
		Tail = nullptr;
		size = 0;
	}

	void printList() {
	
		
		Node<T>* temp = Head;
		for(int i = 0; i < size; i++) {
			
			std::cout  << " element nr "<<i+1 << ":	" << temp->data << "\n";
			temp = temp->previous;
		}
	}
	
};

bool compareInt(const int& a, const int& b) {
	return a == b; 
}







int main() {
	List <int> list;
	
	list.addElementToBegin(3);
	list.addElementToBegin(2);
	list.addElementToBegin(1);
	list.addElementToEnd(4);
	list.addElementToEnd(5);
	list.addElementToEnd(6);

	

	int elementToFind = 6;
	Node<int>* foundElement = list.findElement(elementToFind, compareInt);
	
	list.removeElement(elementToFind, compareInt);
	
	//list.clear();


	
	
	list.printList();


	std::cout << "list size: " << list.size << "\n";




}




}
