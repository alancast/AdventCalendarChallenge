#include <iostream>
#include <fstream>
#include <vector>
#include <set>

void ReadFile(std::ifstream& myfile, const std::string& filename);
void PopulateDirectionsVector(std::vector<std::pair<char, int> >& directions, 
                                const std::string& line);
void SetFacingValue(int& facing, char turn);
void ModifyCoordinates(std::pair<int, int>& coordinates, 
                        int facing, int distance);

int ComputeDistance(std::vector<std::pair<char, int> >& directions);

bool WalkPath(std::set<std::pair<int,int>>& already_seen,
                std::pair<int, int>& coordinates, int facing, int distance);

int main(int argc, char const** argv)
{
    std::string line;
    std::ifstream myfile;
    ReadFile(myfile, "input1.txt");

    while ( getline (myfile,line) )
    {
        std::vector<std::pair<char,int> > directions;
        PopulateDirectionsVector(directions, line);
        int answer = ComputeDistance(directions);
        std::cout<< "The answer is " << answer << std::endl;
    }
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

void PopulateDirectionsVector(std::vector<std::pair<char, int> >& directions,
                                const std::string& line)
{
    int prev = 0;
    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == ',')
        {
            std::string temp = line.substr(prev, i-prev);
            // To remove the comma and space
            prev = i+2;
            char temp_char = temp[0];
            int temp_distance = stoi(temp.substr(1,temp.size()-1));
            directions.push_back(std::make_pair(temp_char, temp_distance));
        }
    }
    // Get the last one
    std::string temp = line.substr(prev, line.size());
    char temp_char = temp[0];
    int temp_distance = stoi(temp.substr(1,temp.size()-1));
    directions.push_back(std::make_pair(temp_char, temp_distance));
}

int ComputeDistance(std::vector<std::pair<char, int> >& directions)
{
    auto coordinates = std::make_pair(0,0);
    // 0=N, 1=E, 2=S, 3=W
    int facing = 0;
    std::set<std::pair<int,int>> already_seen;
    already_seen.insert(std::make_pair(0,0));
    for (int i = 0; i < directions.size(); ++i)
    {
        auto temp_pair = directions[i];
        SetFacingValue(facing, temp_pair.first);
        // ModifyCoordinates(coordinates, facing, temp_pair.second);
        if (WalkPath(already_seen, coordinates, facing, temp_pair.second))
        {
            std::cout << coordinates.first << " " << coordinates.second << std::endl;
            return abs(coordinates.first) + abs(coordinates.second);
        }
    }
    return abs(coordinates.first) + abs(coordinates.second);
}

void SetFacingValue(int& facing, char turn)
{
    if (turn == 'L')
    {
        facing -= 1;
        if (facing == -1)
        {
            facing = 3;
        }
    }
    else if (turn == 'R')
    {
        facing += 1;
        if (facing == 4)
        {
            facing = 0;
        }
    }
}

void ModifyCoordinates(std::pair<int, int>& coordinates, 
                        int facing, int distance)
{
    switch (facing) 
    {
        case 0: 
            coordinates.second = coordinates.second + distance;
            break;
        case 1: 
            coordinates.first = coordinates.first + distance;
            break;
        case 2: 
            coordinates.second = coordinates.second - distance;
            break;
        case 3: 
            coordinates.first = coordinates.first - distance;
            break;
    }
}

// Returns true if we have already seen that coordinate
// And final coordiantes value is the final destination
bool WalkPath(std::set<std::pair<int,int>>& already_seen,
                std::pair<int, int>& coordinates, int facing, int distance)
{
    int x = coordinates.first;
    int y = coordinates.second;
    switch (facing) 
    {
        case 0: 
            for (int i = 1; i <= distance; ++i)
            {
                if (already_seen.find(std::make_pair(x,y+i)) != already_seen.end())
                {
                    coordinates.second += i;
                    return true;
                }
                else
                {
                    already_seen.insert(std::make_pair(x,y+i));
                }
            }
            coordinates.second = coordinates.second + distance;
            break;
        case 1: 
            for (int i = 1; i <= distance; ++i)
            {
                if (already_seen.find(std::make_pair(x+i,y)) != already_seen.end())
                {
                    coordinates.first += i;
                    return true;
                }
                else
                {
                    already_seen.insert(std::make_pair(x+i,y));
                }
            }
            coordinates.first = coordinates.first + distance;
            break;
        case 2: 
            for (int i = 1; i <= distance; ++i)
            {
                if (already_seen.find(std::make_pair(x,y-i)) != already_seen.end())
                {
                    coordinates.second -= i;
                    return true;
                }
                else
                {
                    already_seen.insert(std::make_pair(x,y-i));
                }
            }
            coordinates.second = coordinates.second - distance;
            break;
        case 3: 
            for (int i = 1; i <= distance; ++i)
            {
                if (already_seen.find(std::make_pair(x-i,y)) != already_seen.end())
                {
                    coordinates.first -= i;
                    return true;
                }
                else
                {
                    already_seen.insert(std::make_pair(x-i,y));
                }
            }
            coordinates.first = coordinates.first - distance;
            break;
    }
    return false;
}
