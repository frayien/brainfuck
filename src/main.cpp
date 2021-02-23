#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

struct Config
{
    std::string output = "output.cpp";
    std::string appName = "App.exe";
    bool executeWhenFinished = true;
} config;

std::string transcompile(std::string const& brainfuckRaw)
{
    std::stringstream ccode;

    ccode << "#include <cstdio>\n";
    ccode << "#include <iostream>\n";
    ccode << "int main() {";
    ccode << "char buffer[30000] = {0};";
    ccode << "char *ptr = buffer;";

    for(char c : brainfuckRaw) {
        switch (c)
        {
        case '>': ccode << "ptr++;"; break;
        case '<': ccode << "ptr--;"; break;
        case '+': ccode << "++(*ptr);"; break;
        case '-': ccode << "--(*ptr);"; break;
        case '.': ccode << "putchar(*ptr);"; break;
        case '?': ccode << "std::cout << (int) *ptr << ' ';"; break;
        case ',': ccode << "*ptr=getchar();"; break;
        case '[': ccode << "while(*ptr){"; break;
        case ']': ccode << "}"; break;
        
        default: break;
        }
    }

    ccode << "return 0;}";

    return ccode.str();
}

int compile(std::string brainfuckRaw) 
{
    std::ofstream ofs(config.output);

    ofs << transcompile(brainfuckRaw);

    ofs.close();

    return std::system(("g++ " + config.output + " -o " + config.appName + " -O3 --std=c++17 -Wall").c_str());
}

void loadConfig(int argc, char *argv[])
{
    
}

int main(int argc, char *argv[]) 
{
    config.executeWhenFinished = false;
    loadConfig(argc, argv);

    std::string brainfuckRaw = ">----------[++++++++++>,----------]++++++++++[<]>[.>]";

    compile(brainfuckRaw);

    if(config.executeWhenFinished) 
    {
        return std::system((".\\" + config.appName).c_str());
    }

    return 0;
}