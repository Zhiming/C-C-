#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;

ofstream outfile;

int AskOption(int&); //commands to be run next

int AskMem(double&); // ask for memory

int MemReturn(double&, double); // return memory

double Allocation(double, int); //allocating memory

int main()
{
	ofstream outfile;
	outfile.open("Memory Allocation Information.txt");
	cout << "Please enter the amount of total available memory in megabytes: ";
	double dMemory = 0;
	cin >> dMemory;
	cout  << "The amount of total available memory is: " << dMemory << " MB" << endl << endl;
	outfile  << "The amount of total available memory is: " << dMemory << " MB" << endl << endl;
	dMemory *= 1024;
	double dTotal = dMemory;
	int flag = 1;

	if(dMemory !=0)
	{
		char ch = AskOption(flag);
		while(flag)
		{
			switch(ch)
			{	
				case 'A':
				case 'a':	{
							flag =  AskMem(dMemory);
							if(flag)
							{
								ch = AskOption(flag);
							}
							else
							{
								cout << "Quit" << endl;
							}
							break;
							}

				case 'B':
				case 'b':	{
							flag = MemReturn(dMemory, dTotal);
							if(flag)
							{
								AskOption(flag);
							}
							else
							{
								cout << "Quit" << endl;
							}
							break;
							}
				default: 		cout << "Quit" << endl;
			}
		}
	}
	else 
	cout << "Program Terminates" << endl;
	outfile.close();
	system("pause");
	return 0;
}

int AskOption(int& flag)
{
	cout << endl << "Please enter your choice: " << endl;
	cout << "A: Memory Allocation              B: Memory Return                  C: Quit" << endl;
	char ch;
	if((cin >> ch) && ('A' == ch || 'a' == ch || 'B' == ch || 'b' == ch))
	{
		int flag = 1;
		return ch;
	}
	else 
	{
		cout << "Wrong enter, Quit" << endl;
		flag = 0;
		return 0;
	}
}

int AskMem(double& Memo)
{
	//cout << "ask for memory" << endl;
	cout << endl << "How many KBs memory to allocate: ";
	double n = 0;
	cin >> n;
	cout << n << " KB is needed" << endl;
	outfile << endl << n << " KB is needed" << endl;
	if(Memo > n)
	{
		double MemoAllocated = Allocation(n, 1);
		cout << MemoAllocated << " is allocated. " << endl;
		outfile << MemoAllocated << " is allocated. " << endl;
		Memo -= MemoAllocated;
		cout << Memo << " KB is left. " << endl;
		outfile << Memo << " KB is left. " << endl;
		return 1;
	}
	else
	{
		cout << "No enough memory" << endl;
		outfile << "No enough memory" << endl;
		return 0;
	}
}

double Allocation(double n, int times)
{
	double lower = pow(2.0, times++);
	double upper = pow(2.0, times);
	double MemoAllocated = 0;
	if(n > lower && n <= upper)
	{
		MemoAllocated = upper;
	}
	else
	{
		MemoAllocated = Allocation(n, times);
	}
	return MemoAllocated;
}

int MemReturn(double& Memo, double Total)
{
	//cout << "return memory" << endl;
	cout << endl << "How many KBs to return: ";
	double n;
	cin >> n;
	outfile << endl << n << " KB is returning." << endl;
	if((Memo + n) > Total)
	{
		cout << "Memory overflowed." << endl;
		outfile << "Memory overflowed." << endl;
		return 0;
	}
	else
	{
		double MemReturn = Allocation(n, 1);
		cout << MemReturn << " is returned. " << endl;
		outfile << MemReturn << " is returned. " << endl;
		Memo += MemReturn;
		cout << "The available amount memory now is: " << Memo << endl;
		outfile << "The available amount memory now is: " << Memo << endl;
		return 1;
	}
}


