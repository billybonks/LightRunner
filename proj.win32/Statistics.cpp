#include "Statistics.h"

	Statistics::Statistics()
	{
		_score = 0;
		_multiplier = 1;
		_distanceTraveld = 0;
		_velocity = 0.1;
		_maxSpeed =15;
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
		_score += _score*_multiplier;
	}

	void Statistics::IncrementMultiplier(int value){
		_multiplier += value;
	}

	float Statistics::GetVelocity(){
		return this->_velocity;
	}

	void Statistics::SetVelocity(float velocity){
		this->_velocity = velocity;
	}

	void Statistics::SetAcceleration(float acceleration){
		this->_acceleration = acceleration;
	}

	float Statistics::GetAcceleration(){
		return this->_acceleration;
	}

	float Statistics::Accelerate(float timeSinceLast,float mass){
		float force;
		//this->_velocity += timeSinceLast*_acceleration;
		force = this->GetForceToAccelerate(mass);
		return force;
	}

	float Statistics::GetForceToAccelerate(float mass){
		return mass* _acceleration;
	}

	float Statistics::GetDistanceTraveled(){
		return _distanceTraveld;
	}

	void Statistics::IncrementDistance(float distance){
		_distanceTraveld += distance;
	}

	float Statistics::GetMaximumVelocity(){
		return _maxSpeed;
	}
