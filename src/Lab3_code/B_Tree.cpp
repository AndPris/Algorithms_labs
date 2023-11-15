#include "B_Tree.h"

BTree::BTree(int minimum_degree) : minimum_degree(minimum_degree) {
    root = nullptr;
}

bool BTree::is_empty() const {
    return root == nullptr;
}
void BTree::traverse(vector<Record>& destination) const {
    if (root)
        root->traverse(destination);
}

Record BTree::search(int key, int& amount_of_comparisons) {
    if (!root)
        throw "The tree is empty";
    return root->search(key, amount_of_comparisons);
}

void BTree::edit(int key, char* new_data) {
    if (!root)
        throw "The tree is empty";

    root->edit(key, new_data);
}
void BTree::insert(Record record) {
    if (!root) {
        root = new Node(minimum_degree, true);
        root->records.push_back(record);
        root->amount_of_records = 1;
        return;
    }

    bool contains_record_with_such_key = true;
    try {
        int not_used = 0;
        search(record.key, not_used);
    }
    catch (const char* er) {
        contains_record_with_such_key = false;
    }
    if (contains_record_with_such_key)
        throw "There is a record with such key";


    if (root->is_full()) {
        Node* new_root = new Node(minimum_degree, false);
        new_root->children.push_back(root);
        new_root->split_child(0);

        int i = 0;
        if (new_root->records.at(0).key < record.key)
            ++i;
        new_root->children.at(i)->insert_in_non_full(record);
        root = new_root;
    }
    else
        root->insert_in_non_full(record);

}
void BTree::remove(int key) {
    if (!root)
        throw "This tree is empty";

    root->remove(key);
    if (root->amount_of_records == 0) {
        BTree::Node* temp = root;
        if (root->is_leaf)
            root = nullptr;
        else
            root = root->children[0];

        delete temp;
    }
}



BTree::Node::Node(int minimum_degree, bool is_leaf) : minimum_degree(minimum_degree), is_leaf(is_leaf) {
    amount_of_records = 0;
}

void BTree::Node::traverse(vector<Record>& destination) const {
    int i;
    for (i = 0; i < amount_of_records; ++i) {
        if (!is_leaf)
            children.at(i)->traverse(destination);

        destination.push_back(records.at(i));
    }

    if (!is_leaf)
        children.at(i)->traverse(destination);
}

Record BTree::Node::search(int key, int& amount_of_comparisons) {
    int left = 0;
    int right = records.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (records.at(mid).key == key) {
            ++amount_of_comparisons;
            return records.at(mid);
        }

        if (records.at(mid).key < key)
            left = mid + 1;
        else
            right = mid - 1;

        ++amount_of_comparisons;
    }

    if (is_leaf)
        throw "There is no such element";

    return children.at(left)->search(key, amount_of_comparisons);
}

void BTree::Node::edit(int key, char* new_data) {
    int i = 0;
    while (i < amount_of_records && key > records.at(i).key)
        ++i;

    if (i < amount_of_records && records.at(i).key == key) {
        strcpy_s(records.at(i).data, new_data);
        return;
    }

    if (is_leaf)
        throw "There is no element with such key";

    children.at(i)->edit(key, new_data);
}

void BTree::Node::insert_in_non_full(Record record) {
    int i = amount_of_records - 1;

    if (is_leaf) {
        while (i >= 0 && records.at(i).key > record.key)
            --i;

        records.insert(records.begin() + (i + 1), record);
        ++amount_of_records;
        return;
    }

    while (i >= 0 && records.at(i).key > record.key)
        --i;

    if (children.at(i + 1)->is_full()) {
        split_child(i + 1);

        if (records.at(i + 1).key < record.key)
            ++i;
    }
    children.at(i + 1)->insert_in_non_full(record);
}

void BTree::Node::split_child(int index) {
    BTree::Node* child_to_split = children.at(index);

    BTree::Node* additional_node = new BTree::Node(child_to_split->minimum_degree, child_to_split->is_leaf);
    additional_node->amount_of_records = minimum_degree - 1;

    for (int i = 0; i < minimum_degree - 1; ++i) {
        additional_node->records.push_back(child_to_split->records.at(minimum_degree));
        child_to_split->records.erase(child_to_split->records.begin() + minimum_degree);
    }

    if (!child_to_split->is_leaf) {
        for (int i = 0; i < minimum_degree; ++i) {
            additional_node->children.push_back(child_to_split->children.at(minimum_degree));
            child_to_split->children.erase(child_to_split->children.begin() + minimum_degree);
        }
    }

    child_to_split->amount_of_records = minimum_degree - 1;

    children.insert(children.begin() + index + 1, additional_node);

    records.insert(records.begin() + index, child_to_split->records.at(minimum_degree - 1));
    child_to_split->records.erase(child_to_split->records.begin() + minimum_degree - 1);

    ++amount_of_records;
}
bool BTree::Node::is_full() const {
    return amount_of_records == 2 * minimum_degree - 1;
}
bool BTree::Node::contains_minimal_allowed_amount_of_records() const {
    return amount_of_records == (minimum_degree - 1);
}

int BTree::Node::find_index_of_first_greater_or_equal_key(int key) const {
    auto it = find_if(records.begin(), records.end(), [key](Record element) {return element.key >= key; });
    return (it - records.begin());
}

void BTree::Node::remove(int key) {
    int index = find_index_of_first_greater_or_equal_key(key);
    if (index < amount_of_records && records.at(index).key == key) {
        if (is_leaf)
            remove_from_leaf(index);
        else
            remove_from_non_leaf(index);

        return;
    }

    if (is_leaf)
        throw "The record with key " + to_string(key) + " isn't in the tree";

    bool is_key_present_in_last_child_subtree = (index == amount_of_records);

    if (children[index]->amount_of_records < minimum_degree)
        fill_child(index);

    if (is_key_present_in_last_child_subtree && index > amount_of_records)
        children.at(index - 1)->remove(key);
    else
        children.at(index)->remove(key);
}

void BTree::Node::remove_from_leaf(int key_index) {
    records.erase(records.begin() + key_index);
    --amount_of_records;
}
void BTree::Node::remove_from_non_leaf(int key_index) {
    int key = records.at(key_index).key;

    if (!children.at(key_index)->contains_minimal_allowed_amount_of_records())
        replace_record_by_child_record(key_index, key_index, get_predecessor(key_index));
    else if (!children.at(key_index + 1)->contains_minimal_allowed_amount_of_records())
        replace_record_by_child_record(key_index, key_index + 1, get_successor(key_index));
    else {
        merge_child(key_index);
        children.at(key_index)->remove(key);
    }
}
void BTree::Node::replace_record_by_child_record(int record_index_to_replace, int child_index_to_take_record, Record record) {
    records.at(record_index_to_replace) = record;
    children.at(child_index_to_take_record)->remove(record.key);
}
Record BTree::Node::get_predecessor(int key_index) {
    BTree::Node* curr = children.at(key_index);
    while (!curr->is_leaf)
        curr = curr->children.at(curr->amount_of_records);

    return curr->records.at(curr->amount_of_records - 1);
}
Record BTree::Node::get_successor(int key_index) {
    BTree::Node* curr = children.at(key_index + 1);
    while (!curr->is_leaf)
        curr = curr->children.at(0);

    return curr->records.at(0);
}

void BTree::Node::fill_child(int child_index) {
    if (child_index != 0 && !children.at(child_index - 1)->contains_minimal_allowed_amount_of_records())
        borrow_record_from_previous_child(child_index);
    else if (child_index != amount_of_records && !children.at(child_index + 1)->contains_minimal_allowed_amount_of_records())
        borrow_record_from_next_child(child_index);
    else {
        if (child_index != amount_of_records)
            merge_child(child_index);
        else
            merge_child(child_index - 1);
    }
}
void BTree::Node::borrow_record_from_previous_child(int child_index) {
    BTree::Node* child_which_borrows = children.at(child_index);
    BTree::Node* sibling_child_from_which_borrow = children.at(child_index - 1);

    child_which_borrows->records.insert(child_which_borrows->records.begin(), records.at(child_index - 1));
    if (!child_which_borrows->is_leaf) {
        child_which_borrows->children.insert(child_which_borrows->children.begin(), sibling_child_from_which_borrow->children.at(sibling_child_from_which_borrow->amount_of_records));
        sibling_child_from_which_borrow->children.erase(sibling_child_from_which_borrow->children.begin() + sibling_child_from_which_borrow->amount_of_records);
    }

    records.at(child_index - 1) = sibling_child_from_which_borrow->records.at(sibling_child_from_which_borrow->amount_of_records - 1);
    sibling_child_from_which_borrow->records.erase(sibling_child_from_which_borrow->records.begin() + sibling_child_from_which_borrow->amount_of_records - 1);

    ++child_which_borrows->amount_of_records;
    --sibling_child_from_which_borrow->amount_of_records;
}
void BTree::Node::borrow_record_from_next_child(int child_index) {
    BTree::Node* child_which_borrows = children.at(child_index);
    BTree::Node* sibling_child_from_which_borrow = children.at(child_index + 1);

    child_which_borrows->records.insert(child_which_borrows->records.begin() + child_which_borrows->amount_of_records, records.at(child_index));
    if (!child_which_borrows->is_leaf) {
        child_which_borrows->children.insert(child_which_borrows->children.begin() + child_which_borrows->amount_of_records + 1, sibling_child_from_which_borrow->children.at(0));
        sibling_child_from_which_borrow->children.erase(sibling_child_from_which_borrow->children.begin());
    }

    records.at(child_index) = sibling_child_from_which_borrow->records.at(0);
    sibling_child_from_which_borrow->records.erase(sibling_child_from_which_borrow->records.begin());

    ++child_which_borrows->amount_of_records;
    --sibling_child_from_which_borrow->amount_of_records;
}
void BTree::Node::merge_child(int child_index) {
    BTree::Node* child = children.at(child_index);
    BTree::Node* sibling_which_merges = children.at(child_index + 1);

    child->records.push_back(records.at(child_index));
    records.erase(records.begin() + child_index);

    child->records.insert(child->records.end(), sibling_which_merges->records.begin(), sibling_which_merges->records.end());
    sibling_which_merges->records.clear();

    if (!child->is_leaf) {
        child->children.insert(child->children.end(), sibling_which_merges->children.begin(), sibling_which_merges->children.end());
        sibling_which_merges->children.clear();
    }

    children.erase(children.begin() + child_index + 1);
    --amount_of_records;
    child->amount_of_records += sibling_which_merges->amount_of_records + 1;

    delete sibling_which_merges;
}


void BTree::save(std::ofstream& destination) {
    if (!root)
        return;
    root->save(destination);
}
void BTree::Node::save(ofstream& destination) {
    destination.write(reinterpret_cast<const char*>(&is_leaf), sizeof(is_leaf));
    destination.write(reinterpret_cast<const char*>(&amount_of_records), sizeof(amount_of_records));

    for (int i = 0; i < amount_of_records; ++i)
        destination.write(reinterpret_cast<const char*>(&records.at(i)), sizeof(Record));

    for (const auto& child : children)
        child->save(destination);
}

void BTree::open(std::ifstream& source) {
    root = read_node(source);
}

BTree::Node* BTree::read_node(ifstream& source) {
    bool is_node_leaf;

    source.read(reinterpret_cast<char*>(&is_node_leaf), sizeof(is_node_leaf));
    BTree::Node* node = new BTree::Node(minimum_degree, is_node_leaf);

    source.read(reinterpret_cast<char*>(&node->amount_of_records), sizeof(node->amount_of_records));
    for (int i = 0; i < node->amount_of_records; ++i) {
        Record rec;
        source.read(reinterpret_cast<char*>(&rec), sizeof(Record));
        node->records.push_back(rec);
    }

    if (!is_node_leaf) {
        for (int i = 0; i < node->amount_of_records + 1; ++i)
            node->children.push_back(read_node(source));
    }

    return node;
}