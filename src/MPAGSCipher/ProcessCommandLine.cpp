#include <string>
#include <vector>
#include <iostream>

bool processCommandLine(
    const std::vector<std::string>& cmdLineArgs,
    bool& helpRequested,
    bool& versionRequested,
    std::string& inputFileName,
    std::string& outputFileName)
    /* Processes given command line arguments and modifies variables appropriately
    
    const std::vector<std::string>& cmdLineArgs: vector of command-line arguments
    bool& helpRequested: determines if --help has been passed
    bool& versionRequested: determines if --version has been passed
    std::string& inputFileName: stores the input file name provided by -i
    std::string& outputFileName: stores the output file name provided by -o

    return: true if command line arguments are parsed successfully. false if any errors
    are thrown 
    */
{
    const std::size_t nCmdLineArgs{cmdLineArgs.size()};
    for (std::size_t i{1}; i < nCmdLineArgs; ++i) {
        if (cmdLineArgs[i] == "-h" || cmdLineArgs[i] == "--help") {
            helpRequested = true;
        } else if (cmdLineArgs[i] == "--version") {
            versionRequested = true;
        } else if (cmdLineArgs[i] == "-i") {
            // Handle input file option
            // Next element is filename unless "-i" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -i requires a filename argument"
                          << std::endl;
                return false;
            } else {
                // Got filename, so assign value and advance past it
                inputFileName = cmdLineArgs[i + 1];
                ++i;
            }
        } else if (cmdLineArgs[i] == "-o") {
            // Handle output file option
            // Next element is filename unless "-o" is the last argument
            if (i == nCmdLineArgs - 1) {
                std::cerr << "[error] -o requires a filename argument"
                          << std::endl;
                // exit main with non-zero return to indicate failure
                return false;
            } else {
                // Got filename, so assign value and advance past it
                outputFileName = cmdLineArgs[i + 1];
                ++i;
            }
        } else {
            // Have an unknown flag to output error message and return non-zero
            // exit status to indicate failure
            std::cerr << "[error] unknown argument '" << cmdLineArgs[i]
                      << "'\n";
            return false;
        }
    }
    return true;
}