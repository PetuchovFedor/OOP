#pragma once
#include "car.h"
#include <iostream>
#include <functional>
#include <map>

class CarRemoteControl
{
public:
	CarRemoteControl(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool EngineOn(std::istream& args);
	bool EngineOff(std::istream& args);
	bool SetGear(std::istream& args);
	bool SetSpeed(std::istream& args);
	bool Info(std::istream& args) const;

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;
};
