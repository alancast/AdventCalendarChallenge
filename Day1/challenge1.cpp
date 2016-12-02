#include <iostream>
#include <fstream>
#include <boost/tokenizer.hpp>

int ComputeDistance(const std::string& path);

int main(int argc, char const** argv)
{
    std::string line;
    std::ifstream myfile ("input1.txt");

    if (!myfile.is_open())
    {
        std::cout << "Unable to open file"; 
    }

    while ( getline (myfile,line) )
    {
        int answer = ComputeDistance(line);
        std::cout<< "The answer is " << answer << std::endl;
    }
    myfile.close();

    return 0;
}

int ComputeDistance(const std::string& path)
{
    char_separator<char> sep(", ");
    tokenizer<char_separator<char>> tokens(path, sep);
    for (const auto& t : tokens) {
        cout << t << "." << endl;
    }
    return path.size();
}
