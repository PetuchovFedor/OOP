#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include "../main/CStringStack.h"
#include "../main/EmptyStackExpression.h"
using namespace std;

TEST_CASE("Work with stack and check expressions")
{
	GIVEN("Empty stack")
	{
		CStringStack stack;
		THEN("size == 0 and stack is empty")
		{
			REQUIRE(stack.GetSize() == 0);
			REQUIRE(stack.IsEmpty());
		}
		THEN("GetTop and Pop get expression")
		{
			REQUIRE_THROWS_AS(stack.GetTop(), EmptyStackExpression);
			REQUIRE_THROWS_AS(stack.Pop(), EmptyStackExpression);
		}
		WHEN("Push")
		{
			stack.Push("qwerty"s);
			THEN("GetTop() return qwerty and size = 1 and no empty")
			{
				REQUIRE(stack.GetTop() == "qwerty");
				REQUIRE(stack.GetSize() == 1);
				REQUIRE(!stack.IsEmpty());
			}
			THEN("if Pop() stack is empty")
			{
				stack.Pop();
				REQUIRE(stack.GetSize() == 0);
				REQUIRE(stack.IsEmpty());
			}
		}
		WHEN("More Push()")
		{
			stack.Push("qwerty"s);
			stack.Push("abcd"s);
			stack.Push("qsc"s);
			stack.Push("asdf"s);
			THEN("GetTop() return asdf and size = 4")
			{
				REQUIRE(stack.GetTop() == "asdf");
				REQUIRE(stack.GetSize() == 4);
				REQUIRE(!stack.IsEmpty());
			}
			WHEN("Pop() 2 time")
			{
				stack.Pop();
				stack.Pop();
				THEN("GetTop() return asdf and size = 4")
				{
					REQUIRE(stack.GetTop() == "abcd");
					REQUIRE(stack.GetSize() == 2);
					REQUIRE(!stack.IsEmpty());
				}
			}
		}
	}
}

SCENARIO("Check constructors")
{
	CStringStack stack;
	stack.Push("qwerty"s);
	stack.Push("abcd"s);
	stack.Push("qsc"s);
	stack.Push("asdf"s);
	CStringStack tmp(stack);
	REQUIRE(tmp.GetTop() == stack.GetTop());
	REQUIRE(tmp.GetSize() == stack.GetSize());
	CStringStack stack2(move(tmp));
	REQUIRE(stack2.GetTop() == stack.GetTop());
	REQUIRE(stack2.GetSize() == stack.GetSize());
	REQUIRE(tmp.GetSize() == 0);
	REQUIRE(tmp.IsEmpty());
	REQUIRE_THROWS_AS(tmp.GetTop(), EmptyStackExpression);
}

SCENARIO("Check assignment operators")
{
	CStringStack stack;
	stack.Push("qwerty"s);
	stack.Push("abcd"s);
	stack.Push("qsc"s);
	stack.Push("asdf"s);
	CStringStack tmp;
	tmp = stack;
	REQUIRE(tmp.GetTop() == stack.GetTop());
	REQUIRE(tmp.GetSize() == stack.GetSize());
	CStringStack stack2;
	stack2 = move(tmp);
	REQUIRE(stack2.GetTop() == stack.GetTop());
	REQUIRE(stack2.GetSize() == stack.GetSize());
	REQUIRE(tmp.GetSize() == 0);
	REQUIRE(tmp.IsEmpty());
	REQUIRE_THROWS_AS(tmp.GetTop(), EmptyStackExpression);
}