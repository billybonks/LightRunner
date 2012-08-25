#include "Statistics.h"

	Statistics::Statistics()
	{
		_score = 0;
		_multiplier = 0;
		_distanceTraveld = 0;
		_velocity = 0;
	}

	int Statistics::GetMultiplier(){
		return _multiplier;
	}

	int Statistics::GetScore(){
		return _score;
	}

	void Statistics::HalfMultiplier(){
		_multiplier = _multiplier/2;
	}

	void Statistics::IncrementScore(int value){

	}

	void Statistics::IncrementMultiplier(int value){

	}

	float Statistics::GetVelocity(){
		return this->_velocity;
	}

	void Statistics::SetVelocity(float velocity){
		this->_velocity = velocity;
	}

