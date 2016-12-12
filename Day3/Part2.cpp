#include <iostream>
#include <fstream>
#include <vector>

void ReadFile(std::ifstream& myfile, const std::string& filename);
void ParseLines(const std::string& line, 
                const std::string& line2,
                const std::string& line3,
                std::vector<std::vector<int>>& numbers);
void ParseLine(const std::string& line, std::vector<int>& numbers);
void PrintVector(std::vector<int> input);
int CheckValidity(std::vector<std::vector<int>>& numbers);

int main(int argc, char const** argv)
{
    std::string line, line2, line3;
    std::ifstream myfile;
    ReadFile(myfile, "input.txt");
    std::vector<std::vector<int>> numbers;
    int answer = 0;

    while ( getline (myfile,line) && getline(myfile, line2) && getline(myfile, line3))
    {
        ParseLines(line, line2, line3, numbers);
        answer += CheckValidity(numbers);
        for (int i = 0; i < numbers.size(); ++i)
        {
            numbers[i].clear();
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

void ParseLines(const std::string& line, 
                const std::string& line2,
                const std::string& line3,
                std::vector<std::vector<int>>& numbers)
{
    std::vector<int> temp;
    ParseLine(line, temp);
    numbers.push_back(temp);
    temp.clear();
    ParseLine(line2, temp);
    numbers.push_back(temp);
    temp.clear();
    ParseLine(line3, temp);
    numbers.push_back(temp);
    temp.clear();
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

int CheckValidity(std::vector<std::vector<int>>& numbers)
{
    if (numbers.size() < 3)
    {
        return 0;
    }

    int num_valid = 0;
    for (int i = 0; i < numbers.size(); ++i)
    {
        if (numbers[0][i] + numbers[1][i] <= numbers[2][i] ||
            numbers[1][i] + numbers[2][i] <= numbers[0][i] ||
            numbers[0][i] + numbers[2][i] <= numbers[1][i])
        {
            continue;
        }
        num_valid++;
    }
    return num_valid;
}

void PrintVector(std::vector<int> input)
{
    for (int i = 0; i < input.size(); ++i)
    {
        std::cout << input[i];
    }
    std::cout << std::endl;
}

