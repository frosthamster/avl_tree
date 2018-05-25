#ifndef AVL_TREE_H
#define AVL_TREE_H

template<class T>
class AVLTree {
public:
    explicit AVLTree(T key) {
        AVLTree::key = key;
        left = right = nullptr;
        height = 1;
    }

    unsigned char get_height() {
        return height;
    }

    bool contains(T key){
        return contains(this, key);
    }

    T get_value(){
        return key;
    }

    AVLTree *insert(T key) {
        return insert(this, key);
    }

    AVLTree *remove(T key) {
        return remove(this, key);
    }

private:
    T key;
    unsigned char height;
    AVLTree *left;
    AVLTree *right;

    unsigned char get_height(AVLTree *p) {
        return static_cast<unsigned char>(p ? p->height : 0);
    }

    int get_balance_factor() {
        return get_height(right) - get_height(left);
    }

    void update_height() {
        unsigned char right_height = get_height(left);
        unsigned char left_height = get_height(right);
        height = static_cast<unsigned char>((right_height > left_height ? right_height : left_height) + 1);
    }

    bool contains(AVLTree *tree, T key){
        if(tree->key == key)
            return true;
        if(key < tree->key && tree->left != nullptr)
            return contains(tree->left, key);
        if(key > tree->key && tree->right != nullptr)
            return contains(tree->right, key);
        return false;
    }

    AVLTree *rotate_right() {
        auto *new_root = left;
        left = new_root->right;
        new_root->right = this;
        update_height();
        new_root->update_height();
        return new_root;
    }

    AVLTree *rotate_left() {
        auto *new_root = right;
        right = new_root->left;
        new_root->left = this;
        update_height();
        new_root->update_height();
        return new_root;
    }

    AVLTree *balance() {
        update_height();
        if (get_balance_factor() == 2) {
            if (right->get_balance_factor() < 0)
                right = right->rotate_right();
            return rotate_left();
        }
        if (get_balance_factor() == -2) {
            if (left->get_balance_factor() > 0)
                left = left->rotate_left();
            return rotate_right();
        }
        return this;
    }

    AVLTree *insert(AVLTree *tree, T key) {
        if (!tree) return new AVLTree(key);
        if (key < tree->key)
            tree->left = insert(tree->left, key);
        else
            tree->right = insert(tree->right, key);
        return tree->balance();
    }

    AVLTree *find_min() {
        return left ? left->find_min() : this;
    }

    AVLTree *remove_min() {
        if (left == nullptr)
            return right;
        left = left->remove_min();
        return balance();
    }

    AVLTree *remove(AVLTree *tree, T key) {
        if (!tree) return nullptr;
        if (key < tree->key)
            tree->left = remove(tree->left, key);
        else if (key > tree->key)
            tree->right = remove(tree->right, key);
        else {
            auto *left = tree->left;
            auto *right = tree->right;
            delete tree;
            if (!right) return left;
            auto *min = right->find_min();
            min->right = right->remove_min();
            min->left = left;
            return min->balance();
        }
        return tree->balance();
    }
};

#endif