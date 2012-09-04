// GameObject.h
#ifndef STATISTICS
#define STATISTICS

class Statistics  {
public:
	Statistics();
	//Multiplier
	int GetMultiplier();
	int SetMultiplier();
	void HalfMultiplier();
	void IncrementMultiplier(int value);
	//Score
	int GetScore();
	void IncrementScore(int value);
	//Velocity
	float GetVelocity();
	void SetVelocity(float velocity);
	void SetAcceleration(float acceleration);
	float GetAcceleration();
	float Accelerate(float timeSinceLast,float mass);
	float GetForceToAccelerate(float mass);
	void IncrementDistance(float distance);
	float GetDistanceTraveled();
	float GetMaximumVelocity();
private:
	int _score;
	int _multiplier;
	float _velocity;
	float _distanceTraveld;
	float _acceleration;
	float _maxSpeed;
protected:

};

#endif
