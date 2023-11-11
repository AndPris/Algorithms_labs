#include "B_Tree.h"

BTree::BTree(int minimum_degree) : minimum_degree(minimum_degree) {
    root = nullptr;
}

void BTree::traverse() const {
    if(root)
        root->traverse();
}

BTree::Node *BTree::search(int key) {
    if(!root)
        return nullptr;
    return root->search(key);
}

void BTree::insert(int key) {
    if(!root) {
        root = new Node(minimum_degree, true);
        root->keys.push_back(key);
        root->amount_of_keys = 1;
        return;
    }

    if(root->is_full()) {
        Node* new_root = new Node(minimum_degree, false);
        new_root->children.push_back(root);
        new_root->split_child(0);

        int i = 0;
        if(new_root->keys.at(0) < key)
            ++i;
        new_root->children.at(i)->insert_in_non_full(key);
        root = new_root;
    } else
        root->insert_in_non_full(key);

}
void BTree::remove(int key) {
    if(!root)
        throw "This tree is empty";

    root->remove(key);
    if(root->amount_of_keys == 0) {
        BTree::Node* temp = root;
        if(root->is_leaf)
            root = nullptr;
        else
            root = root->children[0];

        delete temp;
    }
}


BTree::Node::Node(int minimum_degree, bool is_leaf) : minimum_degree(minimum_degree), is_leaf(is_leaf) {
    amount_of_keys = 0;
}

void BTree::Node::traverse() const {
    int i;
    for(i = 0; i < amount_of_keys; ++i) {
        if(!is_leaf)
            children.at(i)->traverse();
        cout<<keys.at(i)<<" ";
    }

    if(!is_leaf)
        children.at(i)->traverse();
}

BTree::Node *BTree::Node::search(int key) {
    int i = 0;
    while(i < amount_of_keys && key > keys.at(i))
        ++i;

    if(i < amount_of_keys && keys.at(i) == key)
        return this;

    if(is_leaf)
        return nullptr;

    return children.at(i)->search(key);
}

void BTree::Node::insert_in_non_full(int key) {
    int i = amount_of_keys - 1;

    if(is_leaf) {
        while (i >= 0 && keys.at(i) > key)
            --i;

        keys.insert(keys.begin() + i+1, key);
        ++amount_of_keys;
        return;
    }

    while (i >= 0 && keys.at(i) > key)
        --i;

    if(children.at(i+1)->is_full()) {
        split_child(i+1);

        if(keys.at(i+1) < key)
            ++i;
    }
    children.at(i+1)->insert_in_non_full(key);
}

void BTree::Node::split_child(int index) {
    BTree::Node* child_to_split = children.at(index);

    BTree::Node* additional_node = new BTree::Node(child_to_split->minimum_degree, child_to_split->is_leaf);
    additional_node->amount_of_keys = minimum_degree-1;

    for(int i = 0; i < minimum_degree-1; ++i) {
        additional_node->keys.push_back(child_to_split->keys.at(minimum_degree));
        child_to_split->keys.erase(child_to_split->keys.begin()+minimum_degree);
    }

    if(!child_to_split->is_leaf) {
        for(int i = 0; i < minimum_degree; ++i) {
            additional_node->children.push_back(child_to_split->children.at(minimum_degree));
            child_to_split->children.erase(child_to_split->children.begin()+minimum_degree);
        }
    }

    child_to_split->amount_of_keys = minimum_degree-1;

    children.insert(children.begin()+index+1, additional_node);

    keys.insert(keys.begin()+index, child_to_split->keys.at(minimum_degree-1));
    child_to_split->keys.erase(child_to_split->keys.begin()+minimum_degree-1);

    ++amount_of_keys;
}
bool BTree::Node::is_full() const {
    return amount_of_keys == 2*minimum_degree-1;
}
bool BTree::Node::contains_minimal_allowed_amount_of_keys() const {
    return amount_of_keys == (minimum_degree-1);
}

int BTree::Node::find_index_of_first_greater_or_equal_key(int key) const {
    auto it = find_if(keys.begin(), keys.end(), [key] (int element) {return element >= key;});
    return (it - keys.begin());
}

void BTree::Node::remove(int key) {
    int index = find_index_of_first_greater_or_equal_key(key);
    if(index < amount_of_keys && keys.at(index) == key) {
        if(is_leaf)
            remove_from_leaf(index);
        else
            remove_from_non_leaf(index);

        return;
    }

    if(is_leaf)
        throw "The key " + to_string(key) + " isn't in the tree";

    bool is_key_present_in_last_child_subtree = (index == amount_of_keys);

    if(children[index]->amount_of_keys < minimum_degree)
        fill_child(index);

    if(is_key_present_in_last_child_subtree && index > amount_of_keys)
        children.at(index-1)->remove(key);
    else
        children.at(index)->remove(key);
}

void BTree::Node::remove_from_leaf(int key_index) {
    keys.erase(keys.begin()+key_index);
    --amount_of_keys;
}
void BTree::Node::remove_from_non_leaf(int key_index) {
    int key = keys.at(key_index);

    if(!children.at(key_index)->contains_minimal_allowed_amount_of_keys())
        replace_key_by_child_key(key_index, key_index, get_predecessor(key_index));
    else if(!children.at(key_index+1)->contains_minimal_allowed_amount_of_keys())
        replace_key_by_child_key(key_index, key_index+1, get_successor(key_index));
    else {
        merge_child(key_index);
        children.at(key_index)->remove(key);
    }
}
void BTree::Node::replace_key_by_child_key(int key_index_to_replace, int child_index_to_take_key, int key) {
    keys.at(key_index_to_replace) = key;
    children.at(child_index_to_take_key)->remove(key);
}
int BTree::Node::get_predecessor(int key_index) {
    BTree::Node* curr = children.at(key_index);
    while (!curr->is_leaf)
        curr = curr->children.at(curr->amount_of_keys);

    return curr->keys.at(curr->amount_of_keys-1);
}
int BTree::Node::get_successor(int key_index) {
    BTree::Node* curr = children.at(key_index+1);
    while (!curr->is_leaf)
        curr = curr->children.at(0);

    return curr->keys.at(0);
}

void BTree::Node::fill_child(int child_index) {
    if(child_index != 0 && !children.at(child_index-1)->contains_minimal_allowed_amount_of_keys())
        borrow_key_from_previous_child(child_index);
    else if (child_index != amount_of_keys && !children.at(child_index+1)->contains_minimal_allowed_amount_of_keys())
        borrow_key_from_next_child(child_index);
    else {
        if(child_index != amount_of_keys)
            merge_child(child_index);
        else
            merge_child(child_index-1);
    }
}
void BTree::Node::borrow_key_from_previous_child(int child_index) {
    BTree::Node* child_which_borrows = children.at(child_index);
    BTree::Node* sibling_child_from_which_borrow = children.at(child_index-1);

    child_which_borrows->keys.insert(child_which_borrows->keys.begin(), keys.at(child_index-1));
    if(!child_which_borrows->is_leaf) {
        child_which_borrows->children.insert(child_which_borrows->children.begin(), sibling_child_from_which_borrow->children.at(sibling_child_from_which_borrow->amount_of_keys));
        sibling_child_from_which_borrow->children.erase(sibling_child_from_which_borrow->children.begin()+sibling_child_from_which_borrow->amount_of_keys);
    }

    keys.at(child_index-1) = sibling_child_from_which_borrow->keys.at(sibling_child_from_which_borrow->amount_of_keys-1);
    sibling_child_from_which_borrow->keys.erase(sibling_child_from_which_borrow->keys.begin()+sibling_child_from_which_borrow->amount_of_keys-1);

    ++child_which_borrows->amount_of_keys;
    --sibling_child_from_which_borrow->amount_of_keys;
}
void BTree::Node::borrow_key_from_next_child(int child_index) {
    BTree::Node* child_which_borrows = children.at(child_index);
    BTree::Node* sibling_child_from_which_borrow = children.at(child_index+1);

    child_which_borrows->keys.insert(child_which_borrows->keys.begin()+child_which_borrows->amount_of_keys, keys.at(child_index));
    if(!child_which_borrows->is_leaf) {
        child_which_borrows->children.insert(child_which_borrows->children.begin()+child_which_borrows->amount_of_keys+1, sibling_child_from_which_borrow->children.at(0));
        sibling_child_from_which_borrow->children.erase(sibling_child_from_which_borrow->children.begin());
    }

    keys.at(child_index) = sibling_child_from_which_borrow->keys.at(0);
    sibling_child_from_which_borrow->keys.erase(sibling_child_from_which_borrow->keys.begin());

    ++child_which_borrows->amount_of_keys;
    --sibling_child_from_which_borrow->amount_of_keys;
}
void BTree::Node::merge_child(int child_index) {
    BTree::Node* child = children.at(child_index);
    BTree::Node* sibling_which_merges = children.at(child_index+1);

    child->keys.push_back(keys.at(child_index));
    keys.erase(keys.begin() + child_index);

    child->keys.insert(child->keys.end(), sibling_which_merges->keys.begin(), sibling_which_merges->keys.end());
    sibling_which_merges->keys.clear();

    if(!child->is_leaf) {
        child->children.insert(child->children.end(), sibling_which_merges->children.begin(), sibling_which_merges->children.end());
        sibling_which_merges->children.clear();
    }

    children.erase(children.begin()+child_index+1);
    --amount_of_keys;
    child->amount_of_keys += sibling_which_merges->amount_of_keys + 1;

    delete sibling_which_merges;
}