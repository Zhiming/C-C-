#ifndef STRUCTUREDEF_H_
#define STRUCTUREDEF_H_

#include <fstream>

using namespace std;

const int CpuProcessing = 60;
const int IOProcessing = 60;
const int NumofProcess = 10;

extern int count;

class _ForOut{
private:

public:
	ofstream outfile;
	_ForOut();
	~_ForOut();
	void Write(const char* ch);
	void Write(const double&);
};

class Process
{
private:
	char cName; // name of each process
	double dArrRedyQueue; // the time that the process arrives at the ready queue
	double dArrCpu; // the time that the process arrives at CPU
	double dLeavCpu; //the time that the process arrives at CPU
	double dArrIOQueue; //the time that the process arrives at I/O ready queue
	double dArrIO; //the time that the process arrives at a I/O equipment
	double dLeavIO; //the time that the process arrives at a I/O equipment
	double dCpuBurst; //the time each process processed by CPU each time
	double dUseCpu;  //the total time each process processed by CPU
	double dCpuUtilize; // the utilizing rate each process processed by CPU
	double dTotalWaitTime; // the total waiting time of each process
	static char i;
	static double MAX;
	static double dTotalTime; //the turnaround time
	static _ForOut output;
	void Wait();
	void SetTimeCount(double&);

public:
	Process();
	~Process(){}
	void ArriveReadQueue();
	void ArriveCpu( const Process& b);
	void LeaveCpu(double&);
	void ArriveIOQueue();
	void ArriveIQ(const Process& b);
	void LeaveIQ();
	double GetLeaveCpu()const;
	static void Reset();
	friend void CpuUtilize(Process& a);
	friend void SetCpuBurst(Process&, double);
	friend double GetCpuBurst(const Process& );
	friend void ShowTurnaroundTime(const Process&);
	friend void ShowWaitTime(const Process&);
	friend void ThroughPut(int&, double&, const Process&);
};



double GetRandom(const double&);

void BubbleSort(double arr[], double n);

#endif