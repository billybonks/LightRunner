// GameObject.h


class Statistics  {
public:
	Statistics();
	int GetMultiplier();
	int GetScore();
	void HalfMultiplier();
	void IncrementScore(int value);
	void IncrementMultiplier(int value);
	float GetVelocity();
	void SetVelocity(float velocity);
private:
	int _score;
	int _multiplier;
    float _velocity;
	float _distanceTraveld;
protected:

};
