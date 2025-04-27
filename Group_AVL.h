#pragma once
#include "AVL_Tree.h"


template<typename K>
struct GroupAVLNode {
    K key;
    vector<DLLNode<User>*> users;
    GroupAVLNode* left;
    GroupAVLNode* right;
    int height;

    GroupAVLNode(const K& k) : key(k), left(nullptr), right(nullptr), height(1) {
    }
};

// Group AVL Tree class
template<typename K>
class GroupAVLTree {
private:
    GroupAVLNode<K>* root;

    int height(GroupAVLNode<K>* node) {
        if (node) {
            return node->height;
        }
        return 0;
    }

    int balanceFactor(GroupAVLNode<K>* node) {
        if (node) {
            return height(node->left) - height(node->right);
        }
        return 0;
    }

    void updateHeight(GroupAVLNode<K>* node) {
        if (node) {
            int leftHeight = height(node->left);
            int rightHeight = height(node->right);
            node->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
        }
    }

    GroupAVLNode<K>* rotateRight(GroupAVLNode<K>* y) {
        GroupAVLNode<K>* x = y->left;
        GroupAVLNode<K>* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    GroupAVLNode<K>* rotateLeft(GroupAVLNode<K>* x) {
        GroupAVLNode<K>* y = x->right;
        GroupAVLNode<K>* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    GroupAVLNode<K>* balance(GroupAVLNode<K>* node) {
        if (!node) return nullptr;

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

    GroupAVLNode<K>* insert(GroupAVLNode<K>* node, const K& key, DLLNode<User>* userNode) {
        if (!node) {
            node = new GroupAVLNode<K>(key);
            node->users.push_back(userNode);
            return node;
        }

        if (key < node->key) {
            node->left = insert(node->left, key, userNode);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, userNode);
        }
        else {
            node->users.push_back(userNode);
            return node;
        }

        return balance(node);
    }

    GroupAVLNode<K>* findMin(GroupAVLNode<K>* node) {
        if (node->left) {
            return findMin(node->left);
        }
        return node;
    }

    GroupAVLNode<K>* removeUser(GroupAVLNode<K>* node, const K& key, DLLNode<User>* userNode) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = removeUser(node->left, key, userNode);
        }
        else if (key > node->key) {
            node->right = removeUser(node->right, key, userNode);
        }
        else {
            // Remove the user from the vector
            for (auto it = node->users.begin(); it != node->users.end(); ++it) {
                if (*it == userNode) {
                    node->users.erase(it);
                    break;
                }
            }

            // If vector is empty, remove the node
            if (node->users.empty()) {
                if (!node->left || !node->right) {
                    GroupAVLNode<K>* temp = node->left ? node->left : node->right;

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
                    GroupAVLNode<K>* temp = findMin(node->right);
                    node->key = temp->key;
                    node->users = temp->users;
                    node->right = removeUser(node->right, temp->key, nullptr);
                }
            }
        }

        return balance(node);
    }

    GroupAVLNode<K>* search(GroupAVLNode<K>* node, const K& key) const {
        if (!node) return nullptr;

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

    void inOrder(GroupAVLNode<K>* node, std::vector<std::pair<K, std::vector<DLLNode<User>*>>>& result) const {
        if (!node) return;

        inOrder(node->left, result);
        result.emplace_back(node->key, node->users);
        inOrder(node->right, result);
    }

    void clear(GroupAVLNode<K>* node) {
        if (!node) return;

        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    GroupAVLTree() : root(nullptr) {
    }
    ~GroupAVLTree() { 
        clear(root); 
}

    void insert(const K& key, DLLNode<User>* userNode) {
        root = insert(root, key, userNode);
    }

    bool removeUser(const K& key, DLLNode<User>* userNode) {
        if (!search(key)) {
            return false;
        }
        root = removeUser(root, key, userNode);
        return true;
    }

    GroupAVLNode<K>* search(const K& key) const {
        return search(root, key);
    }

    std::vector<std::pair<K, std::vector<DLLNode<User>*>>> inOrderTraversal() const {
        std::vector<std::pair<K, std::vector<DLLNode<User>*>>> result;
        inOrder(root, result);
        return result;
    }

    void clear() {
        clear(root);
        root = nullptr;
    }

    bool isEmpty() const {
        return root == nullptr;
    }
};