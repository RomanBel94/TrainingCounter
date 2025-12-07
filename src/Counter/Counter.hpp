#pragma once
#ifndef COUNTER_H

#include <limits>
#include <memory>

#include "Save/Save.hpp"

template <typename uint_t = std::size_t>
class Counter final
{
private:
    std::unique_ptr<Save<uint_t>> m_save = std::make_unique<Save<uint_t>>();
    uint_t m_count{0}; // current value of trainings

    inline static constexpr uint_t max = std::numeric_limits<uint_t>().max();
    inline static constexpr uint_t min = std::numeric_limits<uint_t>().min();

public:
    // set <num> of trainings if <num> is greater than 0
    void set(uint_t num) noexcept;

    // add <num> of trainings if <num> is greater than 0
    void add(uint_t num) noexcept;

    // returns trainings
    uint_t get() const noexcept { return m_count; }

    // decrement trainings by 1 if current number of trainings is greater than 0
    void count() noexcept;

    // removes save file
    void remove_savefile() const noexcept;

    // ctor
    Counter();

    // dtor
    ~Counter();
};

template <typename uint_t>
void Counter<uint_t>::set(uint_t num) noexcept
{
    num <= max ? m_count = num : m_count = max;
}

template <typename uint_t>
void Counter<uint_t>::add(uint_t num) noexcept
{
    m_count + num <= max ? m_count += num : m_count = max;
}

template <typename uint_t>
void Counter<uint_t>::count() noexcept
{
    m_count > 0 ? --m_count : m_count;
}

template <typename uint_t>
void Counter<uint_t>::remove_savefile() const noexcept
{
    m_save->remove_savefile();
}

template <typename uint_t>
Counter<uint_t>::Counter() : m_count(m_save->read())
{
}

template <typename uint_t>
Counter<uint_t>::~Counter()
{
    m_save->write(m_count);
}

#define COUNTER_H
#endif
