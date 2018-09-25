#pragma once

#include<vector>

using namespace std;

//Global veriable
const int Total_state = 12;
const int Total_action = 6;

const float Epsilon = 0.001f;
const float Gamma = 0.9f;


//All the stetes and the Actions
enum class State { s0, s1, s2, s3, s4, s5, s6, s7, s8, s9, s10, s11};
enum class Action { a1, b1, a2, b2, a3, b3};


const int GOALSTATE = (int)State::s3;

class MDP
{
private:

	static MDP* NewObject;

	MDP();
	~MDP();

	vector<vector<vector<float>>> TransitionFunction(); //it's return the transition probability
	vector<vector<vector<float>>> RewardFunction();		//it's return the reward value for each transition
	float GetProbability(int Pre_State, int Action, int NextState);
	float GetReward(int Pre_State, int Action, int NextState);

public:
	vector<vector<vector<float>>> TransitionProb;		//vector for TransitionProb
	vector<vector<vector<float>>> RewardValue;			//vector for RewardValue
	static MDP* Ptr();
	
};
