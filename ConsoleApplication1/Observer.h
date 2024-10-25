#pragma once

class Observer
{
public:
	virtual void update(const char* message=nullptr) = 0;
};