#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;


class BTree {
    class Node {
        vector<int> keys;
        int minimum_degree;
        vector<Node*> children;
        int amount_of_keys;
        bool is_leaf;

    public:
        Node(int minimum_degree, bool is_leaf);

        void traverse() const;
        Node* search(int key);

        void insert_in_non_full(int key);
        void split_child(int index);

        int find_index_of_first_greater_or_equal_key(int key) const;
        void remove(int key);
        void remove_from_leaf(int key_index);
        void remove_from_non_leaf(int key_index);
        void replace_key_by_child_key(int key_index_to_replace, int child_index_to_take_key, int key);
        int get_predecessor(int key_index);
        int get_successor(int key_index);
        void fill_child(int child_index);
        void borrow_key_from_previous_child(int child_index);
        void borrow_key_from_next_child(int child_index);
        void merge_child(int child_index);

        bool is_full() const;
        bool contains_minimal_allowed_amount_of_keys() const;

        friend class BTree;
    };

    Node* root;
    int minimum_degree;

public:
    BTree(int minimum_degree);

    void traverse() const;
    Node* search(int key);
    void insert(int key);
    void remove(int key);
};