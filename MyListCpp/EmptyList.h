#pragma once
#include <exception>

class EmptyListException : std::exception
{
public:
	EmptyList();
	~EmptyList();
};

