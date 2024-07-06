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

	inline void setTrainings(const uint8_t num) noexcept
        { num > 0 ? trainings = num : trainings; }
	
    inline void addTrainings(const uint8_t num) noexcept
        { num > 0 ? trainings += num : trainings; }
	
    inline const uint8_t getTrainings() const noexcept
        { return trainings; }
	
    inline void markTraining() noexcept 
        { trainings > 0 ? --trainings : trainings = 0; }
};

#define COUNTER_H
#endif
