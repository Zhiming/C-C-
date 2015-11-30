#include<iostream>
#include <stdlib.h>
#include <list>
#include <time.h>
#include <fstream>
#include <vector>

using namespace std;

const int NumofPeople = 2800;   // The number of people waiting for boarding in each stop
const int NumofStops = 16;    // The number of stops
const int NumofBuses = 5;   // The number of buses
const double StopTime = 28800;  // The total number of stimulating time
const int DriveTime = 300;  // The time for driving between each two stops
const int BoardRate = 10;  // The boarding time for each person

struct BusUnit
{
	double dArriveTime;
	double dLeaveTime;
	int iPassStop;
	double dSpendTime;
	int iStop; // Which stop the bus is
	int iOrigin; // The original of a bus
	vector<int> NumofBoard;
	vector<double> TimeofArrival;
	vector<double>TimeofLeave;
	
	void Arrival(int iPassStop)
	{
		//this->dArriveTime = dLeaveTime + iPassStop * DriveTime + DriveTime;
		this->dArriveTime = dLeaveTime + DriveTime;
		this->iPassStop = 0;
	}

	void RecArrival(double ArriveTime)
	{
		TimeofArrival.push_back(ArriveTime);
	}

	void SpendTime(int iNumofBoard)
	{
		this->dSpendTime = (iNumofBoard * BoardRate)+iPassStop * DriveTime + DriveTime;
	}

	void Leave(int iNumofBoard)
	{
		this->dLeaveTime = dArriveTime + iNumofBoard * BoardRate;
	}

	void RecLeave(double LeaveTime)
	{
		TimeofLeave.push_back(LeaveTime);
	}

	void UpdateStop()
	{
		this->iStop = (this->iStop+1)%NumofStops;
	}

	void Board(int Count)
	{
		NumofBoard.push_back(Count);
	}
	
	void ShowInfo()
	{
		cout << "The arriving time of the bus is: " << dArriveTime << endl;
		cout << "Now the bus is at NO." << this->iStop+1 << " stop" << endl;
		cout << "The leaving time of the bus is: " << dLeaveTime << endl;
		cout << "The number of stops passed by the bus are: " << iPassStop << endl;
		cout << "The original stop for the bus is: " << iOrigin << endl;
		cout << "The spending time of the bus is: " << dSpendTime<< endl;
	}
};


int main()
{
	srand((int)time(0));
	ofstream outFile;
	outFile.open("The information of the bus stimulation.txt");
	cout << "************** The bus stimulation begins **************" << endl;
	outFile << "************** The bus stimulation begins **************" << endl;
	cout << endl << "###### Introduction ######" << endl;
	cout << "The duration time is: " << StopTime << endl;
	cout << "The total number of stops are: " << NumofStops << endl;
	cout << "The total number of buses are: " << NumofBuses << endl;
	cout << "The driving time between two stops is: " << DriveTime << endl;
	cout << "The boarding rate is: " << BoardRate << endl << endl;
	
	outFile << endl << "###### Introduction ######" << endl;
	outFile << "The duration time is: " << StopTime << endl;
	outFile << "The total number of stops are: " << NumofStops << endl;
	outFile << "The total number of buses are: " << NumofBuses << endl;
	outFile << "The driving time between two stops is: " << DriveTime << endl;
	outFile << "The boarding rate is: " << BoardRate << endl << endl;
	
////////////////////////////////////////////////////////////////////
//Initialize five buses
int factor = 0;
BusUnit Bus[NumofBuses];
for(int i= 0; i<NumofBuses; i++)
{
	{
		Bus[i].dArriveTime = 0.0;
		Bus[i].dLeaveTime = 0.0;
		Bus[i].iPassStop = 0;
		Bus[i].dSpendTime = 0.0;
		Bus[i].iStop = (3*i)%NumofStops;
		Bus[i].iOrigin = Bus[i].iStop;
	};
	//Bus[i].ShowInfo();
	//cout << endl;
}

////////////////////////////////////////////////////////////////////
	
////////////////////////////////////////////////////////////////////
//Initialize people in each stop in 8 hours and sort them in a list
	int iSum = 0; //The sum of the random numbers
	list<int> BusStop[NumofStops];
	list <int> ::iterator iElementLocator;
	for(int i = 0; i<NumofStops; i++)
	{
		iSum = 0;
		for(int j = 0;j<NumofPeople;j++)
	{
		BusStop[i].push_back (iSum);
		iSum+= rand()%15;
	}
	}	
////////////////////////////////////////////////////////////////////
//Print out all the people in each stop in 8 hours
	
	//for(int i =0; i<NumofStops; i++)
	//{
	//	//cout <<"第" << i+1 << "行元素: " << endl;
	//	cout << "The total number of people waiting for a bus: ";
	//	outFile << "The total number of people waiting for a bus: ";
	//	for (iElementLocator = BusStop[i].begin ()
 //       ;iElementLocator != BusStop[i].end ()
 //       ; ++ iElementLocator )
	//	{
	//		cout << *iElementLocator << " ";
	//		outFile << *iElementLocator << " ";
	//	} 
	//	cout << endl;
	//	outFile << endl;
	//}
	//cout << endl;
	//outFile << endl;

	//for (int i =0; i<NumofStops; i++ )
	//{
	//	if(BusStop[i].empty())
	//		cout << "No people" << endl;
	//	else
	//		cout << "There are people." << endl;
	//}
/////////////////////////////////////////////////////////////////////
//Boarding bus
   int iCount = 0; //Count how many people have boarded
	int iMax = 0; // The maximum number of waiting people for each sub-round
	int iTotal = 0; // The average number of people who boarded for each round
	int iMin = 9999; // The minimum number of waitiing people for each sub-round
	vector<int> MAX; // The maximum number of waiting people for each round
	vector<int> MIN; //  The minimum number of waitiing people for each round
	int iRound = 1; // Record which round is going on
	int iSubRound = 1; // Record which bus is going
	double dClock = 0.0; // The spending time for each round
	double dSubClock = 0.0; // The spending time for each bus
	int iAverage = 0; // The average number of people waiting for the bus at each stop
	vector<int> AVERAGE; // The average number of waiting people for each round
	
	int j = 0;
	cout << "--------All buses set off!--------"<< endl << endl;
	outFile << "--------All buses set off!--------"<< endl << endl;

	while(dClock < StopTime)
	{
		if(1 == iSubRound%NumofBuses)
		{
			cout << "---Round " << iRound << " begins---" << endl << endl;
			outFile << "---Round " << iRound << " begins---" << endl << endl;
		}
			
		j = j%NumofBuses;
		Bus[j].Arrival(Bus[j].iPassStop);
		Bus[j].RecArrival(Bus[j].dArriveTime);
		cout << "The NO." << j+1 << " bus is coming to NO."
		        <<Bus[j].iStop+1 <<" stop at " << Bus[j].dArriveTime << endl;
		outFile << "The NO." << j+1 << " bus is coming to NO."
		        <<Bus[j].iStop+1 <<" stop at " << Bus[j].dArriveTime << endl;
		iCount = 0;
		
		if(BusStop[Bus[j].iStop].empty())
		{
			cout << "There is no people waiting at NO." << Bus[j].iStop+1 << " stop, NO." 
				     << j+1 << " bus is passing it" << endl;
			outFile << "There is no people waiting at NO." << Bus[j].iStop+1 << " stop, NO." 
				     << j+1 << " bus is passing it" << endl;
			Bus[j].Leave(iCount);
			Bus[j].RecLeave(Bus[j].dLeaveTime);
			Bus[j].SpendTime(iCount);
			cout << "****The NO." << j+1 <<" bus leaves at " << Bus[j].dLeaveTime <<"****" << endl;
			outFile << "****The NO." << j+1 <<" bus leaves at " << Bus[j].dLeaveTime <<"****" << endl;
			Bus[j].UpdateStop();
		}
		else
		{
			iElementLocator = BusStop[Bus[j].iStop].begin ();
			//cout <<"第" << i+1 << "行被删除的元素： " ;
			if((*iElementLocator) <= Bus[j].dArriveTime)
			{
				while(iElementLocator != BusStop[Bus[j].iStop].end ()
				      && ((*iElementLocator) <= Bus[j].dArriveTime))
						{
							//cout << *iElementLocator << " ";
							//outFile << *iElementLocator << " ";
							iElementLocator = BusStop[Bus[j].iStop].erase(iElementLocator);
							iCount++;
						}
				//cout << endl;
				//outFile << endl;
			}
			else
						{
							Bus[j].iPassStop++;
							//cout << "No elements are deleted." << endl;
						}
			
			
			Bus[j].SpendTime(iCount);
			Bus[j].Leave(iCount);
			Bus[j].RecLeave(Bus[j].dLeaveTime);
			Bus[j].UpdateStop();
			
			if(iCount > 0)
			{
				cout << "There are " << iCount << " people boarded."<< endl;
				outFile << "There are " << iCount << " people boarded."<< endl;
			}
			else
			{
				cout << "There is no people waiting at NO. " << Bus[j].iStop << " stop, NO." 
				        << j+1 << " bus is passing it" << endl;
				outFile << "There is no people waiting at NO. " << Bus[j].iStop << " stop, NO." 
				        << j+1 << " bus is passing it" << endl;
			}
				cout << "The NO." << j+1 <<" bus leaves at " << Bus[j].dLeaveTime << endl;
				outFile << "The NO." << j+1 <<" bus leaves at " << Bus[j].dLeaveTime << endl;
			
		}

		Bus[j].Board(iCount);
		
		if(dSubClock < Bus[j].dSpendTime)
			dSubClock = Bus[j].dSpendTime;
		
		if(iMax < iCount)
			iMax = iCount;

		if(iMin > iCount)
			iMin = iCount;

		iTotal += iCount;
		//cout << "iTotal is: " << iTotal << endl;

		if(0 == iSubRound%NumofBuses)
		{	
			cout << endl;
			outFile << endl;
			iAverage = iTotal/NumofStops;
			cout << "The average size of a waiting queue at each stop in this round is: " << iAverage
				     << endl;
			outFile << "The average size of a waiting queue at each stop in this round is: " << iAverage
				     << endl;
			cout << "The maximium size of a waiting queue at each stop in this round is: " << iMax
				     << endl;
			outFile << "The maximium size of a waiting queue at each stop in this round is: " << iMax
				     << endl;
			cout << "The minimium size of a waiting queue at each stop in this round is: " << iMin
				     << endl;
			outFile << "The minimium size of a waiting queue at each stop in this round is: " << iMin
				     << endl;
			MAX.push_back(iMax);
			MIN.push_back(iMin);
			AVERAGE.push_back(iAverage);

			iTotal = 0;
			cout << endl << "---Round" << iRound << " finishes---" << endl << endl;
			outFile << endl << "---Round" << iRound << " finishes---" << endl << endl;
			iRound++;
			dClock += dSubClock;
			//cout << "The spending time is: " << dClock << endl;
			dSubClock = 0;
			iMax = 0;
			iMin = 9999; //If it is 0 or any other small number, if the the smallest in each sub-round is bigger
			                     // than this value, then iMin won't change, which result in a mistake
		}
			j++;
			iSubRound++;
			cout << endl;
			outFile << endl;
		}

	cout << "************** Time is up, the stimulation stops **************" << endl << endl;
	outFile << "************** Time is up, the stimulation stops **************" << endl << endl;
	
////////////////////////////////////////////////////////////////////
//General information abou this stimulation
cout <<endl << "************** General Information **************" << endl << endl;
outFile <<endl << "************** General Information **************" << endl << endl;
vector <int> ::iterator iELocator;
vector <double> ::iterator dELocator;
cout << "The maximium people at each stop in each round is:  " << endl;
outFile << "The maximium people at each stop in each round is:  " << endl;
for (iELocator = MAX.begin ()
        ;iELocator != MAX.end ()
        ; ++ iELocator )
{
	cout << *iELocator << " ";
	outFile << *iELocator << " ";
}

cout << endl << endl <<"The minimium people at each stop in each round is:  " << endl;
outFile << endl << endl <<"The minimium people at each stop in each round is:  " << endl;
for (iELocator = MIN.begin ()
        ;iELocator != MIN.end ()
        ; ++ iELocator )
{
	cout << *iELocator << " ";
	outFile << *iELocator << " ";
}

cout << endl << endl <<"The average people at each stop in each round is:  " << endl;
outFile << endl << endl <<"The average people at each stop in each round is:  " << endl;
for (iELocator = AVERAGE.begin ()
        ;iELocator != AVERAGE.end ()
        ; ++ iELocator )
{
	cout << *iELocator << " ";
	outFile << *iELocator << " ";
}

cout << endl;
outFile << endl;

for(int i = 0; i<NumofBuses; i++)
{
	cout << endl << "The number of people boarded on NO." << i+1 << " bus in each round is: " << endl;
	outFile << endl << "The number of people boarded on NO." << i+1 << " bus in each round is: " << endl;
	for (iELocator = Bus[i].NumofBoard.begin (); iELocator != Bus[i].NumofBoard.end (); ++ iELocator)
	{
		cout << *iELocator << " ";
		outFile << *iELocator << " ";
	}
	cout << endl;
	outFile << endl;
}

cout << endl;
outFile << endl;


for(int i = 0; i<NumofBuses; i++)
{
	cout << endl << "Starts from NO." << Bus[i].iOrigin+1 << " stop, NO. " << i+1 <<" bus" 
		     << " arrived at each stop at: " << endl;
	outFile << endl << "Starts from NO." << Bus[i].iOrigin+1 << " stop, NO. " << i+1 <<" bus" 
		     << " arrived at each stop at: " << endl;
	for (dELocator = Bus[i].TimeofArrival.begin(); dELocator != Bus[i].TimeofArrival.end (); ++ dELocator)
	{
		cout << *dELocator << " ";
		outFile << *dELocator << " ";
	}

	cout << endl << endl << "Left from NO." << Bus[i].iOrigin+1 << " stop, NO. " << i+1 <<" bus" 
		     << " left each stop at: "<< endl;
	outFile << endl << endl << "Left from NO." << Bus[i].iOrigin+1 << " stop, NO. " << i+1 <<" bus" 
		     << " left each stop at: "<< endl;
	for (dELocator = Bus[i].TimeofLeave.begin (); dELocator != Bus[i].TimeofLeave.end (); ++ dELocator)
	{
		cout << *dELocator << " ";
		outFile << *dELocator << " ";
	}
	cout << endl << endl << endl;
	outFile << endl << endl << endl;
}

////////////////////////////////////////////////////////////////////
	cout << endl;
	outFile << endl;
////////////////////////////////////////////////////////////////////
//The people waiting in each stop
	//for(int i = 0; i<NumofStops; i++)
	//{
	//	//cout <<"第" << i+1 << "行剩下的元素: ";
	//	cout << "The number of people who still waiting for a bus: ";
	//	outFile << "The number of people who still waiting for a bus: ";
	//	for ( iElementLocator = BusStop[i].begin ()
 //       ; iElementLocator != BusStop[i].end ()
 //       ; ++ iElementLocator )
	//	{
	//		cout << *iElementLocator << " ";
	//		outFile << *iElementLocator << " ";
	//	}
	//	cout << endl;
	//	outFile << endl;
	//}
///////////////////////////////////////////////////////////////////

	cout << endl;
	outFile.close();
	system("pause");
	return 0;
}