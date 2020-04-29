//Name........Yafet Kubrom
//EUID........11334602
//Date........2/18/2020
//Course......CSCE3110.002
//......PartB........

#include <iostream>
#include <vector>
#include <fstream>      //To open and write to a file
#include <string>
#include <sstream>      // for stringstream()
using namespace std;

void merge(float arr[], const int low, const int mid, const int high);
void mergeSort(float arr[], const int low, const int high);
void insertionSort(float arr[], int a, int b);


int main()
{
    int index = 0;
    string line;        //temporary variable for holding one line a time 
    float k;            // k is temporary variable for holdin one number from a line
    float array[500];     // array size to be 500
    ifstream read("data1.txt");     // open the input file
    ofstream write("out1.txt");     // open the output file
    if(!read)                       // test if the input file is on directory 
    {   
        cout << "data1.txt does not exist on current directory" << endl;
        exit(1);
    }

    while(getline(read,line))           // getline breaks file to lines and put one line into var line.
    {
        stringstream tmp (line);
        while(tmp >> k) array[index++] = k;
        mergeSort(array, 0, (index - 1));
        for(int i = 0; i < index; i++)      //must be auto
        {
            write << array[i] << " ";         
        }
        write << endl;
        index = 0;  //restarts the array
                 
    }
    read.close();
    write.close();
}

void merge(float arr[], const int low, const int mid, const int high)
{
  float *temp = new float[high-low+1];

  int left = low;
  int right = mid+1;
  int current = 0;
  // Merges the two arrays into temp[]
  while(left <= mid && right <= high)
  {
    if(arr[left] <= arr[right])
    {
      temp[current] = arr[left];
      left++;
    }

    else
    {
      temp[current] = arr[right];     // if right element is smaller that the left
      right++;
    }
    current++;
  }


  if(left > mid)
  {
    for(int i=right; i <= high;i++)
    {
      temp[current] = arr[i];
      current++;
    }
  }

  else
  {
    for(int i=left; i <= mid; i++)
    {
      temp[current] = arr[i];
      current++;
    }
  }

  // into the original array
  for(int i=0; i<=high-low;i++) arr[i+low] = temp[i];
  delete[] temp;
}


void mergeSort(float arr[], const int low, const int high)
{
  if((high-low) <= 8) 
  {
    insertionSort(arr,low,high);
    return;
  }
  int mid = (low+high)/2;
  mergeSort(arr, low, mid);  //left half
  mergeSort(arr, mid+1, high);  //right half
  merge(arr, low, mid, high);  //merge them
}

void insertionSort(float arr[], int a, int b)  
{  
    int i, j;
    float key;  
    for (i = a+1; i <= b; i++) 
    {  
        key = arr[i];  
        j = i - 1;  
        while (j >= 0 && arr[j] > key) 
        {  
            arr[j + 1] = arr[j];  
            j = j - 1;  
        }  
        arr[j + 1] = key;  
    }  
}  

