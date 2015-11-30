#include <iostream>
#include "StructureDef.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

int count = 0;

int main()
{	
	//outfile.open("1.txt");
	srand((int)time(0));
///////////////////////////////////////////////////////////////////////////////////////////////////////Beginning of FCFS
	int NumofTermin = 0;
	double TimeCount = 0; 
	double alpha1 = 0.5;
	double alpha2 = 0.3;
	bool flag = 1;
	double RandArr[NumofProcess];
	for(int i = 0; i<NumofProcess; i++)
	{
		RandArr[i] = GetRandom(alpha1)-2*i;
		cout << RandArr[i] << " ";
	}
	cout << endl << endl;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Beginning of SJF
	
	Process::Reset();
	Process SJF[NumofProcess];
	BubbleSort(RandArr, NumofProcess);
	for(int i = 0; i<NumofProcess; i++)
	{
		SetCpuBurst(SJF[i], RandArr[i]);
		//cout << "SJF[" << i+1 << "]'s CPU Burst Time is: " << GetCpuBurst(SJF[i]) << endl;
	}
	NumofTermin = 0;
	TimeCount = 0; 
	count = 0;
	flag = 1;
	while(flag)
	{
		for(int i = 0; i <NumofProcess; i++)
		{
			if(GetCpuBurst(SJF[i]) == 0)
			{
				NumofTermin++;
				if(NumofProcess == NumofTermin)
				{
					flag = 0;
				}
			}
			else
			{
				SJF[i].ArriveReadQueue();
				SJF[i].ArriveCpu(SJF[(i+NumofProcess-1)%NumofProcess]);
				SJF[i].LeaveCpu(TimeCount);
				if(TimeCount >= 100)
				{
					ThroughPut(count, TimeCount, SJF[i]);
				}
				if(GetCpuBurst(SJF[i]) == 0)
				{
					continue;
				}
				else
				{
					SJF[i].ArriveIOQueue();
					SJF[i].ArriveIQ(SJF[(i+NumofProcess-1)%NumofProcess]);
					SJF[i].LeaveIQ();
					CpuUtilize(SJF[i]);
				}
			}
		}
	}
	for(int i = 0; i<NumofProcess; i++)
	{
		ShowWaitTime(SJF[i]);
		ShowTurnaroundTime(SJF[i]);
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//for(int i = 0; i<NumofProcess; i++)
	//{
	//	RandArr[i] = GetRandom(alpha2)-2*i;
	//	cout << RandArr[i] << " ";
	//}
	//cout << endl << endl;

	//Process::Reset();
	//Process SJF2[NumofProcess];
	//BubbleSort(RandArr, NumofProcess);
	//for(int i = 0; i<NumofProcess; i++)
	//{
	//	SetCpuBurst(SJF2[i], RandArr[i]);
		//cout << "SJF[" << i+1 << "]'s CPU Burst Time is: " << GetCpuBurst(SJF[i]) << endl;
	//}
	//NumofTermin = 0;
	//TimeCount = 0; 
	//count = 0;
	//flag = 1;
	//while(flag)
	//{
	//	for(int i = 0; i <NumofProcess; i++)
	//	{
	//		if(GetCpuBurst(SJF2[i]) == 0)
	//		{
	//			NumofTermin++;
	//			if(NumofProcess == NumofTermin)
	//			{
	//				flag = 0;
	//			}
	//		}
	//		else
	//		{
	//			SJF2[i].ArriveReadQueue();
	//			SJF2[i].ArriveCpu(SJF2[(i+NumofProcess-1)%NumofProcess]);
	//			SJF2[i].LeaveCpu(TimeCount);
	//			if(TimeCount >= 100)
	//			{
	//				ThroughPut(count, TimeCount);
	//			}
	//			if(GetCpuBurst(SJF2[i]) == 0)
	//			{
	//				continue;
	//			}
	//			else
	//			{
	//				SJF2[i].ArriveIOQueue();
	//				SJF2[i].ArriveIQ(SJF2[(i+NumofProcess-1)%NumofProcess]);
	//				SJF2[i].LeaveIQ();
	//				CpuUtilize(SJF2[i]);
	//			}
	//		}
	//	}
	//}
	//for(int i = 0; i<NumofProcess; i++)
	//{
	//	ShowWaitTime(SJF2[i]);
	//	ShowTurnaroundTime(SJF2[i]);
	//}

	//cout << "IOProcessing: " << IOProcessing << endl;
	//outfile.close();
	system("pause");
	return 0;
}