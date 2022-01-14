#include <iostream>
#include <fstream>

using namespace std;

// Delete n-th line from given file
void delete_line(const char *file_name, int n)
{
    // open file in read mode or in mode
    ifstream is(file_name);

    // open file in write mode or out mode
    ofstream ofs;
    ofs.open("temp.txt", ofstream::out);

    // loop getting single characters
    char c;
    int line_no = 1;
    while (is.get(c))
    {
        // if a newline character
        if (c == '\n')
            line_no++;

        // file content not to be deleted
        if (line_no != n)
            ofs << c;
    }

    // closing output file
    ofs.close();

    // closing input file
    is.close();

    // remove the original file
    remove(file_name);

    // rename the file
    rename("temp.txt", file_name);
}

bool find_in_file(string filename, string match)
{
    ifstream fin(filename, ios::in);

    string line;
    while (getline(fin, line))
    {
        if (line.find(match) != string::npos)
        {
            fin.close();
            return true;
        }
    }
    if (fin.is_open())
    {
        fin.close();
    }
    return false;
}