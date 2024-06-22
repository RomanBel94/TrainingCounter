#pragma once
#ifndef COUNTER_H

#include <stdint.h> // uint8_t

class Counter final
{
private:
	int trainings{0};
public:
	Counter() {};
	~Counter() {};

	inline void setTrainings(uint8_t num) noexcept{ trainings = num; }
	inline void addTrainings(uint8_t num) noexcept { trainings += num; }
	inline int getTrainings() const noexcept { return trainings; }
	inline void markTrainings() noexcept { --trainings; }
};

#define COUNTER_H
#endif
