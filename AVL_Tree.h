#pragma once
#include "User_DLL.h"

template<typename K, typename V>
struct AVLNode {
    K key;   // User ID
    V value;  // Pointer to User
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(const K& k, const V& v) : key(k), value(v), left(nullptr), right(nullptr), height(1) {
    }
};



template<typename K, typename V>
class AVLTree {
private:
    AVLNode<K, V>* root;

    int height(AVLNode<K, V>* node) {
        if (node) {
            return node->height;
        }
        return 0;
    }


    int balanceFactor(AVLNode<K, V>* node) {
        if (node) {
            return (height(node->left) - height(node->right));
        }
        return 0;
    }


    void updateHeight(AVLNode<K, V>* node) {
        if (node) {
            int leftHeight = height(node->left);
            int rightHeight = height(node->right);
            node->height = (1 + (leftHeight > rightHeight ? leftHeight : rightHeight));
        }
    }

    AVLNode<K, V>* rotateRight(AVLNode<K, V>* y) {
        AVLNode<K, V>* x = y->left;
        AVLNode<K, V>* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode<K, V>* rotateLeft(AVLNode<K, V>* x) {
        AVLNode<K, V>* y = x->right;
        AVLNode<K, V>* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode<K, V>* balance(AVLNode<K, V>* node) {
        if (!node) {
            return nullptr;
        }

        updateHeight(node);

        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) >= 0) {
                return rotateRight(node);
            }
            else {
                node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
        }

        if (bf < -1) {
            if (balanceFactor(node->right) <= 0) {
                return rotateLeft(node);
            }
            else {
                node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
        }

        return node;
    }

    AVLNode<K, V>* insert(AVLNode<K, V>* node, const K& key, const V& value) {
        if (!node) {
            return new AVLNode<K, V>(key, value);
        }

        if (key < node->key) {
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, value);
        }
        else {
            node->value = value;
            return node;
        }

        return balance(node);
    }

    AVLNode<K, V>* findMin(AVLNode<K, V>* node) {
        if (node->left) {
            return findMin(node->left);
        }
        return node;
    }

    AVLNode<K, V>* remove(AVLNode<K, V>* node, const K& key) {
        if (!node) {
            return nullptr;
        }

        if (key < node->key) {
            node->left = remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
        }
        else {
            if (!node->left || !node->right) {
                AVLNode<K, V>* temp = node->left ? node->left : node->right;

                if (!temp) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                }

                delete temp;
            }
            else {
                AVLNode<K, V>* temp = findMin(node->right);
                node->key = temp->key;
                node->value = temp->value;
                node->right = remove(node->right, temp->key);
            }
        }

        return balance(node);
    }

    AVLNode<K, V>* search(AVLNode<K, V>* node, const K& key) const {
        if (!node) {
            return nullptr;
        }

        if (key < node->key) {
            return search(node->left, key);
        }
        else if (key > node->key) {
            return search(node->right, key);
        }
        else {
            return node;
        }
    }

    void inOrder(AVLNode<K, V>* node, vector<pair<K, V>>& result) const {
        if (!node) {
            return;
        }

        inOrder(node->left, result);
        result.emplace_back(node->key, node->value);
        inOrder(node->right, result);
    }

    void clear(AVLNode<K, V>* node) {
        if (!node) {
            return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {
    }
    ~AVLTree() {
        clear(root);
    }

    void insert(const K& key, const V& value) {
        root = insert(root, key, value);
    }

    bool remove(const K& key) {
        if (!search(key)) {
            return false;
        }
        root = remove(root, key);
        return true;
    }

    V* search(const K& key) const {
        AVLNode<K, V>* node = search(root, key);
        if (node) {
            return &(node->value);
        }
        return nullptr;
    }

    vector<pair<K, V>> inOrderTraversal() const {
        vector<pair<K, V>> result;
        inOrder(root, result);
        return result;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    bool isEmpty() const {
        return (root == nullptr);
    }
};