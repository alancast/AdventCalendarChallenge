#include <iostream>
#include <fstream>
#include <vector>

void ReadFile(std::ifstream& myfile, const std::string& filename);
void PrintVector(std::vector<int> input);
int ComputeNumber(const std::string& line, int starting_pos);
int ComputeNextPosition(char direction, int current_pos);

int main(int argc, char const** argv)
{
    std::string line;
    std::ifstream myfile;
    ReadFile(myfile, "input1.txt");
    std::vector<int> answer;
    int starting = 5;

    while ( getline (myfile,line) )
    {
        starting = ComputeNumber(line, starting);
        answer.push_back(starting);
    }
    PrintVector(answer);
    myfile.close();

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

int ComputeNumber(const std::string& line, int starting_pos)
{
    int current = starting_pos;
    for (int i = 0; i < line.size(); ++i)
    {
        char direction = line[i];
        current = ComputeNextPosition(direction, current);
    }
    return current;
}

int ComputeNextPosition(char direction, int current_pos)
{
    switch (direction) 
    {
        case 'U': 
            if (current_pos - 3 > 0)
            {
                current_pos -= 3;
            }
            break;
        case 'D': 
            if (current_pos + 3 <= 9)
            {
                current_pos += 3;
            }
            break;
        case 'L': 
            if (current_pos != 1 && current_pos != 4 && current_pos != 7)
            {
                current_pos -= 1;
            }
            break;
        case 'R': 
            if (current_pos != 3 && current_pos != 6 && current_pos != 9)
            {
                current_pos += 1;
            }
            break;
    }
    return current_pos;
}

void PrintVector(std::vector<int> input)
{
    for (int i = 0; i < input.size(); ++i)
    {
        std::cout << input[i];
    }
    std::cout << std::endl;
}

