
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "OrgChart.hpp"
using namespace ariel;

int main() {
    OrgChart family_tree;
    family_tree.add_root("Grandmother")
    .add_sub("Grandmother", "Uncle")
    .add_sub("Grandmother", "Aunt")
    .add_sub("Grandmother", "Father")
    .add_sub("Uncle", "Cousin")
    .add_sub("Uncle", "Cousin")
    .add_sub("Father", "Me")
    .add_sub("Me", "My_child");

    cout << family_tree << endl;

    cout << "Level Order: " << endl;
    for (auto it = family_tree.begin_level_order(); it != family_tree.end_level_order(); ++it)
        {
            cout << (*it) << " " ;
        }
    cout << endl;
    cout << "Reverse Order: " << endl;
    for (auto it = family_tree.begin_reverse_order(); it != family_tree.reverse_order(); ++it)
        {
            cout << (*it) << " " ;
        }
    cout << endl;
    cout << "PreOrder Order: " << endl;
    for (auto it = family_tree.begin_preorder(); it != family_tree.end_preorder(); ++it)
        {
            cout << (*it) << " " ;
        }
    cout << endl;
    cout << "Using begin() and end()" << endl;
    for (auto element : family_tree)
        { 
            cout << element << " " ;
        } 
    cout << endl;
    cout << "checking sizes" << endl;
    for (auto it = family_tree.begin_level_order(); it != family_tree.end_level_order(); ++it)
        {
            cout << it->size() << " " ;
        } 

}