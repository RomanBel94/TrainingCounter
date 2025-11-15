#pragma once
#ifndef COUNTER_H

#include <cstdint>
#include <limits>
#include <memory>

#include "Save.h"

class Counter final
{
private:
    std::unique_ptr<Save> _save = std::make_unique<Save>();
    uint32_t _trainings{0}; // current value of trainings
public:
    // set <num> of trainings if <num> is greater than 0
    inline void setTrainings(const uint32_t num) noexcept
    {
        num <= std::numeric_limits<uint32_t>().max()
            ? _trainings = num
            : _trainings = std::numeric_limits<uint32_t>().max();
    }

    // add <num> of trainings if <num> is greater than 0
    inline void addTrainings(const uint32_t num) noexcept
    {
        _trainings + num <= std::numeric_limits<uint32_t>().max()
            ? _trainings += num
            : _trainings = std::numeric_limits<uint32_t>().max();
    }

    // returns trainings
    inline const uint32_t getTrainings() const noexcept { return _trainings; }

    // decrement trainings by 1 if current number of trainings is greater than 0
    inline void markTraining() noexcept
    {
        _trainings > 0 ? --_trainings : _trainings;
    }

    inline void removeSavefile() { _save->removeSavefile(); }

    Counter() : _trainings(_save->read()) {}
    ~Counter() { _save->write(_trainings); }
};

#define COUNTER_H
#endif
