#include <iostream>
#include <fstream>
#include <vector>

void ReadFile(std::ifstream& myfile, const std::string& filename);
void ParseLine(const std::string& line, std::vector<int>& numbers);
void PrintVector(std::vector<int> input);
bool CheckValidity(std::vector<int>& numbers);

int main(int argc, char const** argv)
{
    std::string line;
    std::ifstream myfile;
    ReadFile(myfile, "input.txt");
    std::vector<int> numbers;
    int answer = 0;

    while ( getline (myfile,line) )
    {
        ParseLine(line, numbers);
        if (CheckValidity(numbers))
        {
            answer++;
        }
        numbers.clear();
    }
    std::cout << answer << std::endl;

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

void ParseLine(const std::string& line, std::vector<int>& numbers)
{
    int last_space = -1;
    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == ' ' && last_space == i-1)
        {
            last_space = i;
            continue;
        }
        else if (line[i] == ' ' && last_space != i-1)
        {
            std::string temp = line.substr(last_space+1, i-last_space);
            numbers.push_back(stoi(temp));
            last_space = i;
        }
    }
    // Get the last one
    std::string temp = line.substr(last_space+1);
    numbers.push_back(stoi(temp));
}

bool CheckValidity(std::vector<int>& numbers)
{
    if (numbers.size() < 3)
    {
        return false;
    }
    if (numbers[0] + numbers[1] <= numbers[2] ||
        numbers[1] + numbers[2] <= numbers[0] ||
        numbers[0] + numbers[2] <= numbers[1])
    {
        return false;
    }
    return true;
}

void PrintVector(std::vector<int> input)
{
    for (int i = 0; i < input.size(); ++i)
    {
        std::cout << input[i];
    }
    std::cout << std::endl;
}

