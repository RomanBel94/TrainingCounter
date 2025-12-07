#pragma once
#ifndef SAVE_H

#include <cstdlib> // getenv()
#include <filesystem>
#include <fstream>

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
#pragma warning(disable : 4996)
    inline static const std::filesystem::path cache_directory{
        std::filesystem::path(std::getenv("WINDIR")) / ".." / "ProgramData" /
        "TrainingCounter"};
#pragma warning(default : 4996)
#else
    // cache directory for linux
    inline static const std::filesystem::path cache_directory{
        std::filesystem::path(std::getenv("HOME")) / ".TrainingCounter"};
#endif // _WIN32

    // savefile name
    inline static const std::filesystem::path savefile_path{cache_directory /
                                                            "save"};

public:
    Save();
    ~Save() = default;

    static void write(uint_t num) noexcept;
    [[nodiscard]] static uint_t read() noexcept;

    static void remove_savefile() noexcept;
    [[nodiscard]] static const decltype(cache_directory)
    get_cache_dirrectory() noexcept
    {
        return cache_directory;
    }
};

/*
    Creates cache directory if it's not exists
*/
template <typename uint_t>
Save<uint_t>::Save()
{
    std::filesystem::create_directory(cache_directory);
}

/*
    Reads save file

    @return number of trainings
*/
template <typename uint_t>
uint_t Save<uint_t>::read() noexcept
{
    std::ifstream input(savefile_path, std::ios::in | std::ios::binary);
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
void Save<uint_t>::write(uint_t num) noexcept
{
    std::ofstream output(savefile_path, std::ios::out | std::ios::binary);

    if (output.is_open())
        output.write(reinterpret_cast<const char*>(&num), sizeof(num));
}

template <typename uint_t>
void Save<uint_t>::remove_savefile() noexcept
{
    std::filesystem::remove(savefile_path);
}

#define SAVE_H
#endif
