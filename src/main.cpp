#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream>
#include <fstream>

struct Config
{
    std::string input = "bca.bf";
    std::string cpp_tmp_file = "_tmp_.cpp";
    std::string bf_tmp_file = "_tmp_.bf";
    std::string appName = "App.exe";
    bool executeWhenFinished = true;
    bool extendedBrainfuck = true;
} config;

void print(char const& chr, std::istream & in, std::ostream & out)
{
    if(in.get() == '*') 
    {
        int n = 1;
        if(in.get() == '\'')
        {
            if(in.get() != '\\') in.unget();

            n = in.get();

            if(in.get() != '\'') std::cout << "syntax error : missing ' at " << in.tellg() << std::endl;
        }
        else
        {
            in.unget();
            in >> n;
        }

        out << std::string(n, chr);
    }
    else
    {
        in.unget();
        out << chr;
    }
}

void transcompile_xbf_to_bf(std::istream & in, std::ostream & out)
{
    char chr = 0;
    while(!in.eof() && chr != EOF) {
        chr = in.get();
        switch(chr)
        {
        case '#': while(!in.eof() && in.get() != '#'); break;

        case '>':
        case '<':
        case '+':
        case '-':
        case '.':
        case ',':
        case '[':
        case ']':
            print(chr, in, out);
            break;
        
        default: break;
        }
    }
}

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
    std::ofstream ofs(config.cpp_tmp_file);

    transcompile(in, ofs);

    ofs.close();

    return std::system(("g++ " + config.cpp_tmp_file + " -o " + config.appName + " -O3 --std=c++17 -Wall").c_str());
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
                config.cpp_tmp_file = argv[i++];
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
        else if(cmd == "-ext")
        {
            config.extendedBrainfuck = true;
        }
        else if(cmd == "-noext")
        {
            config.extendedBrainfuck = false;
        }
    }
}

int main(int argc, char *argv[]) 
{
    loadConfig(argc, argv);

    std::ifstream in(config.input);

    if(config.extendedBrainfuck)
    {
        if(in.get() == '#' && in.get() == '!' && in.get() == 'x' && in.get() == 'b' && in.get() == 'f' && in.get() == '#') 
        {
            std::ofstream out(config.bf_tmp_file);

            transcompile_xbf_to_bf(in, out);

            out.close();
            in.close();
            in.open(config.bf_tmp_file);
        }
        else
        {
            in.seekg(0);
        }
    }

    compile(in);

    in.close();

    if(config.executeWhenFinished) 
    {
        return std::system((".\\" + config.appName).c_str());
    }

    return 0;
}