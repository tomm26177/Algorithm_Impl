// ALGO2 IS1 214B LAB06
// Tomasz Kaminski
// kt53661@zut.edu.pl
#include <iostream>
#include "DynamicArray.cpp"

template<typename T>
class BinaryHeap {
public:
    DynamicArray<T> array;
    int sizeOfArray;

public:
    BinaryHeap() {
        sizeOfArray = 0;

            //array.addElementToEnd(NULL);

    }

    void addElement(T e) {
        array.addElementToEnd(e);
        heapifyUp(array.size - 1);
    }

    void heapifyUp(int index) {
        while (index > 0 && array.getElementFromIndex(index) > array.getElementFromIndex((index - 1) / 2)) {
            std::swap(array.array[index], array.array[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

    T removeRoot() {
        if (array.size == 0) {
            std::cout << "Kopiec jest pusty!" << std::endl;
            return T();
        }

        std::swap(array.array[0], array.array[array.size - 1]);
        array.size--;
        heapifyDown(0);
        return array.array[array.size];
    }

    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int largest = index;


        if (leftChild < array.size && array.array[leftChild] > array.array[largest]) {
            largest = leftChild;
        }


        if (rightChild < array.size && array.array[rightChild] > array.array[largest]) {
            largest = rightChild;
        }


        if (largest != index) {
            std::swap(array.array[index], array.array[largest]);
            heapifyDown(largest);
        }
    }

    void clearHeap() {
        array.clear();
    }

    void toString() {
        std::cout << "\n" ;
        if (array.size == 0) {
            std::cout << "kopiec jest pusty" << std::endl;
            return;
        }

        int currentIndex = 0;
        int levelSize = 1;

        while (currentIndex < array.size) {
            for (int i = 0; i < levelSize && currentIndex < array.size; ++i) {
                std::cout << array.array[currentIndex] << " ";
                ++currentIndex;
            }
            std::cout << std::endl;
            levelSize *= 2;
        }
        std::cout << "\n" ;
    }


};

void start() {
    BinaryHeap<int> binaryHeap;
    binaryHeap.addElement(26);
    binaryHeap.addElement(59);
    binaryHeap.addElement(27);
    binaryHeap.addElement(83);
    binaryHeap.addElement(76);
    binaryHeap.addElement(85);
    binaryHeap.addElement(24);
    binaryHeap.addElement(84);
    binaryHeap.addElement(41);
    binaryHeap.addElement(51);
    binaryHeap.addElement(40);
    binaryHeap.addElement(10);
    binaryHeap.toString();

    for(int i=0 ; i<12 ; i++){
     std::cout <<  " " << binaryHeap.removeRoot() <<" \n";
    }
    binaryHeap.toString();
}

bool compareInt(const int &o1, const int &o2) {
    return o1 > o2;
}

int main() {
    BinaryHeap<int> binaryHeap;


    clock_t startAdd = clock();

    for (int i = 0; i < 1000000; i++) {
        binaryHeap.addElement(i);

    }

    clock_t endAdd = clock();
    double add = double(endAdd - startAdd) / CLOCKS_PER_SEC;



    clock_t startRemove = clock();

    for (int i = 0; i < 1000000; i++) {
        binaryHeap.removeRoot();
    }

    clock_t endRemove = clock();


    double remove = double(endRemove - startRemove) / CLOCKS_PER_SEC;

    std::cout << "Czas dodawania: " << add << " sekund\n";
    std::cout << "Czas usuwania: " << remove << " sekund\n";
    std::cout << "Czas calkowity: " << (add + remove) << " sekund\n";
    std::cout << "Sredni czas dodawania: " << add / 1000000 << " sekund\n";
    std::cout << "Sredni czas usuwania: " << remove / 1000000 << " sekund\n";

    start();

    return 0;
}
