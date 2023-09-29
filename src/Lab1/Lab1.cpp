#include "FileHandler.h"
#include "FileSorter.h"
#include <ctime>
#include <iomanip>

int main() {
    const int amount_of_supporting_files = 6;
    const int size_of_initial_file_in_mb = 1;
    string path_to_folder = "x64/Debug/";
    string file_extension = ".bin";
    string initial_file_path = path_to_folder + "initial" + file_extension;
    string supporting_file_prefix = path_to_folder + "supporting_";


    FileHandler handler(initial_file_path, size_of_initial_file_in_mb);


    clock_t beginning_of_creation, end_of_creation,
        beginning_of_sorting, end_of_sorting;

    beginning_of_creation = clock();
    handler.create_initial_file();
    end_of_creation = clock();
    //handler.display_initial_file();
    cout << "Creation of the file took " << fixed << double(end_of_creation - beginning_of_creation) / CLOCKS_PER_SEC << setprecision(5) << " seconds" << endl;

    
    FileSorter sorter(handler.get_initial_file_path(), file_extension, supporting_file_prefix, amount_of_supporting_files);
    beginning_of_sorting = clock();
    sorter.make_initial_spliting();
    sorter.polyphase_merge_sort();
    end_of_sorting = clock();

    cout << "Sorting of the file took " << fixed << double(end_of_sorting - beginning_of_sorting) / CLOCKS_PER_SEC << setprecision(5) << " seconds" << endl;

    return 0;
}