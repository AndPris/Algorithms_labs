#include "FileHandler.h"

int main() {
    FileHandler handler(21, 2);

    handler.create_initial_file();
    handler.display_initial_file();

    return 0;
}