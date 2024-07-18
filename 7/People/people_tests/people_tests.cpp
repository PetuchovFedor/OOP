#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include "../main/CAdvancedStudent.h"
#include "../main/CPerson.h"
#include "../main/CPupil.h"
#include "../main/CStudent.h"
#include "../main/CTeacher.h"
#include "../main/CWorker.h"
#include "../main/IAdvancedStudent.h"
#include "../main/IPerson.h"
#include "../main/IPupil.h"
#include "../main/IStudent.h"
#include "../main/ITeacher.h"
#include "../main/IWorker.h"
#include "../main/CStudentImpl.h"
#include "../main/CPersonImpl.h"
using namespace std;

TEST_CASE("Check Person")
{
	WHEN("first constructor")
	{
		CPerson person("Petuchov Fedya Alecsandrovich", "8 Pushkin street");
		THEN("Methods return correct values")
		{
			REQUIRE(person.GetName() == "Fedya");
			REQUIRE(person.GetSurname() == "Petuchov");
			REQUIRE(person.GetMiddleName() == "Alecsandrovich");
			REQUIRE(person.GetAddress() == "8 Pushkin street");
		}
	}
	WHEN("second constructor")
	{
		CPerson person("Petuchov", "Fedya", "Alecsandrovich", "8 Pushkin street");
		THEN("Methods return correct values")
		{
			REQUIRE(person.GetName() == "Fedya");
			REQUIRE(person.GetSurname() == "Petuchov");
			REQUIRE(person.GetMiddleName() == "Alecsandrovich");
			REQUIRE(person.GetAddress() == "8 Pushkin street");
		}
	}
}

TEST_CASE("Check workers")
{
	WHEN("first constructor")
	{
		CWorker worker("Petuchov Fedya Alecsandrovich", "8 Pushkin street", "programmer");
		THEN("Methods return correct values")
		{
			REQUIRE(worker.GetName() == "Fedya");
			REQUIRE(worker.GetSurname() == "Petuchov");
			REQUIRE(worker.GetMiddleName() == "Alecsandrovich");
			REQUIRE(worker.GetAddress() == "8 Pushkin street");
			REQUIRE(worker.GetSpecialization() == "programmer");
		}
	}
	WHEN("second constructor")
	{
		CWorker worker("Petuchov", "Fedya", "Alecsandrovich", "8 Pushkin street", "programmer");
		THEN("Methods return correct values")
		{
			REQUIRE(worker.GetName() == "Fedya");
			REQUIRE(worker.GetSurname() == "Petuchov");
			REQUIRE(worker.GetMiddleName() == "Alecsandrovich");
			REQUIRE(worker.GetAddress() == "8 Pushkin street");
			REQUIRE(worker.GetSpecialization() == "programmer");
		}
	}
}

TEST_CASE("Check pupil")
{
	WHEN("first constructor")
	{
		CPupil pupil("Petuchov Fedya Alecsandrovich", "8 Pushkin street", "school number 5", "9A");
		THEN("Methods return correct values")
		{
			REQUIRE(pupil.GetName() == "Fedya");
			REQUIRE(pupil.GetSurname() == "Petuchov");
			REQUIRE(pupil.GetMiddleName() == "Alecsandrovich");
			REQUIRE(pupil.GetAddress() == "8 Pushkin street");
			REQUIRE(pupil.GetSchoolName() == "school number 5");
			REQUIRE(pupil.GetGroup() == "9A");
		}
	}
	WHEN("second constructor")
	{
		CPupil pupil("Petuchov", "Fedya", "Alecsandrovich", "8 Pushkin street", "school number 5", "9A");
		THEN("Methods return correct values")
		{
			REQUIRE(pupil.GetName() == "Fedya");
			REQUIRE(pupil.GetSurname() == "Petuchov");
			REQUIRE(pupil.GetMiddleName() == "Alecsandrovich");
			REQUIRE(pupil.GetAddress() == "8 Pushkin street");
			REQUIRE(pupil.GetSchoolName() == "school number 5");
			REQUIRE(pupil.GetGroup() == "9A");
		}
	}
}

TEST_CASE("Check teacher")
{
	WHEN("first constructor")
	{
		CTeacher teacher("Petuchov Fedya Alecsandrovich", "8 Pushkin street", "programming");
		THEN("Methods return correct values")
		{
			REQUIRE(teacher.GetName() == "Fedya");
			REQUIRE(teacher.GetSurname() == "Petuchov");
			REQUIRE(teacher.GetMiddleName() == "Alecsandrovich");
			REQUIRE(teacher.GetAddress() == "8 Pushkin street");
			REQUIRE(teacher.GetSubject() == "programming");
		}
	}
	WHEN("second constructor")
	{
		CTeacher teacher("Petuchov", "Fedya", "Alecsandrovich", "8 Pushkin street", "programming");
		THEN("Methods return correct values")
		{
			REQUIRE(teacher.GetName() == "Fedya");
			REQUIRE(teacher.GetSurname() == "Petuchov");
			REQUIRE(teacher.GetMiddleName() == "Alecsandrovich");
			REQUIRE(teacher.GetAddress() == "8 Pushkin street");
			REQUIRE(teacher.GetSubject() == "programming");
		}
	}
}

TEST_CASE("Check student")
{
	WHEN("first constructor")
	{
		CStudent student("Petuchov Fedya Alecsandrovich", "8 Pushkin street", "PGTU", "s1210501195");
		THEN("Methods return correct values")
		{
			REQUIRE(student.GetName() == "Fedya");
			REQUIRE(student.GetSurname() == "Petuchov");
			REQUIRE(student.GetMiddleName() == "Alecsandrovich");
			REQUIRE(student.GetAddress() == "8 Pushkin street");
			REQUIRE(student.GetUniversityName() == "PGTU");
			REQUIRE(student.GetStudentId() == "s1210501195");
		}
	}
	WHEN("second constructor")
	{
		CStudent student("Petuchov", "Fedya", "Alecsandrovich", "8 Pushkin street", "PGTU", "s1210501195");
		THEN("Methods return correct values")
		{
			REQUIRE(student.GetName() == "Fedya");
			REQUIRE(student.GetSurname() == "Petuchov");
			REQUIRE(student.GetMiddleName() == "Alecsandrovich");
			REQUIRE(student.GetAddress() == "8 Pushkin street");
			REQUIRE(student.GetUniversityName() == "PGTU");
			REQUIRE(student.GetStudentId() == "s1210501195");
		}
	}
}

TEST_CASE("Check advanced student")
{
	WHEN("first constructor")
	{
		CAdvancedStudent student("Petuchov Fedya Alecsandrovich", "8 Pushkin street", "PGTU", "s1210501195", "OOP");
		THEN("Methods return correct values")
		{
			REQUIRE(student.GetName() == "Fedya");
			REQUIRE(student.GetSurname() == "Petuchov");
			REQUIRE(student.GetMiddleName() == "Alecsandrovich");
			REQUIRE(student.GetAddress() == "8 Pushkin street");
			REQUIRE(student.GetUniversityName() == "PGTU");
			REQUIRE(student.GetStudentId() == "s1210501195");
			REQUIRE(student.GetDissertationTopic() == "OOP");
		}
	}
	WHEN("second constructor")
	{
		CAdvancedStudent student("Petuchov", "Fedya", "Alecsandrovich", "8 Pushkin street", "PGTU", "s1210501195", "OOP");
		//CAdvancedStudent st()
		THEN("Methods return correct values")
		{
			REQUIRE(student.GetName() == "Fedya");
			REQUIRE(student.GetSurname() == "Petuchov");
			REQUIRE(student.GetMiddleName() == "Alecsandrovich");
			REQUIRE(student.GetAddress() == "8 Pushkin street");
			REQUIRE(student.GetUniversityName() == "PGTU");
			REQUIRE(student.GetStudentId() == "s1210501195");
			REQUIRE(student.GetDissertationTopic() == "OOP");
		}
	}
}