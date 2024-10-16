#pragma once
#ifndef COUNTER_H

#include <cstdint> // uint32_t

class Counter 
{
private:
    uint32_t m_trainings { 0 };    // current value of trainings
public:
    // set <num> of trainings if <num> is greater than 0
    inline void setTrainings(const uint32_t num) noexcept
        { num >= 0 &&  num <= UINT32_MAX ? m_trainings = num : m_trainings = UINT32_MAX; }
    
    // add <num> of trainings if <num> is greater than 0
    inline void addTrainings(const uint32_t num) noexcept
        { num >= 0 && (m_trainings + num) <= UINT32_MAX ? m_trainings += num : m_trainings = UINT32_MAX; }
    
    // returns trainings
    inline const uint32_t getTrainings() const noexcept
        { return m_trainings; }
    
    // decrement trainings by 1 if current number of trainings is greater than 0
    inline void markTraining() noexcept 
        { m_trainings > 0 ? --m_trainings : m_trainings; }

    virtual ~Counter() {};
};

#define COUNTER_H
#endif
