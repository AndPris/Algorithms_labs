#pragma once

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Record {
    int key;
    string data;
};

class BTree {
    class Node {
        vector<Record> records;
        int minimum_degree;
        vector<Node*> children;
        int amount_of_records;
        bool is_leaf;

    public:
        Node(int minimum_degree, bool is_leaf);

        void traverse() const;
        Record search(int key);

        void insert_in_non_full(Record record);
        void split_child(int index);

        int find_index_of_first_greater_or_equal_key(int key) const;
        void remove(int key);
        void remove_from_leaf(int key_index);
        void remove_from_non_leaf(int key_index);
        void replace_record_by_child_record(int record_index_to_replace, int child_index_to_take_record, Record record);
        Record get_predecessor(int record_index);
        Record get_successor(int record_index);
        void fill_child(int child_index);
        void borrow_record_from_previous_child(int child_index);
        void borrow_record_from_next_child(int child_index);
        void merge_child(int child_index);

        bool is_full() const;
        bool contains_minimal_allowed_amount_of_records() const;

        friend class BTree;
    };

    Node* root;
    int minimum_degree;

public:
    BTree(int minimum_degree);

    void traverse() const;
    Record search(int key);
    void insert(Record record);
    void remove(int key);
};