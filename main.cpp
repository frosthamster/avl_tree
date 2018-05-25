#include <iostream>
#include "AVLTree.h"

using namespace std;

int main() {
    auto tree = new AVLTree<int>(0);
    cout << "height: " << (int) tree->get_height() << endl;
    cout << "root: " << tree->get_value() << endl << endl;
    for (int i = 1; i < 100; i++)
        tree = tree->insert(i);
    cout << "height: " << (int) tree->get_height() << endl;
    cout << "root: " << tree->get_value() << endl << endl;
    cout << "is contains 15 - " << tree->contains(15) << endl;
    cout << "deleted 15" << endl;
    tree = tree->remove(15);
    cout << "is contains 15 - " << tree->contains(15) << endl << endl;
    for (int i = 1; i < 100; i++)
        tree = tree->remove(i);
    cout << "deleted 1-99" << endl;
    cout << "height: " << (int) tree->get_height() << endl;
    cout << "root: " << tree->get_value() << endl;
    return 0;
}