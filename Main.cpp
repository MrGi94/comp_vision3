#include<iostream>
#include<string>
#include<conio.h>
#include"MDP.h"

using namespace std;

vector<double> Utility;
vector<double> Utility1;
vector<int> Policy;
int iteration = 0;


void ValueIteration_MDP();
//void PolicyIteration_MDP();			// you have to code for that
double GetMaxUtility(int State);
string GetActionName(int j);


int main()
{
	char ch;
	int choice;

	do
	{
		
		Utility.assign(Total_state, 0);
		Policy.assign(Total_state, 0);
		
		cout << endl;
		cout << "1. Value Iteration"<<endl;
		cout << "2. Policy Iteration"<<endl;
		cout << "Option:";
		cin >> choice;
		
		switch (choice)
		{
		case 1:
			ValueIteration_MDP();
			break;
		case 2:
			//PolicyIteration_MDP();
			break;
		default:
			cout << "Invalid!";
			break;
		}
		cout << endl<<"Continue(y/n):";
		ch = _getch();
	} while (ch == 'Y' || ch == 'y');

	return 0;
}



void ValueIteration_MDP()
{

	cout << "*************************Value Iteration Results*******************\n";

	double Delta;
	Utility1.assign(Total_state, 0);	

	do
	{
		Delta = 0.0f;
		for (int i = 0; i < Total_state; i++)
		{

			double New = GetMaxUtility(i);

			if (abs(New - Utility[i]) > Delta)
				Delta = abs(New - Utility[i]);
			Utility1[i] = New;

		}
		
		Utility = Utility1;
		iteration++;

		cout << endl << "Iteration: " << iteration << endl;

		cout << "----------------Utilities of states---------------" << endl;
		for (int i = 0; i < Total_state; i++)
			cout << "Utility[" << i << "]=" << Utility[i] << endl;

		cout << endl;
		cout << "----------------Policies of states---------------" << endl;
		for (int i = 0; i < Total_state; i++)
			cout << "Policy[" << i << "]=" << GetActionName(Policy[i]) << endl;

	} while (Delta>=Epsilon);		

	
}
/*
void PolicyIteration_MDP()			//I try to design it, if not correct change it
{
	cout << "*************************Policy Iteration Results*******************\n";

	iteration = 1;

	bool bUnchanged;
	
	Policy.assign(Total_state, 0);

	do
	{

		Utility = GetUtilitySolvingBellman();

		bUnchanged = true;

		for (int i = 0; i < Total_state; i++)
		{

			int a = GetActionGivingMaxUtility(i);
			if (Policy[i] != a)
			{
				Policy[i] = a;
				bUnchanged = false;
			}

		}

		cout << "After iteration " << iteration << endl;

		cout << "----------------Utilities of states---------------" << endl;
		for (int i = 0; i < Total_state; i++)
			cout << "Utility[" << i << "]=" << Utility[i] << endl;

		cout << endl;
		cout << "----------------Policies of states---------------" << endl;
		for (int i = 0; i < Total_state; i++)
			cout << "Policy[" << i << "]=" << GetActionName(Policy[i]) << endl;
		iteration++;

	} while (!bUnchanged);
	
}
*/

double GetMaxUtility(int State)			//it's return the max Utility of each State
{

	double MaxUtility = Utility[State];
	double Reward, E_utility;
	int s = State;//current state
	
	for (int a = 0; a < Total_action; a++)				//action
	{
		
		double result;
		
		Reward = 0.0f;
		E_utility = 0.0f;
		for (int k = 0; k < Total_state; k++)
		{
			Reward += MDP::Ptr()->TransitionProb[s][a][k] * MDP::Ptr()->RewardValue[s][a][k];	//s-State;a-Action
			E_utility += MDP::Ptr()->TransitionProb[s][a][k] * Utility[k];
		}
		
		result = Reward + Gamma * E_utility;		//Bellman's equation
		if (result > MaxUtility)
		{
			MaxUtility = result;
			Policy[s] = a;
		}
	}
	return MaxUtility;
}

string GetActionName(int j)				//it's return the action name int to string, it's help to display output
{
	string Action = "";
	switch (j)
	{
		case 0:
			Action = "a1";
			break;
		case 1:
			Action = "b1";
			break;		
		case 2:
			Action = "a2";
			break;
		case 3:
			Action = "b2";
			break;
		case 4:
			Action = "a3";
			break;
		case 5:
			Action = "b3";
			break;
	}
	return Action;
}

