#include "CStringStack.h"
#include <algorithm>
#include "EmptyStackExpression.h"

CStringStack::CStringStack()
{
	//m_capacity = 4;
	//m_arr = new std::string[m_capacity];
	m_size = 0;
}

CStringStack::CStringStack(CStringStack const& other)
	/*: m_size(other.m_size)
	, m_capacity(other.m_capacity)
	, m_arr(new std::string[other.m_capacity])*/
{
	CStringStack tmpStack, newStack;
	auto otherTop = other.m_top.get();
	while (tmpStack.m_size != other.m_size)
	{
		tmpStack.Push(otherTop->value);
		otherTop = otherTop->next.get();
	}
	auto newTop = tmpStack.m_top.get();
	while (newStack.m_size != tmpStack.m_size)
	{
		newStack.Push(newTop->value);
		newTop = newTop->next.get();
	}
	m_size = newStack.m_size;
	m_top = move(newStack.m_top);
}

CStringStack::CStringStack(CStringStack&& other)
	: m_size(other.m_size) , m_top(move(other.m_top))
{
	other.m_size = 0;
	other.m_top = nullptr;
}

CStringStack::~CStringStack()
{
	m_size = 0;
}


void CStringStack::Push(std::string const& str)
{
	auto newTop = std::make_unique<Node>(str, move(m_top));
	m_top = move(newTop);
	m_size++;
}

void CStringStack::Pop()
{
	if (IsEmpty())
		throw EmptyStackExpression("stack is empty");
	m_top = move(m_top->next);
	m_size--;
}

std::string CStringStack::GetTop() const
{
	if (IsEmpty())
		throw EmptyStackExpression("stack is empty");
	return m_top->value;
}

size_t CStringStack::GetSize() const
{
	return m_size;
}

bool CStringStack::IsEmpty() const
{
	return m_size == 0;
}

CStringStack& CStringStack::operator=(CStringStack const& other)
{
	if (this == &other)
	{
		return *this;
	}

	CStringStack tempStack(other);
	m_size = tempStack.m_size;
	m_top = move(tempStack.m_top);
	

	tempStack.m_size = 0;
	tempStack.m_top = nullptr;

	return *this;
}

CStringStack& CStringStack::operator=(CStringStack&& other)
{
	m_size = other.m_size;
	m_top = move(other.m_top);
	other.m_top = nullptr;
	other.m_size = 0;
	return *this;
}


