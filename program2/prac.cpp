#include <iostream>
#include <fstream>      //To open and write to a file
#include <string>
#include <sstream>      // for stringstream()
using namespace std;

int main()
{
    int index = 0;      // counter for array
    string line;        // temporarly hold line from input file
    int k;              // temporarly hold one number from line
    int array[500];     
    ifstream read("data2.txt");
    ofstream write("out2.txt");
    if(!read)
    {
        cout << "data2.txt does not exist on current directory" << endl;
        exit(1);
    }

    while(getline(read,line))   //getline() breaks up file to lines and input one line at a time
    {
        stringstream tmp (line);
        while(tmp >> k) array[index++] = k+1;
        for(int i = 0; i < index; i++)
        {
            write << array[i] << " ";
        }
        write << endl;
        index = 0;
     }
     read.close();
     write.close();
}
