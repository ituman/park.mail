#include<iostream>
#include <fstream>
#include <algorithm>

using namespace std;

const char* OPT_COUNT_VARIANTS = "-c";
const char* OPT_PPARAM = "-p";
const char* OPT_FILENAME = "-f";
const char* OPT_HELP  = "-h";

char* getCmdOption(char ** begin, char ** end, const string & option)
{
    char ** itr = find(begin, end, option);
    if (itr != end && ++itr != end)
    {
        return *itr;
    }
    return 0;
}

bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}


int main(int argc, char * argv[]){
    if (cmdOptionExists(argv, argv + argc, OPT_HELP) || argc == 1) {
        cout << "To set filename use flag: " << OPT_FILENAME << endl;
        cout << "To set pparam use flag: " << OPT_PPARAM << endl;
        cout << "To set count variants use flag: " << OPT_COUNT_VARIANTS << endl;
        return 0;
    }

    char* filename = getCmdOption(argv, argv + argc, OPT_FILENAME);
    if (!filename) {
        cout << "File name must be set: use flag " << OPT_FILENAME << endl;
        return 1;
    }

    char* pParam = getCmdOption(argv, argv + argc, OPT_PPARAM);
    if (!pParam) {
        cout << "PParam must be set: use flag " << OPT_PPARAM << endl;
        return 1;
    }

    int countVariants;
    char * rawCountVariants = getCmdOption(argv, argv + argc, OPT_COUNT_VARIANTS);
    if (!rawCountVariants) {
        cout << "Count variants must be set: use flag " << OPT_COUNT_VARIANTS << endl;
        return 1;
    }
    try {
        countVariants = stoi(rawCountVariants);
    }
    catch(exception) {
        cout << "error: count variants option must be integer" << endl;
        return 1;
    }

    ifstream f(filename);
    if (f.is_open()) {
        hash<string> strHash;
        string line;
        while(getline(f,line)) 
        {
            cout << line << ": " << ((strHash(line) ^ strHash(pParam) ^ strHash(line + pParam)) % countVariants) + 1 << endl;
        }
        f.close();
    } else {
        cout << "Can`t open file " << filename << endl;
        return 1;
    }

    return 0;
}