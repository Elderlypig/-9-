#include <iostream>

struct Node {
    int data;
    Node* left;
    Node* right;
};

class BalancedBinarySearchTree {
private:
    Node* root;

public:
    BalancedBinarySearchTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = insertRecursive(root, value);
    }

    Node* insertRecursive(Node* node, int value) {
        if (node == nullptr) {
            Node* newNode = new Node;
            newNode->data = value;
            newNode->left = nullptr;
            newNode->right = nullptr;
            return newNode;
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    void remove(int value) {
        root = removeRecursive(root, value);
    }

    Node* removeRecursive(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = removeRecursive(node->left, value);
        }
        else if (value > node->data) {
            node->right = removeRecursive(node->right, value);
        }
        else {
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = minValueNode(node->right);
            node->data = temp->data;
            node->right = removeRecursive(node->right, temp->data);
        }

        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;

        while (current && current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    bool search(int value) {
        return searchRecursive(root, value);
    }

    bool searchRecursive(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (value == node->data) {
            return true;
        }

        if (value < node->data) {
            return searchRecursive(node->left, value);
        }

        return searchRecursive(node->right, value);
    }

    void printInOrder() {
        printInOrderRecursive(root);
        std::cout << std::endl;
    }

    void printInOrderRecursive(Node* node) {
        if (node != nullptr) {
            printInOrderRecursive(node->left);
            std::cout << node->data << " ";
            printInOrderRecursive(node->right);
        }
    }

    void printReverseOrder() {
        printReverseOrderRecursive(root);
        std::cout << std::endl;
    }

    void printReverseOrderRecursive(Node* node) {
        if (node != nullptr) {
            printReverseOrderRecursive(node->right);
            std::cout << node->data << " ";
            printReverseOrderRecursive(node->left);
        }
    }

    void printReverseDescendingOrder() {
        printReverseDescendingOrderRecursive(root);
        std::cout << std::endl;
    }

    void printReverseDescendingOrderRecursive(Node* node) {
        if (node != nullptr) {
            printReverseDescendingOrderRecursive(node->right);
            std::cout << node->data << " ";
            printReverseDescendingOrderRecursive(node->left);
        }
    }

    int countLeavesOnEachLevel() {
        int level = 0;
        int count = 0;
        countLeavesOnEachLevelRecursive(root, level, count);
        return count;
    }

    void countLeavesOnEachLevelRecursive(Node* node, int level, int& count) {
        if (node == nullptr) {
            return;
        }

        if (node->left == nullptr && node->right == nullptr) {
            std::cout << "Level " << level << ": " << node->data << std::endl;
            count++;
        }

        countLeavesOnEachLevelRecursive(node->left, level + 1, count);
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    BalancedBinarySearchTree tree;

   
    for (int i = -50; i <= 50; i++) {
        tree.insert(i);
    }

    
    std::cout << "Прямой обход: ";
    tree.printInOrder();

    
    std::cout << "Обратный обход: ";
    tree.printReverseOrder();

    
    std::cout << "Обратный возрастающий порядок: ";
    tree.printReverseDescendingOrder();

    
    int value = 8;
    if (tree.search(value)) {
        std::cout << "Значение " << value << " найдено в дереве" << std::endl;
    }
    else {
        std::cout << "Значение " << value << " не найдено в дереве" << std::endl;
    }

    
    tree.remove(value);

    
    std::cout << "Прямой обход после удаления значения " << value << ": ";
    tree.printInOrder();

    
    std::cout << "Число листьев на каждом уровне дерева:" << std::endl;
    int leafCount = tree.countLeavesOnEachLevel();
    std::cout << "Общее число листьев: " << leafCount << std::endl;

    return 0;
}
