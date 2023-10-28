// ConsoleApplication1.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <random>
#include <time.h>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
template <typename T>
class DynamincArray {
public:
   int size;
   int capacity;
   T* array;

    DynamincArray() {
        size = 0;
        capacity=1;
        array = new T[capacity];
    }



    

    void expandArray() {      
        T* newArray = new T[capacity * 2];
        for (int i = 0; i < size; i++) {
            newArray[i] = array[i];
           
        }
        delete[] array;
        array = newArray;
        capacity = capacity * 2;
    }

    void addElementToEnd(T e) {
        if (size >= capacity) {
            expandArray();
        }
        array[size] = e;
        size++;
    }

    T getElementFromIndex(int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        else {
            std::cout << "!!!uzytkowniku podales zly index!!! ponizszy wynik to sa losowe liczby" << "\n";
        }
      
    }

    void setElementByIndex(int index,T data) {
        if (index >= 0 && index < size) {
             array[index]=data;
        }
        else {
            std::cout << "!!!uzytkowniku podales zly index!!! " << "\n";
        }
    }
    
    void clear() {
        delete[] array; 
        size = 0;         
             
        array = new T[capacity];
    }

    void bubbleSort() {
        int i = size;
        int sorted = 0;
        while ((i > 1) && (!sorted)) {
            sorted = 1;
            for (int j = 0; j < i - 1; j++) {
                if (compareInt(array[j], array[j + 1])) {
                    std::swap(array[j], array[j + 1]);
                    sorted = 0;
                }
            }
            i--;
        }
    }

    bool compareInt(const T& o1, const T& o2) {
        return o1 > o2;
    }

    void toString() {
        std::cout <<"pojemnosc tablicy " << this->capacity << "\n";
        std::cout <<"rozmiar tablicy " << this->size << "\n";
        std::cout << "\n";
        std::cout << "[";
        for (int i = 0;i<size; i++) {
          
            std::cout << ANSI_COLOR_GREEN << array[i] << " " << ANSI_COLOR_RESET ;
        }
        std::cout << "]" << "\n";

    }

    ~DynamincArray() {
        delete[] array;
    }

};




int main()
{
    DynamincArray <int> array; 
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-1000, 1000); 


    for (int i = 0; i < 100; i++) {
        int randomValue = dist(gen);
        array.addElementToEnd(randomValue);
  }
    std::cout << ANSI_COLOR_RED << "wynik metody tostring: " << ANSI_COLOR_RESET << std::endl;

    array.toString();
    std::cout << " \n\n";
   








    
    

    clock_t  start = clock();

    int elementAtIndex = array.getElementFromIndex(0);

    clock_t  end = clock();
    double getElementFromIndexTIME = (end-start) / (double)CLOCKS_PER_SEC;

    printf("Czas zuzyty przez program: %f sekundy\n", getElementFromIndexTIME);


    std::cout << "sprawdzam element zerowy:   " << "element zerowy= " << array.getElementFromIndex(0) << "\n";





      start = clock();

    array.setElementByIndex(0, 2023);

      end = clock();
     getElementFromIndexTIME = (end - start) / (double)CLOCKS_PER_SEC;

    printf("Czas zuzyty przez program: %f sekundy\n", getElementFromIndexTIME);






  
    std::cout << "ustawiam element zerowy na liczbe 2023:   " << "element zerowy= " << array.getElementFromIndex(0) << "\n";

  
    std::cout << "\n\n\nsortowanie tablicy: \n";


    start = clock();

    array.bubbleSort();

    end = clock();
    getElementFromIndexTIME = (end - start) / (double)CLOCKS_PER_SEC;

    printf("Czas zuzyty przez program: %f sekundy\n", getElementFromIndexTIME);
    
    array.toString();


    std::cout << ANSI_COLOR_RED << "\n\nczyscimy wszystkie elementy z tablicy:" << ANSI_COLOR_RESET << std::endl;


    start = clock();

    array.clear();

    end = clock();
    getElementFromIndexTIME = (end - start) / (double)CLOCKS_PER_SEC;

    printf("Czas zuzyty przez program: %f sekundy\n", getElementFromIndexTIME);



    
    array.toString();



    
}

