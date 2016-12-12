#include <iostream>
#include <fstream>
#include <vector>

void ReadFile(std::ifstream& myfile, const std::string& filename);
void PrintVector(std::vector<char> input);
void ComputeNumber(const std::string& line, std::pair<int,int>& coordinates);
void ComputeNextPosition(char direction, std::pair<int,int>& coordinates);

char keypad[7][7] = {
        {'x','x','x','x','x','x','x'},
        {'x','x','x','1','x','x','x'},
        {'x','x','2','3','4','x','x'},
        {'x','5','6','7','8','9','x'},
        {'x','x','A','B','C','x','x'},
        {'x','x','x','D','x','x','x'},
        {'x','x','x','x','x','x','x'}
    };

int main(int argc, char const** argv)
{
    std::string line;
    std::ifstream myfile;
    ReadFile(myfile, "input1.txt");
    std::vector<char> answer;
    // y then x coordinate
    auto coordinates = std::make_pair(3,1);

    while ( getline (myfile,line) )
    {
        ComputeNumber(line, coordinates);
        answer.push_back(keypad[coordinates.first][coordinates.second]);
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

void ComputeNumber(const std::string& line, std::pair<int,int>& coordinates)
{
    auto current_coordinates(coordinates);
    for (int i = 0; i < line.size(); ++i)
    {
        char direction = line[i];
        ComputeNextPosition(direction, current_coordinates);
    }
    coordinates.first = current_coordinates.first;
    coordinates.second = current_coordinates.second;
}

void ComputeNextPosition(char direction, std::pair<int,int>& coordinates)
{
    switch (direction) 
    {
        case 'U': 
            if (keypad[coordinates.first-1][coordinates.second] != 'x')
            {
                coordinates.first -= 1;
            }
            break;
        case 'D': 
            if (keypad[coordinates.first+1][coordinates.second] != 'x')
            {
                coordinates.first += 1;
            }
            break;
        case 'L': 
            if (keypad[coordinates.first][coordinates.second-1] != 'x')
            {
                coordinates.second -= 1;
            }
            break;
        case 'R': 
            if (keypad[coordinates.first][coordinates.second+1] != 'x')
            {
                coordinates.second += 1;
            }
            break;
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

