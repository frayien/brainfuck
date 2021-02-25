#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

struct Config
{
    std::string input = "echo.bf";
    std::string output = "output.cpp";
    std::string appName = "App.exe";
    bool executeWhenFinished = false;
} config;

void transcompile(std::istream & in, std::ostream & out)
{
    out << "#include <iostream>\n";
    out << "#include <cstdio>\n";
    out << "int main() {";
    out << "char buffer[30000] = {0};";
    out << "char *ptr = buffer;";
    
    while(!in.eof()) {
        switch (in.get())
        {
        case '>': out << "ptr++;"; break;
        case '<': out << "ptr--;"; break;
        case '+': out << "++(*ptr);"; break;
        case '-': out << "--(*ptr);"; break;
        case '.': out << "putchar(*ptr);"; break;
        //case '?': out << "std::cout << (int) *ptr << ' ';"; break;
        case ',': out << "*ptr=getchar();"; break;
        case '[': out << "while(*ptr){"; break;
        case ']': out << "}"; break;
        
        default: break;
        }
    }

    out << "return 0;}";
}

int compile(std::istream & in) 
{
    std::ofstream ofs(config.output);

    transcompile(in, ofs);

    ofs.close();

    return std::system(("g++ " + config.output + " -o " + config.appName + " -O3 --std=c++17 -Wall").c_str());
}

void loadConfig(int argc, char *argv[])
{
    int i = 1;
    while(i < argc)
    {
        std::string cmd(argv[i++]);
        if(cmd == "-o")
        {
            if(i < argc)
            {
                config.appName = argv[i++];
            }
        }
        else if(cmd == "-i")
        {
            if(i < argc)
            {
                config.input = argv[i++];
            }
        }
        else if(cmd == "-t")
        {
            if(i < argc)
            {
                config.output = argv[i++];
            }
        }
        else if(cmd == "-exe")
        {
            config.executeWhenFinished = true;
        }
        else if(cmd == "-noexe")
        {
            config.executeWhenFinished = false;
        }
    }
}

int main(int argc, char *argv[]) 
{
    loadConfig(argc, argv);

    std::ifstream in(config.input);

    compile(in);

    in.close();

    if(config.executeWhenFinished) 
    {
        return std::system((".\\" + config.appName).c_str());
    }

    return 0;
}