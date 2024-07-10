#pragma once
#ifndef COUNTER_H

#include <stdint.h> // uint8_t

class Counter final
{
private:
	uint8_t trainings { 0 };    // current value of trainings
public:
	// set <num> of trainings if <num> is greater than 0
    inline void setTrainings(const uint8_t num) noexcept
        { num >= 0 ? trainings = num : trainings; }
	
    // add <num> of trainings if <num> is greater than 0
    inline void addTrainings(const uint8_t num) noexcept
        { num >= 0 ? trainings += num : trainings; }
	
    // returns trainings
    inline const uint8_t getTrainings() const noexcept
        { return trainings; }
	
    // decrement trainings by 1 if current number of trainings is greater than 0
    inline void markTraining() noexcept 
        { trainings > 0 ? --trainings : trainings = 0; }
};

#define COUNTER_H
#endif
