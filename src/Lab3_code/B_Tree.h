#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>

using namespace std;

#define DATA_SIZE 35

struct Record {
    int key;
    char data[DATA_SIZE];
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

        void traverse(vector<Record>& destination) const;
        Record search(int key, int& amount_of_comparisons);

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

        void save(ofstream& destination);
        void edit(int key, char new_data[DATA_SIZE]);

        friend class BTree;
    };

    Node* root;
    int minimum_degree;

    BTree::Node* read_node(ifstream& source);
public:
    BTree(int minimum_degree);

    void traverse(vector<Record>& destination) const;
    Record search(int key, int& amount_of_comparisons);
    void insert(Record record);
    void edit(int key, char new_data[DATA_SIZE]);
    void remove(int key);

    void save(ofstream& destination);
    void open(ifstream& source);

    bool is_empty() const;
};