#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../main/car.h";


bool ExpectedValues(Car& car, int expectedSpeed, Car::Gear expectedGear, Car::Direction expectedDirection, bool IsEngine)
{
	return ((car.GetSpeed() == expectedSpeed) && (car.GetGear() == expectedGear) && (car.GetDirection() == expectedDirection) && (car.IsTurnedOn() == IsEngine));
}

TEST_CASE("Initial information about a car")
{
	GIVEN("A car")
	{
		Car car;
		WHEN("Engine turn on")
		{
			car.TurnOnEngine();
			THEN("All properties have initial values")
			{
				REQUIRE(ExpectedValues(car, 0, Car::Gear::Neutral, Car::Direction::Stop, true));
			}
		}
		WHEN("Engine turn off")
		{
			car.TurnOffEngine();
			THEN("All properties have initial values")
			{
				REQUIRE(ExpectedValues(car, 0, Car::Gear::Neutral, Car::Direction::Stop, false));
			}
			THEN("All properties can not change while engine off")
			{
				REQUIRE(!car.SetGear(Car::Gear::First));
				REQUIRE(!car.SetSpeed(20));
			}
		}
	}
}

TEST_CASE("Drive car on the first gear")
{
	GIVEN("Car with engine on and first gear")
	{
		Car car;
		car.TurnOnEngine();
		car.SetGear(Car::Gear::First);
		THEN("Change speed")
		{
			REQUIRE(car.SetSpeed(25));
		}
		THEN("Change speed for incorrect values")
		{
			REQUIRE(!car.SetSpeed(50));
		}
	}
}

SCENARIO("Change speed on negative values")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::Gear::First);
	REQUIRE(!car.SetSpeed(-10));
}

SCENARIO("Trying to change speed up when there is a neutral gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::Gear::First);
	car.SetSpeed(25);
	car.SetGear(Car::Gear::Neutral);
	REQUIRE(!car.SetSpeed(27));
}

SCENARIO("Switching between different gears when speed up and watch finish state")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::Gear::First);
	car.SetSpeed(25);
	REQUIRE(car.SetGear(Car::Gear::Second));
	car.SetSpeed(40);
	REQUIRE(car.SetGear(Car::Gear::Third));
	car.SetSpeed(60);
	REQUIRE(car.SetGear(Car::Gear::Fourth));
	REQUIRE(ExpectedValues(car, 60, Car::Gear::Fourth, Car::Direction::Forward, true));
}

SCENARIO("Reduce speed on neutral gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::Gear::First);
	car.SetSpeed(30);
	car.SetGear(Car::Gear::Neutral);
	REQUIRE(car.SetSpeed(25));
	car.SetGear(Car::Gear::Second);
	car.SetSpeed(50);
	car.SetGear(Car::Gear::Neutral);
	REQUIRE(car.SetSpeed(35));
}


SCENARIO("Trying to correctly stop car")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::Gear::First);
	car.SetSpeed(30);
	car.SetGear(Car::Gear::Neutral);
	car.SetSpeed(0);
	REQUIRE(car.TurnOffEngine());
	REQUIRE(ExpectedValues(car, 0, Car::Gear::Neutral, Car::Direction::Stop, false));
}

SCENARIO("Trying to stop car while driving")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::Gear::First);
	car.SetSpeed(30);
	REQUIRE(!car.TurnOffEngine());
}

SCENARIO("Switch to reverse gear and driving")
{
	Car car;
	car.TurnOnEngine();
	REQUIRE(car.SetGear(Car::Gear::Reverse));
	REQUIRE(car.SetSpeed(10));
	REQUIRE(car.SetSpeed(15));
}

SCENARIO("Trying to speed down on reverse gear")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::Gear::Reverse);
	car.SetSpeed(15);
	REQUIRE(!car.SetSpeed(0));

}

SCENARIO("Trying to switch from reverse to firts when car stop")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::Gear::Reverse);
	REQUIRE(car.SetGear(Car::Gear::First));
}

SCENARIO("Trying to switch from reverse to neuntal when car stop and drive forward")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::Gear::Reverse);
	REQUIRE(car.SetGear(Car::Gear::Neutral));
	REQUIRE(!car.SetSpeed(30));
}

SCENARIO("Switch the all gear to itself on different speeds")
{
	Car car;
	car.TurnOnEngine();
	car.SetGear(Car::Gear::Reverse);
	REQUIRE(car.SetGear(Car::Gear::Reverse));
	car.SetGear(Car::Gear::Neutral);
	REQUIRE(car.SetGear(Car::Gear::Neutral));
	car.SetGear(Car::Gear::First);
	car.SetSpeed(30);
	REQUIRE(car.SetGear(Car::Gear::First));
	car.SetGear(Car::Gear::Second);
	car.SetSpeed(40);
	REQUIRE(car.SetGear(Car::Gear::Second));
	car.SetGear(Car::Gear::Third);
	car.SetSpeed(50);
	REQUIRE(car.SetGear(Car::Gear::Third));
	car.SetGear(Car::Gear::Fourth);
	REQUIRE(car.SetGear(Car::Gear::Fourth));
	car.SetSpeed(80);
	car.SetGear(Car::Gear::Fifth);
	REQUIRE(car.SetGear(Car::Gear::Fifth));
}