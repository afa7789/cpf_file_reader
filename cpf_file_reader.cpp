#include <chrono>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, const char **argv) {
    bool verbose = false;

    // hello world
    std::cout << "Hello World!" << std::endl;

    if (argc < 4 || argc > 6) {
        std::cerr
            << "Usage: cpf_file_reader <input_file_path> <output_file_path> "
               "<search_string> [<older_than>] [<younger_than>], [] means "
               "optional"
            << std::endl;
        return 1;
    }

    // std::string inputFilePath = "6-MG.txt";
    std::string inputFilePath = argv[1];
    // std::string outputFilePath = "output.txt";
    std::string outputFilePath = argv[2];
    // std::string searchString = "Valentina";
    std::string searchString = argv[3];

    // print variables to check
    std::cout << "inputFilePath: " << inputFilePath << std::endl;
    std::cout << "outputFilePath: " << outputFilePath << std::endl;

    int olderThan = 0;
    int youngerThan = 200;
    if (argc > 4) {
        // receive older than from argv
        olderThan = atoi(argv[4]);
        std::cout << "olderThan: " << olderThan << std::endl;
        if (argc == 6) {
            // receive younger than from argv
            youngerThan = atoi(argv[5]);
            std::cout << "youngerThan: " << youngerThan << std::endl;
        }
    }

    std::ifstream inputFile(inputFilePath);
    std::ofstream outputFile(outputFilePath);
    if (!inputFile) {
        std::cerr << "Failed to open input file." << std::endl;
        return 1;
    }

    if (!outputFile) {
        std::cerr << "Failed to open output file." << std::endl;
        return 1;
    }

    std::time_t t;
    std::tm *local_time;
    int current_year;
    if (!(olderThan == 0 && youngerThan == 200)) {
        t = std::time(nullptr);
        local_time = std::localtime(&t);
        current_year = local_time->tm_year + 1900;
    }

    std::string line;
    std::cout << "searching !" << std::endl;
    auto start_time = chrono::high_resolution_clock::now();

    while (std::getline(inputFile, line)) {
        // separate line by |
        std::vector<std::string> seglist;
        // std::stringstream ss = "";
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, '|')) {
            seglist.push_back(token);
        }

        // the last position of the seglist array is a time in format :
        // 05/10/1979
        std::istringstream datedSS(seglist[3]);
        std::tm tm = {};
        // parsing date as this format : 05/10/1979
        datedSS >> std::get_time(&tm, "%d/%m/%Y");

        if (!datedSS.fail() && !(olderThan == 0 && youngerThan == 200)) {
            // current_year - year from input
            int age = current_year - (tm.tm_year + 1900);
            // std::cout << "age: " << age << std::endl;
            if (age >= olderThan && age <= youngerThan) {
                if (verbose) {
                    std::cout << "age: " << age << std::endl;
                }
            } else {
                continue;
            }
        }

        if ((line.find(searchString) != std::string::npos)) {
            // print found one
            std::cout << "found one" << std::endl;
            outputFile << line << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();

    auto end_time = chrono::high_resolution_clock::now();
    auto duration =
        chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

    cout << "Time taken by while loop: " << duration.count() << " milliseconds"
         << endl;

    return 0;
}
