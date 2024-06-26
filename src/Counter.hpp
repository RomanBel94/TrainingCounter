#pragma once
#ifndef COUNTER_H

#include <stdint.h> // uint8_t

class Counter final
{
private:
	uint8_t trainings { 0 };
public:
	Counter() {};
	~Counter() {};

	inline void setTrainings(const uint8_t num) noexcept{ trainings = num; }
	inline void addTrainings(const uint8_t num) noexcept { trainings += num; }
	inline const uint8_t getTrainings() const noexcept { return trainings; }
	inline void markTraining() noexcept { --trainings; }
};

#define COUNTER_H
#endif
