//Name.......Yafet Kubrom
//EUID.......11334602
//Date.......3/21/2020
//Course.....CSCE3110.002
//....Program 3(Heap Sort).....

#include <iostream>
#include <vector>
#include <fstream>          // to open and write to a file
#include <string>
#include <sstream>          // for stringstream()
using namespace std;

void maxHeap(float arr[], int n, int i)
{
    int largest = i;    // initialize largest as the root
    int l = 2*i + 1;    // left child to parent i
    int r = 2*i + 2;    // right child to parent r

    // if left child is larger than root
    if (l < n && arr[l] > arr[largest]) largest = l;

    // if right child is larger 
    if (r < n && arr[r] > arr[largest]) largest = r;

    // if largest is not root
    if (largest != i)
    {
        swap(arr[i], arr[largest]);
        maxHeap(arr, n, largest);
    }
}

void heapsort(float arr[], int n)
{
    //build heap
    for(int i = n/2-1; i >= 0; i--) maxHeap(arr, n, i);

    //extract one-by-one
    for(int i = n-1; i>=0; i--) 
    {
        swap(arr[0], arr[i]);   // move current root to end
        maxHeap(arr, i, 0);        // turn reduced array into maxHeap
    }
}

int main()
{
    int index = 0;      // counter for the array
    string line;        // temporary variable for line by line
    float k;            // temporary variable for number by number
    float array[100];   // assuming input of 500 or less
    ifstream read("data3.txt"); //open input file
    ofstream write("output3.txt"); //open output file
    if(!read)
    {
        cout << "data3.txt does not exist on current directory" << endl;
        exit(1);
    }

    while(getline(read,line))   //getline() goes line by line 
    {
        stringstream tmp (line);
        while(tmp >> k) array[index++] = k;
        heapsort(array,index);
        for(int i = 0; i < index; i++)
        {
            write << array[i] << " ";
        }
        write << endl;  //start new line
        index = 0;      // restart index for new array
    }
    read.close();
    write.close();
}