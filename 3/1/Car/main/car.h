#pragma once
#include <vector>
#include <utility>

class Car
{
public:
	enum class Direction
	{
		Stop, 
		Forward,
		Backward
	};

	enum class Gear
	{
		Reverse = -1,
		Neutral,
		First, 
		Second, 
		Third,
		Fourth,
		Fifth
	};

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetSpeed() const;
	Gear GetGear() const;
	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetSpeed(int speed);
	bool SetGear(Gear gear);

private:
	//Переименовать m_engine
	bool m_engineIsTurnOn = false;
	int m_speed = 0;
	Direction m_direction = Direction::Stop;
	Gear m_gear = Gear::Neutral;
	std::vector<std::pair<int, int>> m_speedIntervals = { {0, 20}, {0, 150}, {0, 30}, {20, 50}, {30, 60}, {40, 90}, {50, 150} };

};