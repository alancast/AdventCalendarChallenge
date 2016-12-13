#include <iostream>
#include <fstream>
#include <vector>

void ReadFile(std::ifstream& myfile, const std::string& filename);
void PrintVector(std::vector<char> input);

int main(int argc, char const** argv)
{
    std::string line;
    std::ifstream myfile;
    ReadFile(myfile, "inputTest.txt");
    std::vector<char> answer;

    while ( getline (myfile,line) )
    {
        // answer += CheckValidity(line);
    }

    PrintVector(answer);

    return 0;
}

void ReadFile(std::ifstream &myfile, const std::string& filename)
{
    myfile.open(filename);
    if (!myfile.is_open())
    {
        std::cout << "Unable to open file " << filename << std::endl; 
        exit(1);
    }
}

void PrintVector(std::vector<char> input)
{
    for (int i = 0; i < input.size(); ++i)
    {
        std::cout << input[i];
    }
    std::cout << std::endl;
}


