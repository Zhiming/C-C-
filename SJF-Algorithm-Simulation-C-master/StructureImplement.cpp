#include "StructureDef.h"
#include <iostream>

using namespace std;

char Process::i = 'a';
double Process::MAX = 0;
double Process::dTotalTime = 0;

_ForOut::_ForOut(){
	outfile.open("1.txt");
}

_ForOut::~_ForOut(){
	outfile.close();
}

void _ForOut::Write(const char* ch){
	this->outfile << ch;
}

void _ForOut::Write(const double& a){
	this->outfile << a;
}

_ForOut Process::output;

void Process::Reset()
{
	Process::i = 'a';
	Process::dTotalTime = 0;
}

Process::Process()
{
		cName = i;
		i++;
		dArrRedyQueue = 0;
		dArrCpu = 0;
		dUseCpu = 0;
		dLeavCpu = 0;
		dArrIOQueue = 0;
		dArrIO = 0;
		dLeavIO = 0;
		dCpuBurst = 0;
		dTotalWaitTime = 0;
}

void Process::ArriveReadQueue()
{
	this->dArrRedyQueue = this->dLeavIO;
}

void Process::ArriveCpu(const Process& b)
{
	if(this->dArrRedyQueue < b.dLeavCpu)
		this->dArrCpu = b.dLeavCpu;
	else
		this->dArrCpu = this->dArrRedyQueue;
	this->Wait();
}

void Process::Wait()
{
	dTotalWaitTime += (this->dArrCpu - this->dArrRedyQueue);
}

void Process::LeaveCpu(double& a)
{
	if(CpuProcessing < this->dCpuBurst)
	{
		this->dLeavCpu = this->dArrCpu + CpuProcessing;
		this->dCpuBurst -= CpuProcessing;
		this->dUseCpu = CpuProcessing;
		//cout << this->cName << " is setting Time Count: " << endl;
		this->SetTimeCount(a);
	}
	else
	{
		this->dLeavCpu = this->dArrCpu + this->dCpuBurst;
		this->dUseCpu = this->dCpuBurst;
		this->dCpuBurst = 0;
		count++;
		cout << endl << "Process " << this->cName << " terminates. " << endl;
		char pt_name[2] = {this->cName, '\0'};
		output.Write("Process ");
		output.Write(pt_name);
		output.Write(" terminates\n");
		//cout << "Process " << this->cName << "'s turnaround time is: " << this->dLeavCpu << endl;
		//cout << this->cName << " is setting Time Count: " << endl;
		this->SetTimeCount(a);
	}
}

void Process::SetTimeCount(double& TimeCount)
{
	if(0 == dTotalTime)
	{
		dTotalTime = this->dLeavCpu;
		TimeCount = dTotalTime;
		//cout << "TimeCount = dTotalTime: " << TimeCount << endl;
	}
	else
	{
		TimeCount += this->dLeavCpu - dTotalTime;
		dTotalTime = this->dLeavCpu;
		//cout << "this->dLeavCpu: " << this->dLeavCpu << endl;
		//cout << "dTotalTime: " << dTotalTime << endl;
		//cout << "TimeCount += this->dLeavCpu - dTotalTime: " << TimeCount << endl;
	}
}

void Process::ArriveIOQueue()
{
	this->dArrIOQueue = this->dLeavCpu;
}

double Process::GetLeaveCpu()const
{
	return this->dArrIO;
}

void Process::ArriveIQ(const Process& b)
{
	if(b.GetLeaveCpu() == 0)
	{
		this->dArrIO = this->dArrIOQueue;
		MAX = this->dArrIO;
	}
	else if(MAX<b.dLeavIO)
	{
		this->dArrIO = b.dLeavIO;
		MAX = b.dLeavIO;
	}
	else
	{
		this->dArrIO = MAX;
	}
}

void Process::LeaveIQ()
{
	this->dLeavIO = this->dArrIO + IOProcessing;
	MAX = this->dLeavIO;
}

void CpuUtilize(Process& a)
{
	if(a.dLeavIO > a.dArrRedyQueue)
	{
		a.dCpuUtilize = a.dUseCpu/ (a.dLeavIO - a.dArrRedyQueue);
	}
	else
	{
		a.dCpuUtilize = a.dUseCpu / (a.dLeavCpu - a.dArrRedyQueue);
	}
	//cout << endl << "Process " << a.cName << "'s Leaving IO time is: " << a.dLeavIO << endl;
	//cout << "Process " << a.cName << "'s Arriving Ready Queue tiime is: " << a.dArrRedyQueue << endl;
	//cout << "Process " << a.cName << "'s Arriving CPU Time is: " << a.dArrCpu << endl;
	//cout << "Process " << a.cName << "'s Leaving CPU Time is: " << a.dLeavCpu << endl;
	//cout << "Process " << a.cName << "'s Arriving IO Ready Queue Time is: " << a.dArrIOQueue << endl;
	cout << "Process " << a.cName << "'s CPU utilization rate is: " << a.dCpuUtilize << endl;
	a.output.Write("Process ");
	char pt_name[2] = {a.cName, '\0'};
	a.output.Write(pt_name);
	a.output.Write(" \'s CPU utilization rate is: ");
	a.output.Write(a.dCpuUtilize);
	a.output.Write("\n");
}

void ThroughPut(int& count, double& TimeCount, const Process& a)
{
	cout << endl << "The throughput within this 1 second is: " << count << endl;
	a.output.Write("The throughput with this 1 second is:  ");
	a.output.Write(count);
	a.output.Write("\n");
	//outfile << "The throughput within this 1 second is: " << count << endl;
	//cout << "The TimeCount is: " << TimeCount << endl;
	count = 0;
	TimeCount = TimeCount - 100;
	//cout << "TimeCount = TimeCount - 100: " << TimeCount << endl;
}

void SetCpuBurst(Process& a, double CpuBurst)
{
	a.dCpuBurst = CpuBurst;
}

double GetCpuBurst(const Process& a)
{
	return a.dCpuBurst;
}

void ShowWaitTime(const Process& a)
{
	cout << endl << "Process " << a.cName << "'s total waiting time is: " << a.dTotalWaitTime << endl;
	//outfile << endl << "Process " << a.cName << "'s total waiting time is: " << a.dTotalWaitTime << endl;
	a.output.Write("Process ");
	char pt_name[2] = {a.cName, '\0'};
	a.output.Write(pt_name);
	a.output.Write(" \'s total waiting time is: ");
	a.output.Write(a.dTotalWaitTime);
	a.output.Write("\n");
}

void ShowTurnaroundTime(const Process& a)
{
	cout << endl << "Process " << a.cName << "'s total turnaround time is: " << a.dLeavCpu << endl;
	//outfile << "Process " << a.cName << "'s total turnaround time is: " << a.dLeavCpu << endl;
	a.output.Write("Process ");
	char pt_name[2] = {a.cName, '\0'};
	a.output.Write(pt_name);
	a.output.Write(" \'s total turnaround time is: ");
	a.output.Write(a.dLeavCpu);
	a.output.Write("\n");
}

double GetRandom(const double &alpha)
{
	return (60000 + rand()%200 + 30*alpha);
	//return 120;
}

void BubbleSort(double arr[], double n)
{
      bool swapped = true;
      double j = 0;
      double tmp;
      while (swapped) 
	  {
            swapped = false;
            j++;
            for (int i = 0; i < n - j; i++) 
				{
                  if (arr[i] > arr[i + 1]) 
					{
                        tmp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = tmp;
                        swapped = true;
                  }
            }
      }
}
