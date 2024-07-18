#include "car.h"
using namespace std;

bool Car::IsTurnedOn() const
{
    return m_engineIsTurnOn;
}

Car::Direction Car::GetDirection() const
{
    return m_direction;
}

int Car::GetSpeed() const
{
    return abs(m_speed);
}

Car::Gear Car::GetGear() const
{
    return m_gear;
}

bool Car::TurnOnEngine()
{
    if (!m_engineIsTurnOn)
        m_engineIsTurnOn = true;
    return m_engineIsTurnOn;
}

bool Car::TurnOffEngine()
{
    if (m_engineIsTurnOn && m_gear == Gear::Neutral && m_direction == Direction::Stop)
        m_engineIsTurnOn = false;
    else
        return false;
    return true;
}

bool Car::SetSpeed(int speed)
{
    pair<int, int> speedRange = m_speedIntervals[static_cast<int>(m_gear) + 1];
    if (!m_engineIsTurnOn || speed < 0)
        return false;
    if (m_gear == Gear::Neutral && speed > abs(m_speed))
        return false;
    if (speed < speedRange.first || speed > speedRange.second)
        return false;
    if (speed == 0 && m_gear == Gear::Neutral)
        m_direction = Direction::Stop;
    if (m_gear == Gear::Reverse && speed < abs(m_speed))
        return false;
    if (m_gear == Gear::Reverse && m_direction == Direction::Backward)
        m_speed = -speed;
    else
        m_speed = speed;
    return true;
}

bool Car::SetGear(Gear gear)
{
    if (!m_engineIsTurnOn)
        return false;
    if (m_gear == gear)
        return true;
    if (m_speed == 0 && gear == Gear::Reverse)
    {
        m_gear = gear;
        m_direction = Direction::Backward;
        return true;
    }
    if (m_speed == 0 && gear == Gear::Neutral)
    {
        m_gear = gear;
        return true;
    }
    if (m_speed < 0 && gear == Gear::Neutral)
    {
        m_gear = gear;
        return true;
    }
    if (m_speed == 0 && (m_gear == Gear::Reverse  || m_gear == Gear::Neutral) && gear == Gear::First)
    {
        m_gear = gear;
        m_direction = Direction::Forward;
        return true;
    }
    if (m_speed > m_speedIntervals[static_cast<int>(gear) + 1].first && m_speed < m_speedIntervals[static_cast<int>(gear) + 1].second)
    {
        m_gear = gear;
        return true;
    }
    return false;
}
