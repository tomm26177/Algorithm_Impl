#include <iostream>
#include <cstdlib> 
#include <algorithm>
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
enum Color { RED, BLACK };

template <typename T>
class Node {
public:
    bool isRed;
    T data;
    Node* left;
    Node* right;
    Node* parent;

    Node(T x, Node* p, Node* n, Color c) : data(x), left(p), right(n), parent(nullptr), isRed(c == RED) {}
};

template <typename T>
class RedBlackTree {
public:
    Node<T>* start;
    int size;
    int height;

    RedBlackTree() : size(0), height(0), start(nullptr) {}

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
        Node<T>* newNode = new Node<T>(e, nullptr, nullptr, RED);
        if (size == 0) {
            start = newNode;
            size++;
            newNode->isRed = false; // Korzeń zawsze jest czarny
        }
        else {
            Node<T>* temp = start;
            while (temp != nullptr) {
                if (e < temp->data) {
                    // e mniejsze od temp
                    if (temp->left == nullptr) {
                        temp->left = newNode;
                        newNode->parent = temp;
                        size++;
                        insertFixup(newNode);
                        break;
                    }
                    else {
                        temp = temp->left;
                    }
                }
                else {
                    // e większe lub równe temp
                    if (temp->right == nullptr) {
                        temp->right = newNode;
                        newNode->parent = temp;
                        size++;
                        insertFixup(newNode);
                        break;
                    }
                    else {
                        temp = temp->right;
                    }
                }
            }
        }
    }

    void insertFixup(Node<T>* node) {
        while (node->parent != nullptr && node->parent->isRed) {
            if (node->parent == node->parent->parent->left) {
                Node<T>* uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->isRed) {
                    node->parent->isRed = false;
                    uncle->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rotateRight(node->parent->parent);
                }
            }
            else {
                Node<T>* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->isRed) {
                    node->parent->isRed = false;
                    uncle->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                }
                else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }
                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rotateLeft(node->parent->parent);
                }
            }
        }
        start->isRed = false;
    }

    void rotateLeft(Node<T>* node) {
        Node<T>* rightChild = node->right;
        node->right = rightChild->left;
        if (rightChild->left != nullptr) {
            rightChild->left->parent = node;
        }
        rightChild->parent = node->parent;
        if (node->parent == nullptr) {
            start = rightChild;
        }
        else if (node == node->parent->left) {
            node->parent->left = rightChild;
        }
        else {
            node->parent->right = rightChild;
        }
        rightChild->left = node;
        node->parent = rightChild;
    }

    void rotateRight(Node<T>* node) {
        Node<T>* leftChild = node->left;
        node->left = leftChild->right;
        if (leftChild->right != nullptr) {
            leftChild->right->parent = node;
        }
        leftChild->parent = node->parent;
        if (node->parent == nullptr) {
            start = leftChild;
        }
        else if (node == node->parent->right) {
            node->parent->right = leftChild;
        }
        else {
            node->parent->left = leftChild;
        }
        leftChild->right = node;
        node->parent = leftChild;
    }

    void inOrderTraversal(Node<T>* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            if (node->isRed) {
                std::cout << ANSI_COLOR_RED << node->data << ANSI_COLOR_RESET << "  ";
            }
            else {
                std::cout << node->data << "  ";
            }
            inOrderTraversal(node->right);
        }
    }




    void preOrderTraversal(Node<T>* node) {
        if (node != nullptr) {
            if (node->isRed) {
                std::cout << ANSI_COLOR_RED << node->data << ANSI_COLOR_RESET << "  ";
            }
            else {
                std::cout << node->data << "  ";
            }
            preOrderTraversal(node->left);
            preOrderTraversal(node->right);
        }
    }

    void printTree(Node<T>* node, int level) {
        if (node != nullptr) {
            printTree(node->right, level + 1);
            for (int i = 0; i < level; i++) {
                std::cout << "    ";
            }

            if (node->isRed) {
                std::cout << ANSI_COLOR_RED << node->data << ANSI_COLOR_RESET << std::endl;
          
                std::cout << std::endl;
            }
            else {
                std::cout << node->data << std::endl;
            }

            printTree(node->left, level + 1);
        }
    }
};

int compareInt(const int& a, const int& b) {
    if (a > b) {
        return -1;
    }
    if (a == b) {
        return 0;
    }
    if (a < b) {
        return 1;
    }
}

void start() {
    RedBlackTree<int> tree;

    srand(static_cast<unsigned>(time(nullptr)));

    for (int i = 1; i <= 10; i++) {
        int random = (rand() % 30);
        tree.addElement(random, compareInt);
    }

    int height = tree.getHeight(tree.start);
    tree.printTree(tree.start, height);
    std::cout << "size " << tree.size<<"\n";
    tree.preOrderTraversal(tree.start);
    std::cout << "\ninOrderTraversal \n";
    tree.inOrderTraversal(tree.start);
    
}

int main() {
    start();
}
