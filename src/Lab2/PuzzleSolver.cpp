#include "PuzzleSolver.h"

PuzzleSolver::Node::Node(int **puzzle, int puzzle_size, int depth, int action, Node* parent) : depth(depth), action(action), parent(parent) {
    size = puzzle_size;

    MemoryHandler handler;
    state = handler.allocate_memory(size, size);

    copy(state, puzzle, size);

    empty_cell_coords = find_coords_of_empty_cell();
}
PuzzleSolver::Node::Node(const PuzzleSolver::Node &obj) {
    this->size = obj.size;
    this->empty_cell_coords = obj.empty_cell_coords;
    this->depth = obj.depth;
    this->action = obj.action;
    this->parent = obj.parent;

    MemoryHandler handler;
    state = handler.allocate_memory(size, size);

    copy(state, obj.state, size);
}

PuzzleSolver::Node::Coords PuzzleSolver::Node::find_coords_of_empty_cell() const {
    Coords empty_cell_coords;

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(state[i][j] == 0) {
                empty_cell_coords.row = i;
                empty_cell_coords.col = j;
                return empty_cell_coords;
            }
        }
    }

    empty_cell_coords.row = -1;
    empty_cell_coords.col = -1;
    return empty_cell_coords;
}
PuzzleSolver::Node::Node(PuzzleSolver::Node &&obj) {
    this->state = obj.state;
    obj.state = nullptr;
    
    this->size = obj.size;
    this->empty_cell_coords = obj.empty_cell_coords;
    this->depth = obj.depth;
    this->action = obj.action;
    this->parent = obj.parent;
}
PuzzleSolver::Node& PuzzleSolver::Node::operator=(PuzzleSolver::Node &&obj) {
    this->state = obj.state;
    obj.state = nullptr;
    
    this->size = obj.size;
    this->empty_cell_coords = obj.empty_cell_coords;
    this->depth = obj.depth;
    this->action = obj.action;
    this->parent = obj.parent;

    return *this;
}


PuzzleSolver::Node* PuzzleSolver::Node::expand() {
    int amount_of_successors = get_amount_of_successors();
    Node* successors = new Node[amount_of_successors];
    int i = 0;

    if(!is_empty_cell_in_top_row() && action!=UP)
        successors[i++] = move_down();
    if(!is_empty_cell_in_bottom_row() && action!=DOWN)
        successors[i++] = move_up();
    if(!is_empty_cell_in_left_col() && action!=RIGHT)
        successors[i++] = move_right();
    if(!is_empty_cell_in_right_col() && action!=LEFT)
        successors[i] = move_left();

    return successors;
}
int PuzzleSolver::Node::get_amount_of_successors() const {
    int amount_of_successors = 4;

    if(is_empty_cell_in_top_row() || action==UP)
        --amount_of_successors;
    if(is_empty_cell_in_bottom_row() || action==DOWN)
        --amount_of_successors;
    if(is_empty_cell_in_left_col() || action==RIGHT)
        --amount_of_successors;
    if(is_empty_cell_in_right_col() || action==LEFT)
        --amount_of_successors;

    return amount_of_successors;
}
bool PuzzleSolver::Node::is_empty_cell_in_top_row() const {
    return empty_cell_coords.row == 0;
}
bool PuzzleSolver::Node::is_empty_cell_in_bottom_row() const {
    return empty_cell_coords.row == size-1;
}
bool PuzzleSolver::Node::is_empty_cell_in_left_col() const {
    return empty_cell_coords.col == 0;
}
bool PuzzleSolver::Node::is_empty_cell_in_right_col() const {
    return empty_cell_coords.col == size-1;
}

PuzzleSolver::Node PuzzleSolver::Node::move_up() {
    Node new_node(state, size, depth+1, UP, this);

    swap(new_node.state[empty_cell_coords.row][empty_cell_coords.col],
         new_node.state[empty_cell_coords.row+1][empty_cell_coords.col]);
    ++new_node.empty_cell_coords.row;

    return new_node;
}
PuzzleSolver::Node PuzzleSolver::Node::move_down() {
    Node new_node(state, size, depth+1, DOWN, this);

    swap(new_node.state[empty_cell_coords.row][empty_cell_coords.col],
         new_node.state[empty_cell_coords.row-1][empty_cell_coords.col]);
    --new_node.empty_cell_coords.row;

    return new_node;
}
PuzzleSolver::Node PuzzleSolver::Node::move_left() {
    Node new_node(state, size,  depth+1, LEFT, this);

    swap(new_node.state[empty_cell_coords.row][empty_cell_coords.col],
         new_node.state[empty_cell_coords.row][empty_cell_coords.col+1]);
    ++new_node.empty_cell_coords.col;

    return new_node;
}
PuzzleSolver::Node PuzzleSolver::Node::move_right() {
    Node new_node(state, size,  depth+1, RIGHT, this);

    swap(new_node.state[empty_cell_coords.row][empty_cell_coords.col],
         new_node.state[empty_cell_coords.row][empty_cell_coords.col-1]);
    --new_node.empty_cell_coords.col;

    return new_node;
}
void PuzzleSolver::Node::swap(int &first_number, int &second_number) {
    int temp = first_number;
    first_number = second_number;
    second_number = temp;
}

bool PuzzleSolver::Node::is_solution() const {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(state[i][j] != i * size + j)
                return false;
        }
    }
    return true;
}

int **PuzzleSolver::Node::get_state() {
    return state;
}
int PuzzleSolver::Node::get_depth() const {
    return depth;
}
int PuzzleSolver::Node::get_size() const {
    return size;
}
int PuzzleSolver::Node::manhattan_distance() const {
    int distance = 0;

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j)
            distance += abs(state[i][j]/size - i) + abs(state[i][j]%size - j);
    }

    return distance;
}

bool PuzzleSolver::Node::operator==(const PuzzleSolver::Node &obj) const {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(state[i][j] != obj.state[i][j])
                return false;
        }
    }
    return true;
}

void PuzzleSolver::Node::display_path() {
    stack<Node*> path;

    Node* current = this;
    path.push(current);
    while(current->parent != nullptr) {
        current = current->parent;
        path.push(current);

    }

    while (!path.empty()) {
        current = path.top();
        path.pop();
        display(current->get_state(), current->get_size());
    }
}
PuzzleSolver::Node::~Node() {
    if(state) {
        MemoryHandler handler;
        handler.delete_memory(state, size);
    }
}


int **PuzzleSolver::LDFS_solve(int **puzzle, int puzzle_size, int limit) {
    if(!is_solvable(puzzle, puzzle_size))
        throw "Puzzle doesn't have solution";

    Node initial_state(puzzle, puzzle_size, 1, INITIAL, nullptr);

    bool is_cutoff = false;
    bool is_failure = false;
    Node *result = _LDFS_solve(initial_state, limit, is_cutoff, is_failure);
    if (result) {
        result->display_path();

        int** result_state;
        MemoryHandler handler;
        result_state = handler.allocate_memory(result->get_size(), result->get_size());
        copy(result_state, result->get_state(), result->get_size());

        return result_state;
    }

    if(is_failure)
        throw "Failure";
    if(is_cutoff)
        throw "Cutoff";
}

PuzzleSolver::Node* PuzzleSolver::_LDFS_solve(Node &node, int limit, bool &is_cutoff, bool &is_failure) {
    bool cutoff_occurred = false;
    is_cutoff = false;
    is_failure = false;
    if (node.is_solution())
        return &node;
    

    if(node.get_depth() >= limit) {
        is_cutoff = true;
        return nullptr;
    }

    Node *successors = node.expand();
    int amount_of_successors = node.get_amount_of_successors();
    Node *result;

    for(int i = 0; i < amount_of_successors; ++i) {
        result = _LDFS_solve(successors[i], limit, is_cutoff, is_failure);

        if(is_cutoff)
            cutoff_occurred = true;
        else if(!is_failure)
            return result;
    }
    delete[] successors;

    if(cutoff_occurred) {
        is_cutoff = true;
        return nullptr;
    }

    is_failure = true;
    return nullptr;
}

bool PuzzleSolver::is_solvable(int **puzzle, int size) const {
    int *elements = create_elements_array(puzzle, size);
    int inversions = count_inversions(elements, size*size-1);

    delete[] elements;
    return (inversions % 2 == 0);
}
int *PuzzleSolver::create_elements_array(int **puzzle, int size) const {
    int *elements = new int[size*size-1];
    int index = 0;

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(puzzle[i][j] != 0)
                elements[index++] = puzzle[i][j];
        }
    }

    return elements;
}
int PuzzleSolver::count_inversions(int *elements, int size) const {
    int inversions = 0;

    for(int i = 0; i < size; ++i) {
        for(int j = i+1; j < size; ++j) {
            if(elements[i] > elements[j])
                ++inversions;
        }
    }

    return inversions;
}
int** PuzzleSolver::A_star(int** puzzle, int puzzle_size) {
    if (!is_solvable(puzzle, puzzle_size))
        throw "Puzzle doesn't have solution";

    Node initial_state(puzzle, puzzle_size, 1, INITIAL, nullptr);
    
    Node *result = _A_star(initial_state);
    result->display_path();
    int** result_state;
    MemoryHandler handler;
    result_state = handler.allocate_memory(puzzle_size, puzzle_size);
    copy(result_state, result->get_state(), puzzle_size);
    return result_state;
}
PuzzleSolver::Node *PuzzleSolver::_A_star(Node &node) {
    class NodeComparator {
    public:
        bool operator()(Node *&obj1, Node *&obj2) {
            int heur1 = obj1->get_depth() + obj1->manhattan_distance() - 1;
            int heur2 = obj2->get_depth() + obj2->manhattan_distance() - 1;
            return heur1 > heur2;
        }
    };

    priority_queue<Node*, vector<Node*>, NodeComparator> open;
    vector<Node*> close;

    open.push(&node);

    while (!open.empty()) {
        Node* current = open.top();
        open.pop();

        if (current->is_solution())
            return current;

        close.push_back(current);
        PuzzleSolver::Node* successors = current->expand();
        int amount_of_successors = current->get_amount_of_successors();

        for(int i = 0; i < amount_of_successors; ++i) {
            if(!contains(close, successors[i]))
                open.push(&successors[i]);
        }
    }
}

bool PuzzleSolver::contains(vector<PuzzleSolver::Node*> &container, const PuzzleSolver::Node &obj) const {
    for (Node*& curr : container) {
        if(*curr == obj)
            return true;
    }

    return false;
}