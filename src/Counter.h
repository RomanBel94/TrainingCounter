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

	inline void setTrainings(int num) noexcept{ trainings = num; }
	inline void addTrainings(int num) noexcept { trainings += num; }
	inline int getTrainings() const noexcept { return trainings; }
	inline void markTrainings() noexcept { --trainings; }
};

#define COUNTER_H
#endif
