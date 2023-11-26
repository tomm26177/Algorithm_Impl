//
// Created by 48510 on 25.11.2023.
//


#include <iostream>
#include <string>
#include <algorithm>
#include "List.cpp"
#include <math.h>

template<typename T>
class Joint {
public:
    List<T> list;
    std::string key;
    T element;

    Joint(T e, std::string k) : element(e), key(k) {
        list.addElementToBegin(e);
    }


    Joint() : element(T()), key("") {

    }
};

template<typename T>
class HashTable {
public:
    static int sizeOfhashArray;
    int numberOfElements;
    Joint<T> *hashArray;

    HashTable() {
        sizeOfhashArray = 20;
        numberOfElements = 0;
        hashArray = new Joint<T>[sizeOfhashArray];
    }

    size_t hashfunction(std::string x) {
        size_t temp = 0;
        size_t q = x.length();
        size_t p = 1;

        for (size_t i = 0; i < x.length(); i++) {
            temp = temp + x[i] * (static_cast<size_t>(1) << (q - p++));
        }

        return temp % sizeOfhashArray;
    }

    void printTable() {

        std::cout << "\n\n\n sizeOfhashArray: " << sizeOfhashArray << "\n";
        std::cout << "\n numberOfElements " << numberOfElements << "\n";


        for (int i = 0; i < sizeOfhashArray; i++) {
            if (hashArray[i].list.size > 0) {
                std::cout << "\n" << i << ": \n";
                hashArray[i].list.printList();
                std::cout << "\n";
            }

        }
    }

    void addElement(T e, std::string k) {


        int index = hashfunction(k);
        hashArray[index].list.addElementToBegin(e);
        numberOfElements++;

        if ((sizeOfhashArray * 3) / 4 <= numberOfElements) {
            this->expandTable();
        }
    }

    void expandTable() {
        sizeOfhashArray = sizeOfhashArray * 2;

        Joint<T> *newHashArray = new Joint<T>[sizeOfhashArray];

        for (int j = 0; j < sizeOfhashArray / 2; j++) {
            Node<T> *tempNode = hashArray[j].list.Head;
            std::string tempKey = hashArray[j].key;

            while (tempNode != nullptr) {
                T data = tempNode->data;
                int index = hashfunction(tempKey) % sizeOfhashArray;

                newHashArray[index].list.addElementToBegin(data);
                newHashArray[index].key = tempKey;
                tempNode = tempNode->next;
            }
        }

        delete[] hashArray;
        hashArray = newHashArray;
    }

    Joint<T> *searchElement(std::string k) {

        int index = this->hashfunction(k) % sizeOfhashArray;

        return &hashArray[index];


    }

    int deleteElement(std::string k) {

        int index = this->hashfunction(k) % sizeOfhashArray;

        if (hashArray[index].list.size != 0) {
            Joint<T> *temp = &hashArray[index];
            temp->list.clear();
            return 1;
        }
        return 0;

    }

    void clearHash() {
        for (int i = 0; i < sizeOfhashArray; i++) {
            hashArray[i].list.clear();

        }
        delete[] hashArray;
        hashArray = nullptr;
        numberOfElements = 0;
        sizeOfhashArray = 0;
    }

    


};


void showPrintResult();

std::string generateRandomString(int length) {
    const std::string characters = "abcdefghijklmnoprstwuyz1234567890!@#$%^&*()?/.,.:;{]{}[]|*/";
    const int charactersLength = characters.length();

    std::string randomString;

    for (int i = 0; i < length; ++i) {
        int randomIndex = rand() % charactersLength;
        randomString += characters[randomIndex];
    }

    return randomString;
}


template<typename T>
int HashTable<T>::sizeOfhashArray = 0;


void testTime(int e) {
    HashTable<int> hashTable;



    clock_t start = clock();
    for (int i = 0; i < e; i++) {
        std::string key = generateRandomString(10);
        hashTable.addElement(i, key);
    }
    hashTable.addElement(1,"kluczyk");
    clock_t end = clock();
    double addElementTime = (end - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Czas dodawania elementow: " << addElementTime << " sekundy\n";


    start = clock();
    Joint<int> *searchResult = hashTable.searchElement("kluczyk");
    end = clock();
    double searchElementTime = (end - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Czas wyszukiwania elementu: " << searchElementTime << " sekundy\n";


    start = clock();
    int deleteResult = hashTable.deleteElement("kluczyk");
    end = clock();
    double deleteElementTime = (end - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Czas usuwania elementu: " << deleteElementTime << " sekundy\n";
    std::cout << "Czy usunirty zostal element? " << (deleteResult ? "Tak" : "Nie") << std::endl;


    start = clock();
    hashTable.clearHash();
    end = clock();
    double clearHashTableTime = (end - start) / (double) CLOCKS_PER_SEC;
    std::cout << "Czas czyszczenia tablicy: " << clearHashTableTime << " sekundy\n";

}

void showPrintResult() {

    HashTable<int> hashTable;

    hashTable.addElement(1,"klucz");
    hashTable.addElement(2,"ala");
    hashTable.addElement(3,"mawposiadaniu");
    hashTable.addElement(4,"kota");
    hashTable.addElement(5,"ajakwiado");
    hashTable.addElement(6,"monam");
    hashTable.addElement(7,"kottojes");
    hashTable.addElement(8,"najlepszy");
    hashTable.addElement(9,"przyjaciel");
    hashTable.addElement(10,"vczloewika");
    hashTable.addElement(11,"wspolczesnego");
    hashTable.addElement(12,"itakdalej");


    std::cout<< "\n\nwynik wyszukiwania\n";
    hashTable.searchElement("klucz")->list.printList();
    std::cout << "Czy usunirty zostal element? " << (hashTable.deleteElement("klucz") ? "Tak" : "Nie") << std::endl;
    hashTable.printTable();

    hashTable.clearHash();

    hashTable.printTable();


}


int main() {

    testTime(1000000);

    showPrintResult();




    return 0;
}


