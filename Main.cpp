#include<iostream>
#include<string>
#include <cstdio>
#include <time.h>
#include"MDP.h"

using namespace std;

vector<double> Utility;
vector<double> Utility1;
vector<int> Policy;
int iteration = 0;


void ValueIteration_MDP();
void PolicyIteration_MDP();		
double Max_Utility(int State);
string GetActionName(int a);

vector<double> Utility_for_policyItr();
vector<double> GetCoefficients(int State);
int Max_arg_Utility(int State);


int main()
{
	char ch;
	int choice;
	clock_t clkStart;
	clock_t clkFinish;
	clock_t clkdiff;
	do
	{		
		Utility.assign(Total_state, 0);
		Policy.assign(Total_state, 0);
		iteration = 0;
		cout << "1. Value Iteration"<<endl;
		cout << "2. Policy Iteration"<<endl;
		cout << "Option:";
		cin >> choice;
		
		switch (choice)
		{
		case 1:
			clkStart = clock();
			ValueIteration_MDP();
			clkFinish = clock();
			break;
		case 2:
			clkStart = clock();
			PolicyIteration_MDP();
			clkFinish = clock();
			break;
		default:
			cout << "Invalid!";
			break;
		}
		clkdiff=clkFinish - clkStart;
		cout <<endl<<"Total execution time: " << clkdiff <<"sec"<< endl;
		cout << endl<<"Continue(y/n)? : ";
		ch = getchar();
		ch = getchar();
	} while (ch == 'Y' || ch == 'y');
	
	return 0;
}



void ValueIteration_MDP()
{

	cout << "=============================Value Iteration Results======================\n";

	double Delta;
	Utility1.assign(Total_state, 0);	
	int Obser_state = 3;

	do
	{
		Delta = 0.0f;
		for (int i = 0; i < Total_state; i++)
		{

			double New = Max_Utility(i);

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
			if(i== Obser_state)
				cout << "Policy[" << i << "]=" << "0" << endl;
			else
				cout << "Policy[" << i << "]=" << GetActionName(Policy[i]) << endl;

	} while (Delta>=Epsilon);		

	
}

void PolicyIteration_MDP()			
{
	cout << "========================Policy Iteration Results=======================\n";

	iteration = 1;

	bool Unchange_flag;
	int Obser_state = 3;
	
	Policy.assign(Total_state, 0);

	do
	{

		Utility = Utility_for_policyItr();
		Unchange_flag = true;

		for (int i = 0; i < Total_state; i++)
		{

			int a = Max_arg_Utility(i);
			if (Policy[i] != a)
			{
				Policy[i] = a;
				Unchange_flag = false;
			}

		}

		cout << "After iteration " << iteration << endl;

		cout << "----------------Utilities of states---------------" << endl;
		for (int i = 0; i < Total_state; i++)
			cout << "Utility[" << i << "]=" << Utility[i] << endl;

		cout << endl;
		cout << "----------------Policies of states---------------" << endl;
		for (int i = 0; i < Total_state; i++)
			if (i == Obser_state)
				cout << "Policy[" << i << "]=" << "0" << endl;
			else
				cout << "Policy[" << i << "]=" << GetActionName(Policy[i]) << endl;
		iteration++;

	} while (!Unchange_flag);
	
}


double Max_Utility(int State)		
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


vector<double> Utility_for_policyItr()
{
	vector<vector<double>> C_all_utility;		//Contains all the Cofficients of all Utility

	for (int i =0; i < Total_state; i++)	
		C_all_utility.push_back(GetCoefficients(i));	

	return Utility;
}


vector<double> GetCoefficients(int State)
{
	vector<double> myCofficient;

	double Reward = 0.0f;

	for (int k = 0; k < Total_state; k++) //count+1 since we have a new column of rewards
	{

		if (k == State)
			myCofficient.push_back(1 - (Gamma * MDP::Ptr()->TransitionProb[State][Policy[State]][k]));
		else
			myCofficient.push_back(-(Gamma * MDP::Ptr()->TransitionProb[State][Policy[State]][k]));

	}

	for (int k = 0; k < Total_state; k++)
	{
		Reward += MDP::Ptr()->TransitionProb[State][Policy[State]][k] * MDP::Ptr()->RewardValue[State][Policy[State]][k];
	}

	myCofficient.push_back(Reward);

	return myCofficient;
}

string GetActionName(int a)				//it's return the action name int to string, it's help to display output
{
	string Action = "";
	switch (a)
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

int Max_arg_Utility(int State)
{
	int MaxAction = Policy[State];
	double result, Reward, E_utility;
	double MaxUtility = Utility[State];
	int i = State;//current state

	for (int j =0; j < Total_action; j++)//action
	{
		
		Reward = 0.0f;
		E_utility = 0.0f;

		for (int k = 0; k < Total_state; k++)
		{
			Reward += MDP::Ptr()->TransitionProb[i][j][k] * MDP::Ptr()->RewardValue[i][j][k];	//i-State;j-Action
			E_utility += MDP::Ptr()->TransitionProb[i][j][k] * Utility[k];
		}

		result = Reward + Gamma * E_utility;

		if (result > MaxUtility)
		{
			Utility[i] = result;
			MaxUtility = result;
			MaxAction = j;
		}
	}
	return MaxAction;
}

