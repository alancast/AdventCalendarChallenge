#include <iostream>
#include <fstream>
#include <vector>
#include <map>

void ReadFile(std::ifstream& myfile, const std::string& filename);
void PrintVector(std::vector<char> input);

int main(int argc, char const** argv)
{
    std::string line;
    std::ifstream myfile;
    ReadFile(myfile, "input.txt");
    std::vector<char> answer;
    std::vector<int> answer_count;

    // Key is (index,char) value is count of that
    std::map<std::pair<int,char>, int> characters;
    while ( getline (myfile,line) )
    {
        for (int i = 0; i < line.size(); ++i)
        {
            if (characters.find(std::make_pair(i, line[i])) == characters.end())
            {
                characters[std::make_pair(i,line[i])] = 1;
            }
            else
            {
                characters[std::make_pair(i,line[i])]++;
            }
        }
    }

    for (int i = 0; i < line.size(); ++i)
    {
        answer.push_back('_');
        answer_count.push_back(1000000);
    }

    for (std::map<std::pair<int,char>, int>::iterator it = characters.begin();
            it != characters.end(); ++it)
    {
        if (it->second < answer_count[it->first.first])
        {
            answer_count[it->first.first] = it->second;
            answer[it->first.first] = it->first.second;
        }
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


