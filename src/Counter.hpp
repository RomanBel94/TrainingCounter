#pragma once
#ifndef COUNTER_H

#include <cstdint>
#include <limits>
#include <memory>

#include "Save.h"

class Counter final
{
private:
    using counter_t = uint32_t;

    std::unique_ptr<Save> _save = std::make_unique<Save>();
    uint32_t _trainings{0}; // current value of trainings
public:
    // set <num> of trainings if <num> is greater than 0
    void setTrainings(counter_t num) noexcept
    {
        num <= std::numeric_limits<counter_t>().max()
            ? _trainings = num
            : _trainings = std::numeric_limits<counter_t>().max();
    }

    // add <num> of trainings if <num> is greater than 0
    void addTrainings(counter_t num) noexcept
    {
        _trainings + num <= std::numeric_limits<counter_t>().max()
            ? _trainings += num
            : _trainings = std::numeric_limits<counter_t>().max();
    }

    // returns trainings
    counter_t getTrainings() const noexcept { return _trainings; }

    // decrement trainings by 1 if current number of trainings is greater than 0
    void decreaseTraining() noexcept
    {
        _trainings > 0 ? --_trainings : _trainings;
    }

    // removes save file
    void removeSavefile() { _save->removeSavefile(); }

    // ctor
    Counter() : _trainings(_save->read()) {}

    // dtor
    ~Counter() { _save->write(_trainings); }
};

#define COUNTER_H
#endif
