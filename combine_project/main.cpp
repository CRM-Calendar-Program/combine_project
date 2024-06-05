#include <iostream>
#include "data_handler.h"
using namespace std;

int GetSize(string filename)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Unable to open file" << std::endl;
        return 0;
    }

    int size = 0;
    string line;
    while (getline(file, line))
    {
        size++;
    }

    file.close();
    return size + 10;
}

int main()
{
    string filename = "test1.csv";
    string filename_o = "test2.csv";
    int size;

    size = GetSize(filename);
    DataHandler DB(size);
    DB.ReadCSV(filename);
    DB.WriteCSV(filename_o);

    return 0;
}