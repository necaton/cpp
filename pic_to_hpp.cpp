//#include "picture.hpp"
//Texture texture;
//texture.loadFromMemory(picture, sizeof(picture));

#include <fstream>
#include <iomanip>
#include <iostream>

int main(int argc, char** argv)
{
	std::string name, charArray;
	std::cout<<"file: ";
	std::cin>>name;
	std::cout<<"\narray name: ";
	std::cin>>charArray;
	
    std::ifstream in(name, std::ios_base::binary);
    std::ofstream out("header.hpp");

    out << "const char "<<charArray<<"[] =" << std::endl;
    out << "{" << std::endl;
    do
    {
        out << "    ";
        for (int i = 0; (i < 20) && in; ++i)
            out << "0x" << std::hex << std::setw(2) << std::setfill('0') << in.get() << std::dec << ", ";
        out << std::endl;
    }
    while (in);
    out << "};" << std::endl;

    return 0;
}