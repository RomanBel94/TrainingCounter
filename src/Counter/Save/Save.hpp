#pragma once
#ifndef SAVE_H

#include <cstdlib> // getenv()
#include <filesystem>
#include <format>
#include <fstream>
#include <string> // strings

template <typename uint_t>
class Save final
{
private:
    Save(const Save&) = delete;
    Save(Save&&) = delete;
    Save& operator=(const Save&) = delete;
    Save& operator=(Save&&) = delete;

#ifdef _WIN32
    // cache directory for windows
    inline static const std::string m_cache_dir{std::format(
        "{}\\..\\ProgramData\\TrainingCounter\\", getenv("WINDIR"))};
#else
    // cache directory for linux
    inline static const std::string m_cache_dir{
        std::format("{}/.TrainingCounter/", getenv("HOME"))};
#endif // _WIN32

    // savefile name
    inline static const std::string m_filename{
        std::format("{}save", m_cache_dir)};

public:
    Save();
    ~Save() = default;

    static void write(uint_t trainings) noexcept;
    static uint_t read() noexcept;

    static void remove_savefile() noexcept;
    static const auto& get_cache_dir() noexcept { return m_cache_dir; }
};

/*
    Creates cache directory if it's not exists
*/
template <typename uint_t>
Save<uint_t>::Save()
{
    std::filesystem::create_directory(m_cache_dir);
}

/*
    Reads save file

    @return number of trainings
*/
template <typename uint_t>
uint_t Save<uint_t>::read() noexcept
{
    std::ifstream input(m_filename, std::ios::in | std::ios::binary);
    uint_t number{0};

    if (input.is_open())
        input.read(reinterpret_cast<char*>(&number), sizeof(number));

    return number;
}

/*
    Writes given number into save file

    @param number to write
*/
template <typename uint_t>
void Save<uint_t>::write(uint_t trainings) noexcept
{
    std::ofstream output(m_filename, std::ios::out | std::ios::binary);

    if (output.is_open())
        output.write(reinterpret_cast<const char*>(&trainings),
                     sizeof(trainings));
}

template <typename uint_t>
void Save<uint_t>::remove_savefile() noexcept
{
    std::filesystem::remove(m_filename);
}

#define SAVE_H
#endif
