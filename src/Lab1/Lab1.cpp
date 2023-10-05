#include "FileCreator.h"
#include "FileSorter.h"
#include <ctime>
#include <iomanip>

int input_positive_number() {
    int number;
    char ch;
    bool repeat;
    do {
        repeat = false;
        if (!(cin >> number) || ((ch = getchar()) != '\n') || (number <= 0) || (number > INT32_MAX)) {
            cout << "Invalid data, input integer number from 1 to "<<INT32_MAX<<" please." << endl;
            cin.clear();
            cin.ignore(100, '\n');
            repeat = true;
        }
    } while (repeat);
    return number;
}

int main() {
    const int AMOUNT_OF_SUPPORTING_FILES = 3;
    string file_extension = ".bin";
    string supporting_file_prefix = "supporting_";
    string result_file_path = "result" + file_extension;
    const wchar_t* initial_file_path = L"initial.bin";
    int repeat;
    do {
        cout << "Enter size of file to sort in megabytes:" << endl;
        int size_of_initial_file_in_mb = input_positive_number();

        try {
            FileCreator creator(initial_file_path, size_of_initial_file_in_mb);

            clock_t beginning_of_creation, end_of_creation,
                beginning_of_sorting, end_of_sorting;

            beginning_of_creation = clock();
            creator.create_initial_file();

            end_of_creation = clock();
            cout << "Creation of the file took " << fixed << double(end_of_creation - beginning_of_creation) / CLOCKS_PER_SEC << setprecision(5) << " seconds" << endl;

            FileMapping file_to_sort(creator.get_initial_file_path());

            FileSorter sorter(&file_to_sort, file_extension, supporting_file_prefix, AMOUNT_OF_SUPPORTING_FILES, result_file_path);
            beginning_of_sorting = clock();

            sorter.polyphase_merge_sort();

            end_of_sorting = clock();

            cout << "Sorting of the file took " << fixed << double(end_of_sorting - beginning_of_sorting) / CLOCKS_PER_SEC << setprecision(5) << " seconds" << endl;

            sorter.display_sorted_file();

            cout << "Enter 1 to run program again or any other positive value from 2 to "<< INT32_MAX<<" to stop it : " << endl;
            repeat = input_positive_number();
            file_to_sort.close();
        }
        catch (const char* err) {
            cout << err << endl;
            repeat = 0;
        }

    } while (repeat == 1);

    return 0;
}