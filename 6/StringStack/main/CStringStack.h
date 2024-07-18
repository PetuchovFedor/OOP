#pragma once
#include <string>
#include <memory>

class CStringStack
{
public:
	CStringStack();

	CStringStack(CStringStack const& other);

	CStringStack(CStringStack&& other);

	~CStringStack();

	void Push(std::string const& str);

	void Pop();

	std::string GetTop() const;

	size_t GetSize() const;

	bool IsEmpty() const;

	CStringStack& operator=(CStringStack const& other);

	CStringStack& operator=(CStringStack&& other);

private:
	struct Node
	{
		Node(const std::string& data, std::unique_ptr<Node>&& next)
			: value(data), next(std::move(next))
		{}
		std::string value;
		std::unique_ptr<Node> next;

	};
	std::unique_ptr<Node> m_top;
	size_t m_size;
};