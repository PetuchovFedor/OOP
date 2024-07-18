#include "CarRemoteControl.h"
using namespace std;
#include <string>
#include <sstream>

namespace 
{
    int StrToInt(string str, ostream& out)
    {
        try
        {
            int num = stoi(str);
            return num;
        }
        catch (exception)
        {
            out << "invalid input argument" << endl;
        }
    }

}
CarRemoteControl::CarRemoteControl(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ 
                { "EngineOn", [this](std::istream& args) {
                    return EngineOn(args); } },
                { "EngineOff", [this](std::istream& args) {
                    return EngineOff(args); } },
                { "SetGear", [this](std::istream& args) {
                    return SetGear(args); } },
                { "SetSpeed", [this](std::istream& args) {
                    return SetSpeed(args); } },
                { "Info", [this](std::istream& args) {
                    return Info(args); } } 
                })
{
}

bool CarRemoteControl::HandleCommand()
{
    string commandLine;
    getline(m_input, commandLine);
    istringstream strm(commandLine);

    string action;
    strm >> action;

    auto it = m_actionMap.find(action);
    if (it != m_actionMap.end())
    {
        return it->second(strm);
    }

    return false;
}

bool CarRemoteControl::EngineOn(std::istream& /*args*/)
{
    m_car.TurnOnEngine();
    m_output << "Engine is turned on" << endl;
    return true;;
}

bool CarRemoteControl::EngineOff(std::istream& /*args*/)
{
    if (!m_car.TurnOffEngine())
        m_output << "You can't turn off the engine" << endl;
    else
        m_output << "Engine is turned off" << endl;
    return true;
}

//Вывести в анонимный namespace

bool CarRemoteControl::SetGear(std::istream& args)
{
   
    string arg;
    args >> arg;
    int gear = StrToInt(arg, m_output);
    if (m_car.SetGear(static_cast<Car::Gear>(gear)))
        m_output << "Gear " << gear << " succesfully set" << endl;
    else
        m_output << "There are some problem with set gear" << endl;
    return true;
}

bool CarRemoteControl::SetSpeed(std::istream& args)
{
    string arg;
    args >> arg;
    int speed = StrToInt(arg, m_output);
    if (m_car.SetSpeed(speed))
        m_output << "Speed " << speed << " succesfully set" << endl;
    else
        m_output << "There are some problem with set speed" << endl;
    return true;
}

bool CarRemoteControl::Info(std::istream& /*args*/) const
{
    string isTurnedOn = m_car.IsTurnedOn() ? " on" : "off";
    m_output << "Engine is " << isTurnedOn << endl;
    m_output << "Gear is " << static_cast<int>(m_car.GetGear()) << endl;
    m_output << "Speed is " << m_car.GetSpeed() << endl;
    m_output << "Direction is ";
    switch (m_car.GetDirection())
    {
    case Car::Direction::Forward:
        m_output << "forward" << endl;
        break;
    case Car::Direction::Backward:
        m_output << "backward" << endl;
        break;
    case Car::Direction::Stop:
        m_output << "standing still" << endl;
        break;
    }
    return true;
}
