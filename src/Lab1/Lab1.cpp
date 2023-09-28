#include "FileHandler.h"
#include "FileSorter.h"

int main() {
    const int amount_of_supporting_files = 6;
    const int size_of_initial_file_in_mb = 1;
    string path_to_folder = "x64/Debug/";
    string file_extension = ".bin";
    string initial_file_path = path_to_folder + "initial" + file_extension;
    string supporting_file_prefix = path_to_folder + "supporting_";


    FileHandler handler(initial_file_path, size_of_initial_file_in_mb);

    handler.create_initial_file();
    //handler.display_initial_file();

    
    FileSorter sorter(handler.get_initial_file_path(), file_extension, supporting_file_prefix, amount_of_supporting_files);
    sorter.make_initial_spliting();
    sorter.polyphase_merge_sort();
    return 0;
}