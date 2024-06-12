#pragma once
#ifndef COUNTER_H

class Counter final
{
private:
	int trainings{0};
public:
	Counter() {};
	Counter(int num) : Counter() { setTrainings(num); }
	~Counter() {};

	inline void setTrainings(int num) { trainings = num; }
	inline void addTrainings(int num) { trainings += num; }
	inline int getTrainings() const { return trainings; }
	inline void markTrainings() { --trainings; }
};

#define COUNTER_H
#endif
