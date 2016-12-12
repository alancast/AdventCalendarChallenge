#include <iostream>
#include <fstream>
#include <map>
#include <set>

struct SetComparator {
    bool operator()(std::pair<char,int> a, std::pair<char,int> b) 
    {
        if (a.second == b.second)
        {
            return a.first < b.first;
        }
        return a.second > b.second;
    }
};

void ReadFile(std::ifstream& myfile, const std::string& filename);
int CheckValidity(const std::string& line);
void ParseLine(const std::string& line, std::map<char, int>& characters,
                int& id, std::string& checksum);
void CreateSet(std::map<char, int>& characters,
                std::set<std::pair<char,int>, SetComparator>& ordered_characters);
void RotateAndPrintRoomName(std::string line, int sector_id);
char Rotate(char input, int num_rotations);

int main(int argc, char const** argv)
{
    std::string line;
    std::ifstream myfile;
    ReadFile(myfile, "input.txt");
    int answer = 0;

    while ( getline (myfile,line) )
    {
        answer += CheckValidity(line);
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

int CheckValidity(const std::string& line)
{
    int id = 0;
    std::string checksum;
    std::map<char, int> characters;
    ParseLine(line, characters, id, checksum);
    std::set<std::pair<char,int>, SetComparator> ordered_characters;
    CreateSet(characters, ordered_characters);
    int i = 0;
    if (ordered_characters.size() < 5)
    {
        return 0;
    }
    for (std::set<std::pair<char,int>>::iterator it=ordered_characters.begin(); 
            it!=ordered_characters.end(); ++it)
    {
        if (i == 5)
        {
            break;
        }
        if (it->first != checksum[i])
        {
            return 0;
        }
        i++;
    }
    // The room is valid so rotate it and print it's name
    RotateAndPrintRoomName(line, id);
    return id;
}

void ParseLine(const std::string& line, std::map<char, int>& characters,
                int& id, std::string& checksum)
{
    int id_start = 0;
    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == '-')
        {
            continue;
        }
        if (isdigit(line[i]))
        {
            if (id_start == 0)
            {
                id_start = i;
            }
            continue;
        }
        if (line[i] == '[')
        {
            id = stoi(line.substr(id_start, i-id_start));
            checksum = line.substr(i+1, 5);
            break;
        }
        if (characters.find(line[i]) == characters.end())
        {
            characters[line[i]] = 1;
            continue;
        }
        else
        {
            characters[line[i]]++;
        }
    }
}

void CreateSet(std::map<char, int>& characters,
                std::set<std::pair<char,int>, SetComparator>& ordered_characters)
{
    for (std::map<char,int>::iterator it=characters.begin(); 
        it!=characters.end(); ++it)
    {
        ordered_characters.insert(std::make_pair(it->first, it->second));
    }
}

void RotateAndPrintRoomName(std::string line, int sector_id)
{
    for (int i = 0; i < line.size(); ++i)
    {
        if (line[i] == '-')
        {
            continue;
        }
        if (isdigit(line[i]))
        {
            break;
        }
        line[i] = Rotate(line[i], sector_id);
    }
    std::cout << line << std::endl;
}

char Rotate(char input, int num_rotations)
{
    char newchar = ((input - 'a') + num_rotations) % 26;
    return newchar + 'a';
}

