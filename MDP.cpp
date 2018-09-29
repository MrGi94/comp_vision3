#include<cmath>
#include "MDP.h"

using namespace std;


MDP::MDP()
{
	TransitionProb = TransitionFunction();
	RewardValue = RewardFunction();
}
MDP::~MDP()
{
	delete(NewObject);
}

MDP* MDP::Ptr()
{
	if (NewObject == nullptr)
		NewObject = new MDP();
	return NewObject;
}

MDP* MDP::NewObject = nullptr;

vector<vector<vector<float>>> MDP::TransitionFunction()		 //it's return the transition probability
{
	vector<vector<vector<float>>> Probability;

	for (size_t i = 0; i < Total_state; i++)
	{
		vector<vector<float>> InnerVector;
		for (size_t j = 0; j < Total_action; j++)
		{
			vector<float> Vector;
			for (size_t k = 0; k < Total_state; k++)
			{
				Vector.push_back(GetProbability(i, j, k));
			}
			InnerVector.push_back(Vector);
		}
		Probability.push_back(InnerVector);
	}

	return Probability;
}

float  MDP::GetProbability(int Pre_State, int Action, int NextState)		//Input for transition probability
{
	float Prob = 0.0f;
	switch (Pre_State)
	{
	case (int)State::s0:
		if ((Action == (int)Action::b2) && (NextState == (int)State::s1))
			Prob = 0.9f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s1))
			Prob = 0.1f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s4))
			Prob = 0.9f;

		else if ((Action == (int)Action::b2) && (NextState == (int)State::s4))
				Prob = 0.1f;		
		break;

	case (int)State::s5:
			if ((Action == (int)Action::a3) && (NextState == (int)State::s2))
			Prob = 0.9f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s2))
			Prob = 0.1f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s1))
			Prob = 0.9f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s1))
			Prob = 0.1f;
		break;

	case (int)State::s10:
		if ((Action == (int)Action::a2) && (NextState == (int)State::s9))
			Prob = 0.9f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s9))
			Prob = 0.1f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s4))
			Prob = 0.9f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s4))
			Prob = 0.1f;
		break;

	case (int)State::s8:
		if ((Action == (int)Action::b1) && (NextState == (int)State::s7))
			Prob = 0.9f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s7))
			Prob = 0.1f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s9))
			Prob = 0.9f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s9))
			Prob = 0.1f;
		break;

	case (int)State::s11:
		if ((Action == (int)Action::a3) && (NextState == (int)State::s6))
			Prob = 0.9f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s6))
			Prob = 0.1f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s7))
			Prob = 0.9f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s7))
			Prob = 0.1f;
		break;

	case (int)State::s1:
		if ((Action == (int)Action::b3) && (NextState == (int)State::s4))
			Prob = 0.9f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s4))
			Prob = 0.1f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s5))
			Prob = 0.9f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s5))
			Prob = 0.1f;
		else if ((Action == (int)Action::a3) && (NextState == (int)State::s2))
			Prob = 0.9f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s2))
			Prob = 0.1f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s0))
			Prob = 0.9f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s0))
			Prob = 0.1f;
		break;

	case (int)State::s4:
		if ((Action == (int)Action::b2) && (NextState == (int)State::s1))
			Prob = 0.9f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s0))
			Prob = 0.9f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s9))
			Prob = 0.9f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s1))
			Prob = 0.1f;
		else if ((Action == (int)Action::b2) && (NextState == (int)State::s0))
			Prob = 0.1f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s9))
			Prob = 0.1f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s10))
			Prob = 0.9f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s10))
			Prob = 0.1f;
		break;

	case (int)State::s9:
		if ((Action == (int)Action::a1) && (NextState == (int)State::s4))
			Prob = 0.9f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s4))
			Prob = 0.1f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s10))
			Prob = 0.9f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s10))
			Prob = 0.1f;
		else if ((Action == (int)Action::b1) && (NextState == (int)State::s7))
			Prob = 0.9f;

		else if ((Action == (int)Action::b2) && (NextState == (int)State::s7))
			Prob = 0.1f;

		else if ((Action == (int)Action::b2) && (NextState == (int)State::s10))
			Prob = 0.9f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s10))
			Prob = 0.1f;
		break;

	case (int)State::s7:
		if ((Action == (int)Action::a3) && (NextState == (int)State::s6))
			Prob = 0.9f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s6))
			Prob = 0.1f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s11))
			Prob = 0.9f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s11))
			Prob = 0.1f;
		else if ((Action == (int)Action::b2) && (NextState == (int)State::s8))
			Prob = 0.9f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s8))
			Prob = 0.1f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s9))
			Prob = 0.9f;

		else if ((Action == (int)Action::b2) && (NextState == (int)State::s9))
			Prob = 0.1f;
		break;

	case (int)State::s2:

		if ((Action == (int)Action::b1) && (NextState == (int)State::s6))
			Prob = 0.9f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s5))
			Prob = 0.9f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s5))
			Prob = 0.1f;
		else if ((Action == (int)Action::a1) && (NextState == (int)State::s1))
			Prob = 0.9f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s1))
			Prob = 0.1f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s3))
			Prob = 1.0f;				
		break;

	case (int)State::s6:
		if ((Action == (int)Action::b2) && (NextState == (int)State::s2))
			Prob = 0.9f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s11))
			Prob = 0.9f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s11))
			Prob = 0.1f;
		else if ((Action == (int)Action::a2) && (NextState == (int)State::s7))
			Prob = 0.9f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s7))
			Prob = 0.1f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s3))
			Prob = 1.0f;
		break;

	}
	return Prob;
}
vector<vector<vector<float>>> MDP::RewardFunction()
{
	vector<vector<vector<float>>> RewardValue;

	for (size_t i = 0; i < Total_state; i++)
	{
		vector<vector<float>> InnerVector;
		for (size_t j = 0; j < Total_action; j++)
		{
			vector<float> Vector;
			for (size_t k = 0; k < Total_state; k++)
			{
				Vector.push_back(GetReward(i, j, k));
			}
			InnerVector.push_back(Vector);
		}
		RewardValue.push_back(InnerVector);
	}

	return RewardValue;
}

float MDP::GetReward(int Pre_State, int Action, int NextState)//Input for Reward probability
{
	float Reward=0.0f;

	switch (Pre_State)
	{
	case (int)State::s0:
		if ((Action == (int)Action::b2) && (NextState == (int)State::s1))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s1))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s4))
			Reward = -1.0f;

		else if ((Action == (int)Action::b2) && (NextState == (int)State::s4))
			Reward = -1.0f;
		break;

	case (int)State::s5:
		if ((Action == (int)Action::a3) && (NextState == (int)State::s2))
			Reward = -1.0f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s2))
			Reward = -1.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s1))
			Reward = -1.0f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s1))
			Reward = -1.0f;
		break;

	case (int)State::s10:
		if ((Action == (int)Action::a2) && (NextState == (int)State::s9))
			Reward = -1.0f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s9))
			Reward = -1.0f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s4))
			Reward = -1.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s4))
			Reward = -1.0f;
		break;

	case (int)State::s8:
		if ((Action == (int)Action::b1) && (NextState == (int)State::s7))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s7))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s9))
			Reward = -1.0f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s9))
			Reward = -1.0f;
		break;

	case (int)State::s11:
		if ((Action == (int)Action::a3) && (NextState == (int)State::s6))
			Reward = -1.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s6))
			Reward = -1.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s7))
			Reward = -1.0f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s7))
			Reward = -1.0f;
		break;

	case (int)State::s1:
		if ((Action == (int)Action::b3) && (NextState == (int)State::s4))
			Reward = -1.0f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s4))
			Reward = -1.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s5))
			Reward = -10.0f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s5))
			Reward = -10.0f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s2))
			Reward = -1.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s2))
			Reward = -1.0f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s0))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s0))
			Reward = -1.0f;
		break;

	case (int)State::s4:
		if ((Action == (int)Action::b2) && (NextState == (int)State::s1))
			Reward = -1.0f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s0))
			Reward = -1.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s9))
			Reward = -1.0f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s1))
			Reward = -1.0f;
		else if ((Action == (int)Action::b2) && (NextState == (int)State::s0))
			Reward = -1.0f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s9))
			Reward = -1.0f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s10))
			Reward = -10.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s10))
			Reward = -10.0f;
		break;

	case (int)State::s9:
		if ((Action == (int)Action::a1) && (NextState == (int)State::s4))
			Reward = -1.0f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s4))
			Reward = -1.0f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s10))
			Reward = -10.0f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s10))
			Reward = -10.0f;
		else if ((Action == (int)Action::b1) && (NextState == (int)State::s7))
			Reward = -1.0f;

		else if ((Action == (int)Action::b2) && (NextState == (int)State::s7))
			Reward = -1.0f;

		else if ((Action == (int)Action::b2) && (NextState == (int)State::s10))
			Reward = -1.0f;

		else if ((Action == (int)Action::b1) && (NextState == (int)State::s10))
			Reward = -1.0f;
		break;

	case (int)State::s7:
		if ((Action == (int)Action::a3) && (NextState == (int)State::s6))
			Reward = -1.0f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s6))
			Reward = -1.0f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s11))
			Reward = -10.0f;

		else if ((Action == (int)Action::a3) && (NextState == (int)State::s11))
			Reward = -10.0f;
		else if ((Action == (int)Action::b2) && (NextState == (int)State::s8))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s8))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s9))
			Reward = -1.0f;

		else if ((Action == (int)Action::b2) && (NextState == (int)State::s9))
			Reward = -1.0f;
		break;

	case (int)State::s2:
		if ((Action == (int)Action::b1) && (NextState == (int)State::s6))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s6))
			Reward = -1.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s5))
			Reward = -10.0f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s5))
			Reward = -10.0f;
		else if ((Action == (int)Action::a1) && (NextState == (int)State::s1))
			Reward = -1.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s1))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s3))
			Reward = 100.0f;
		break;

	case (int)State::s6:
		if ((Action == (int)Action::b2) && (NextState == (int)State::s2))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s2))
			Reward = -1.0f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s11))
			Reward = -10.0f;

		else if ((Action == (int)Action::a2) && (NextState == (int)State::s11))
			Reward = -10.0f;
		else if ((Action == (int)Action::a2) && (NextState == (int)State::s7))
			Reward = -1.0f;

		else if ((Action == (int)Action::a1) && (NextState == (int)State::s7))
			Reward = -1.0f;

		else if ((Action == (int)Action::b3) && (NextState == (int)State::s3))
			Reward = 100.0f;
		break;

	}
	return Reward;
}
