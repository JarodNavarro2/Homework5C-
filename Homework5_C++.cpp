#include "stdafx.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <vector>
#include <ctime> //needed for random array
#include <algorithm>

using namespace std;

void Bubble_Sort(int A[], int n);
void Insertion_Sort(int A[], int n);
void swap(int &x, int &y);
int partition(int a[], int left, int right, int pivotIndex);
void Quick_Sort(int a[], int left, int right);
void Shell_Sort(int A[], int n);
void merge(int A[], int low, int high, int mid);
void Merge_Sort(int A[], int low, int high);
int * Ar(string file);

int comparisons = 0; //every function uses these two integers. Making them public helps out with main//
int exchanges = 0;
//ALL FUNCTIONS ARE GIVEN BY THE BOOK//
void Bubble_Sort(int A[], int n)    //Bubble sorting
{
	int i, j, temp;
	for (i = 1; i < n; i++)      
	{
		for (j = 0; j < n - 1; j++)      
		{
			comparisons++;         
			if (A[j] > A[j + 1])     
			{
				temp = A[j];       
				A[j] = A[j + 1];
				A[j + 1] = temp;
				exchanges++;        
			}
		}
	}
	cout << "Bubble Comparisons: " << comparisons << endl; 
	cout << "Bubble Exchanges: " << exchanges << endl; 
	cout << endl; 
}

void Insertion_Sort(int A[], int n)    //Insertion sort
{
	int i, j, element;
	for (i = 1; i < n; i++)
	{
		element = A[i];     
		j = i;
		comparisons++;      
		while ((j > 0) && (A[j - 1] > element))     
		{

			A[j] = A[j - 1];        
			j = j - 1;
			exchanges++;        
			comparisons++;     
		}
		A[j] = element;         
	}
	cout << "Insertion Comparisons: " << comparisons << endl;   
	cout << "Insertion Exchanges: " << exchanges << endl;       
	cout << endl;
}

void swap(int &x, int &y)       //for Quick_Sort
{
	int temp;
	temp = x;
	x = y;
	y = temp;
}

int partition(int a[], int left, int right, int pivotIndex)     //for Quick_Sort
{
	int pivot = a[pivotIndex];      
	do
	{
		while (a[left] < pivot)
		{
			left++;     
			comparisons++;      
		}
		comparisons++;
		while (a[right] > pivot)
		{
			right--;        
			comparisons++;     
		}
		comparisons++;
		if (left < right && a[left] != a[right])
		{
			swap(a[left], a[right]);        
			exchanges++;        
		}
		else
		{
			return right;
		}
	} while (left < right);
	return right;
}

void Quick_Sort(int a[], int left, int right)
//Quick sorting, will call swap and partition function above
{
	if (left < right)
	{
		int pivot = (left + right) / 2;         
		int pivotNew = partition(a, left, right, pivot);
		Quick_Sort(a, left, pivotNew - 1);
		Quick_Sort(a, pivotNew + 1, right);
	}
}

void Shell_Sort(int A[], int n)     //Shell sorting
{
	int temp, gap, i;
	int swapped;
	gap = n / 2;
	do
	{
		do
		{
			swapped = 0;        
			for (i = 0; i < n - gap; i++)
			{
				comparisons++;      
				if (A[i] > A[i + gap])
				{
					temp = A[i];
					A[i] = A[i + gap];
					A[i + gap] = temp;
					swapped = 1;
					exchanges++;    
				}
			}
		} while (swapped == 1);    
	} while ((gap = gap / 2) >= 1);
	cout << "Shell Comparisons: " << comparisons << endl;   
	cout << "Shell Exchanges: " << exchanges << endl;       
	cout << endl; 
}

void merge(int A[], int low, int high, int mid)     //for Merge_Sort
{
	int i, j, k, C[10000];
	i = low;          
	j = mid + 1;     
	k = 0;          
	while ((i <= mid) && (j <= high))
	{
		comparisons++;      
		if (A[i] < A[j])
		{
			C[k] = A[i++];
			exchanges++;       
		}
		else
		{
			C[k] = A[j++];
			exchanges++;       
		}
		k++;
	}
	while (i <= mid)
	{
		C[k++] = A[i++];
		exchanges++;        
	}
	while (j <= high)
	{
		C[k++] = A[j++];
		exchanges++;        
	}
	for (i = low, j = 0; i < high; i++, j++)
		
	{
		A[i] = C[j];
	}
}

void Merge_Sort(int A[], int low, int high)     //Merge sorting, call to the function above
{
	int mid;
	if (low < high)
	{
		mid = (low + high) / 2;
		Merge_Sort(A, low, mid);
		Merge_Sort(A, mid + 1, high);
		merge(A, low, high, mid);       
	}
	return;
}

int  * Ar(string file)  //Needed to clear memory
{
	ifstream File;      
	File.open(file.c_str());     //opens file

	if (!File.is_open())     //confirmation
	{
		cout << "Can't open" << endl;
		 
		return false;
	}
	string temp;      //temp string
	string temp2 = " ";    //temp empty string
	while (File.peek() != EOF) //reading the file to the end
	
	{
		File >> temp;      //putting files into temp
		temp2 += temp + " "; //moving it
	}
	File.clear(); //clearing files
	File.close(); //closing files

	vector<string> words;    //vector to store words    
	temp = ""; //temp is now empty
	for (int i = 0; i < temp2.length(); i++)
	{
		if (temp2[i] == ' ') //if it's empty
		{
			words.push_back(temp); //push back
			temp = "";
		}
		else
		{
			temp += temp2[i]; //storing
		}
	}
	
	int * numbers = new int[words.size()]; //new array

	for (int i = 0; i < words.size(); i++)
	{
		numbers[i] = atoi(words[i].c_str()); //storing. ATOI NEEDED BECAUSE STOI CRASHES
	}
	
	
	return numbers; //return it
}

int main()
{
	srand(time(NULL)); //FOR RANDOM GENERATOR
	int * Numbers; //Needed for testing
	string File_location[4]; //Location for files
	File_location[0] = "FewUnique.txt"; //you know what this does
	cout << "FewUnique.txt" << endl;    
	File_location[1] = "NearlySorted.txt";
	cout << "NearlySorted.txt" << endl;     
	File_location[2] = "Random.txt";
	cout << "Random.txt" << endl;       
	File_location[3] = "Reversed.txt";
	cout << "Reversed.txt" << endl;     
	cout << endl;  

	for (int i = 0; i < 4; i++) //testing loooooop
	{
		
		Numbers = Ar(File_location[i]); //test bubble
		Bubble_Sort(Numbers, 10000);
		cout << "Bubble Comparisons: " << comparisons << endl;
		cout << "Bubble Exchanges: " << exchanges << endl;
		cout << endl;

		Numbers = Ar(File_location[i]); //test insert
		Insertion_Sort(Numbers, 10000);
		cout << "Insertion Comparisons: " << comparisons << endl;
		cout << "Insertion Exchanges: " << exchanges << endl;
		cout << endl;
		Numbers = Ar(File_location[i]); //test shell
		Shell_Sort(Numbers, 10000);
		cout << "Shell Comparisons: " << comparisons << endl;
		cout << "Shell Exchanges: " << exchanges << endl;
		cout << endl;

		Numbers = Ar(File_location[i]); //test quick
		Quick_Sort(Numbers, 0, 9999);
		cout << "Quick Comparisons: " << comparisons << endl;
		cout << "Quick Exchanges: " << exchanges << endl;
		cout << endl;

		Numbers= Ar(File_location[i]); //test merge
		Merge_Sort(Numbers, 0, 9999);
		cout << "Merge Comparisons: " << comparisons << endl;     
		cout << "Merge Exchanges: " << exchanges << endl;      
		cout << endl;   

	}
	cout << "Comparisons complete" << endl; 
	cout << "Files cleared." << endl;

	cout << "Would you like to test a different array? Y/N" << endl; //For your own test
	char answer;
	cin >> answer;
	if (answer == 'Y')
	{
		cout << "How big do you want the array to be?" << endl;//questions
		int size;//array size
		cin >> size;
		int * nums = new int[size];//creating new array based on size
	
		for (int i = 0; i < size; i++)
		{
			nums[i] = rand() % 100 + 1; //each number is randomly generated
			cout << nums[i] << endl; //to make sure it has numbers

		}
		//THE FUNCTIONS WORK AND GIVE ANSWERS, ALTHOUGH IT DOESN'T GET OUT THE LOOP. STILL WORKS TO AN EXTENT
		cout << "What do you want to test?" << endl;//asking what you want to test
		cout << "1)Bubble" << endl;
		cout << "2)Insert" << endl;
		cout << "3)Quick" << endl;
		cout << "4)Shell" << endl;
		cout << "5)Merge" << endl;
		int ans;
		cin >> ans;
		
			if (ans == 1)
			{
				Numbers = Ar(File_location[0]); //TESTING BUBBLE ON EACH FILE
				Bubble_Sort(Numbers, 10000);
				cout << "Bubble Comparisons: " << comparisons << endl;
				cout << "Bubble Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[1]);
				Bubble_Sort(Numbers, 10000);
				cout << "Bubble Comparisons: " << comparisons << endl;
				cout << "Bubble Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[2]);
				Bubble_Sort(Numbers, 10000);
				cout << "Bubble Comparisons: " << comparisons << endl;
				cout << "Bubble Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[3]);
				Bubble_Sort(Numbers, 10000);
				cout << "Bubble Comparisons: " << comparisons << endl;
				cout << "Bubble Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[4]);
				Bubble_Sort(Numbers, 10000);
				cout << "Bubble Comparisons: " << comparisons << endl;
				cout << "Bubble Exchanges: " << exchanges << endl;
				return true;
			}
			else if (ans == 2)
			{
				Numbers = Ar(File_location[0]); //TESTING INSERT ON EACH FILE
				Insertion_Sort(Numbers, 10000);
				cout << "Insert Comparisons: " << comparisons << endl;
				cout << "Insert Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[1]);
				Insertion_Sort(Numbers, 10000);
				cout << "Insert Comparisons: " << comparisons << endl;
				cout << "Insert Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[2]);
				Insertion_Sort(Numbers, 10000);
				cout << "Insert Comparisons: " << comparisons << endl;
				cout << "Insert Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[3]);
				Insertion_Sort(Numbers, 10000);
				cout << "Insert Comparisons: " << comparisons << endl;
				cout << "Insert Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[4]);
				Insertion_Sort(Numbers, 10000);
				cout << "Insert Comparisons: " << comparisons << endl;
				cout << "Insert Exchanges: " << exchanges << endl;
				cout << endl;
				return true;
				
			}
			else if (ans == 3)
			{
				Numbers = Ar(File_location[0]); //TESTING QUICK ON EACH FILE
				Quick_Sort(Numbers, 0, 9999);
				cout << "Quick Comparisons" << comparisons << endl;
				cout << "Quick Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[1]);
				Quick_Sort(Numbers, 0, 9999);
				cout << "Quick Comparisons: " << comparisons << endl;
				cout << "Quick Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[2]);
				Quick_Sort(Numbers, 0, 9999);
				cout << "Quick Comparisons: " << comparisons << endl;
				cout << "Quick Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[3]);
				Quick_Sort(Numbers, 0, 9999);
				cout << "Quick Comparisons: " << comparisons << endl;
				cout << "Quick Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[4]);
				Quick_Sort(Numbers, 0, 9999);
				cout << "Quick Comparisons: " << comparisons << endl;
				cout << "Quick Exchanges: " << exchanges << endl;
				cout << endl;
				return true;
			}
			else if (ans == 4)
			{
				Numbers = Ar(File_location[0]); //TESTING SHELL ON EACH FILE
				Shell_Sort(Numbers, 10000);
				cout << "Shell Comparisons: " << comparisons << endl;
				cout << "Shell Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[1]);
				Shell_Sort(Numbers, 10000);
				cout << "Shell Comparisons: " << comparisons << endl;
				cout << "Shell Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[2]);
				Shell_Sort(Numbers, 10000);
				cout << "Shell Comparisons: " << comparisons << endl;
				cout << "Shell Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[3]);
				Shell_Sort(Numbers, 10000);
				cout << "Shell Comparisons: " << comparisons << endl;
				cout << "Shell Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[4]);
				Shell_Sort(Numbers, 10000);
				cout << "Shell Comparisons: " << comparisons << endl;
				cout << "Shell Exchanges: " << exchanges << endl;
				return true;
			}
			else if (ans == 5)
			{
				Numbers = Ar(File_location[0]); //TESTING MERGE ON EACH FILE
				Merge_Sort(Numbers, 0, 9999);
				cout << "Merge Comparisons: " << comparisons << endl;
				cout << "Merge Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[1]);
				Merge_Sort(Numbers, 0, 9999);
				cout << "Merge Comparisons: " << comparisons << endl;
				cout << "Merge Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[2]);
				Merge_Sort(Numbers, 0, 9999);
				cout << "Merge Comparisons: " << comparisons << endl;
				cout << "Merge Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[3]);
				Merge_Sort(Numbers, 0, 9999);
				cout << "Merge Comparisons: " << comparisons << endl;
				cout << "Merge Exchanges: " << exchanges << endl;
				Numbers = Ar(File_location[4]);
				Merge_Sort(Numbers, 0, 9999);
				cout << "Merge Comparisons: " << comparisons << endl;
				cout << "Merge Exchanges: " << exchanges << endl;
				return true;
			}
		
		

	}
	else
	{
		cout << "Okay :(" << endl; //sad face because you no like me :(
		return false;
	}
	
	return 0;
}