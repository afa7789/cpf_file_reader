#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <vector>

using namespace std;

int main(int argc, const char **argv){

    // hello world
    std::cout << "Hello World!" << std::endl;

    if( argc < 4 || argc > 6 ){
        std::cerr << "Usage: cpf_file_reader <input_file_path> <output_file_path> <search_string> [<older_than>] [<younger_than>], [] means optional" << std::endl;
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
    if (argc <= 6) {
        // receive older than from argv
        olderThan = atoi(argv[4]);
        std::cout << "olderThan: " << olderThan << std::endl;
        if (argc == 6) {
            // receive younger than from argv
            youngerThan =  atoi(argv[5]);
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


    std::time_t t = std::time(nullptr);
    std::tm* local_time = std::localtime(&t);
    int current_year = local_time->tm_year + 1900;

    std::string line;
    std::cout << "searching !" << std::endl;
    while (std::getline(inputFile, line)) {
        
        // separate line by | 
        std::vector<std::string> seglist;
        // std::stringstream ss = "";
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, '|')) {
            seglist.push_back(token);
        }

        // debug seglist print it
        // std::cout << "seglist size: " << seglist.size() << std::endl;
        // for (int i = 0; i < seglist.size(); i++) {
        //     std::cout << seglist[i] << std::endl;
        // }

        std::istringstream datedSS(seglist[3]);
        std::tm tm = {};

        // parsing date as this format : 05/10/1979
        datedSS >> std::get_time(&tm, "%d/%m/%Y");

        bool betweenAges = false;
        // if (datedSS.fail()) {
            // if (seglist[3] == "N/D") {
            //     std::cout << "N/D achei" << std::endl;
            // }else{
                // std::cout << "Failed to parse date" << std::endl;
                // betweenAges = false;
            // }
        // } else {
         if (!datedSS.fail()) {
            if ( olderThan == 0 && youngerThan == 200 ) {
                std::cout << "not considering age" << std::endl;
                // not considering age
                betweenAges = true;
            }else {
                // current_year - year from input 
                int age = current_year - ( tm.tm_year + 1900 );
                // std::cout << "age: " << age << std::endl;
                if (age >= olderThan && age <= youngerThan) {
                    std::cout << "age: " << age << std::endl;
                    betweenAges = true;
                }
            }
        }

        // the last position of the seglist array is a time in format : 05/10/1979
        if ( (line.find(searchString) != std::string::npos) && betweenAges ) {
            // print found one
            std::cout << "found one" << std::endl;
            outputFile << line << std::endl;
        }
    }

    inputFile.close();
    outputFile.close();
    std::cout << "closed files..." << std::endl;
    return 0;
}
