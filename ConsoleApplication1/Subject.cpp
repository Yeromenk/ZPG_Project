#include "Subject.h"

void Subject::add_subject(Observer* subject) {
	subjects.push_back(subject);
}

void Subject::remove_subject(Observer* subject)
{
	subjects.erase(std::remove(subjects.begin(), subjects.end(), subject), subjects.end());
}

void Subject::notify(const char* message) {
	for (auto subject : subjects) {
		subject->update(message);
	}
}