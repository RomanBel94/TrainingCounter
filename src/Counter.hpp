#pragma once
#ifndef COUNTER_H

#include <cstdint> // uint32_t

#include "Save.h"

class Counter final
{
private:
    std::unique_ptr<Save> save = std::make_unique<Save>();
    uint32_t _trainings{0}; // current value of trainings
public:
    // set <num> of trainings if <num> is greater than 0
    inline void setTrainings(const uint32_t num) noexcept
    {
        num >= 0 && num <= UINT32_MAX ? _trainings = num
                                      : _trainings = UINT32_MAX;
    }

    // add <num> of trainings if <num> is greater than 0
    inline void addTrainings(const uint32_t num) noexcept
    {
        num >= 0 && (_trainings + num) <= UINT32_MAX ? _trainings += num
                                                     : _trainings = UINT32_MAX;
    }

    // returns trainings
    inline const uint32_t getTrainings() const noexcept { return _trainings; }

    // decrement trainings by 1 if current number of trainings is greater than 0
    inline void markTraining() noexcept
    {
        _trainings > 0 ? --_trainings : _trainings;
    }

    inline void removeSavefile() { save->removeSavefile(); }

    Counter() : _trainings(save->read()) {}
    ~Counter() { save->write(_trainings); }
};

#define COUNTER_H
#endif
