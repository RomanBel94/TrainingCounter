#pragma once
#ifndef COUNTER_H

#include <stdint.h> // uint16_t
#include <limits.h> // _UI8_MAX

class Counter final
{
private:
	uint16_t trainings { 0 };    // current value of trainings
public:
	// set <num> of trainings if <num> is greater than 0
    inline void setTrainings(const uint16_t num) noexcept
        { num >= 0 &&  num <= _UI8_MAX ? trainings = num : trainings = _UI8_MAX; }
	
    // add <num> of trainings if <num> is greater than 0
    inline void addTrainings(const uint16_t num) noexcept
        { num >= 0 && (trainings + num) <= _UI8_MAX ? trainings += num : trainings = _UI8_MAX; }
	
    // returns trainings
    inline const uint16_t getTrainings() const noexcept
        { return trainings; }
	
    // decrement trainings by 1 if current number of trainings is greater than 0
    inline void markTraining() noexcept 
        { trainings > 0 ? --trainings : trainings = 0; }
};

#define COUNTER_H
#endif
