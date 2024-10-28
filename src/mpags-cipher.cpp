#include <cctype>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "TransformChar.hpp"
#include "ProcessCommandLine.hpp"
#include "RunCaesarCipher.hpp"

int main(int argc, char* argv[])
{
    // Convert the command-line arguments into a more easily usable form
    const std::vector<std::string> cmdLineArgs{argv, argv + argc};

    // Options that might be set by the command-line arguments
    bool helpRequested{false};
    bool versionRequested{false};
    std::string inputFile{""};
    std::string outputFile{""};
    size_t key{0};
    bool encrypt{true};

    // Process command-line arguments. Exit program if any errors are thrown
    if (!processCommandLine(cmdLineArgs, helpRequested, versionRequested, inputFile, outputFile, key, encrypt)){
        return 1;
    }

    // Handle help, if requested
    if (helpRequested) {
        // Line splitting for readability
        std::cout
            << "Usage: mpags-cipher [-h/--help] [--version] [-i <file>] [-o <file>]\n\n"
            << "Encrypts/Decrypts input alphanumeric text using classical ciphers\n\n"
            << "Available options:\n\n"
            << "  -h|--help        Print this help message and exit\n\n"
            << "  --version        Print version information\n\n"
            << "  -i FILE          Read text to be processed from FILE\n"
            << "                   Stdin will be used if not supplied\n\n"
            << "  -o FILE          Write processed text to FILE\n"
            << "                   Stdout will be used if not supplied\n\n"
            << "  -k KEY [0, 25]   Key for the Caesar Cipher (default: 0)\n\n"
            << "  -d               Decrypt flag"
            << std::endl;
        // Help requires no further action, so return from main
        // with 0 used to indicate success
        return 0;
    }

    // Handle version, if requested
    // Like help, requires no further action,
    // so return from main with zero to indicate success
    if (versionRequested) {
        std::cout << "0.1.0" << std::endl;
        return 0;
    }

    // Initialise variables
    char inputChar{'x'};
    std::string inputText;

    // Flag to determine whether to read from an input file or from console
    bool read_from_file{false};
    // std::ifstream in_file;
    // Read in user input from stdin/file
    if (!inputFile.empty()) {
        std::ifstream in_file{inputFile};
        if (!in_file.good()){
            std::cerr << "Cannot read from " << inputFile <<". Reverting to terminal input" << std::endl;
        }
        else{
            read_from_file = true;
            while(in_file >> inputChar){
            inputText += transformChar(inputChar);
        }
        }
    }
    else{
        std::cout << "No input file specifed. Reverting to terminal input" << std::endl;
    }

    if (!read_from_file){
        // loop over each character from user input
        while (std::cin >> inputChar) {
            inputText += transformChar(inputChar);
        }
    }
    
    // Run the cipher
    std::string cipherText = runCaesarCipher(inputText, key, encrypt);

    // Print out the transliterated text

    bool write_to_file{false};
    if (!outputFile.empty()) {
        std::ofstream out_file{outputFile};
        if (!out_file.good()){
            std::cerr << "Cannot write to " << outputFile <<". Reverting to terminal output" << std::endl;
        }
        else{
            write_to_file = true;
            out_file << cipherText;
        }
    }
    else{
        std::cout << "No output file specifed. Reverting to terminal output" << std::endl;
    }

    if (!write_to_file){
        std::cout << cipherText << std::endl;
    }


    // No requirement to return from main, but we do so for clarity
    // and for consistency with other functions
    return 0;
}
