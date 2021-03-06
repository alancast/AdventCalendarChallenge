#include <iostream>
#include <fstream>
#include <vector>
#include "md5.h"

void ReadFile(std::ifstream& myfile, const std::string& filename);
void PrintVector(std::vector<char> input);
bool HashStartsWith(const std::string& start, const std::string& input, 
                    std::string& hashed_output);
bool HashValidLocation(const std::string& hash, std::vector<char>& answer);
bool Finished(std::vector<char>& answer);

int main(int argc, char const** argv)
{
    std::string door_id;
    std::ifstream myfile;
    ReadFile(myfile, "input.txt");
    std::vector<char> answer;
    getline (myfile, door_id);
    long long append_num = 0;
    std::string hash_input = door_id;
    std::string hashed_output;
    std::string starting_match = "00000";
    hash_input.append(std::to_string(append_num));
    for (int i = 0; i < 8; ++i)
    {
        answer.push_back('_');
    }
    while (!Finished(answer))
    {
        while (!HashStartsWith(starting_match, hash_input, hashed_output)
                || !HashValidLocation(hashed_output, answer))
        {
            append_num++;
            hash_input = door_id;
            hash_input.append(std::to_string(append_num));
        }
        std::cout << hash_input << std::endl;
        std::cout << hashed_output << std::endl;
        answer[stoi(hashed_output.substr(5,1))] = hashed_output[6];
        append_num++;
        hash_input = door_id;
        hash_input.append(std::to_string(append_num));
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

bool HashStartsWith(const std::string& start, const std::string& input, 
                    std::string& hashed_output)
{
    hashed_output = md5(input);
    // std::cout << hashed_output << std::endl;
    if (hashed_output.substr(0, start.size()) == start)
    {
        return true;
    }
    return false;
}

bool HashValidLocation(const std::string& hash, std::vector<char>& answer)
{
    if (isdigit(hash[5]) && stoi(hash.substr(5,1)) <= 7
        && answer[stoi(hash.substr(5,1))] == '_')
    {
        return true;
    }
    return false;
}

bool Finished(std::vector<char>& answer)
{
    for (int i = 0; i < answer.size(); ++i)
    {
        if (answer[i] == '_')
        {
            return false;
        }
    }
    return true;
}

void PrintVector(std::vector<char> input)
{
    for (int i = 0; i < input.size(); ++i)
    {
        std::cout << input[i];
    }
    std::cout << std::endl;
}


