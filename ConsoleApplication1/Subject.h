#pragma once

#include "Observer.h"
#include <vector>

class Subject
{
private:
	std::vector<Observer*> subjects;

public:
	virtual void add_subject(Observer* subject);
	virtual void notify(const char* message = nullptr);
};


