#include "Save.h"
#include <filesystem>

/*
    Creates cache directory if it's not exists
*/
Save::Save() { std::filesystem::create_directory(cacheDir); }

/*
    Reads save file

    @return number of trainings
*/
const uint32_t Save::read() noexcept
{
    std::ifstream input(filename, std::ios::in | std::ios::binary);
    uint32_t trainings{0};

    if (input.is_open())
    {
        input.read(reinterpret_cast<char*>(&trainings), sizeof(trainings));
        input.close();
    }

    return trainings;
}

/*
    Writes given number into save file

    @param number to write
*/
void Save::write(const uint32_t trainings) noexcept
{
    std::ofstream output(filename, std::ios::out | std::ios::binary);

    if (output.is_open())
    {
        output.write(reinterpret_cast<const char*>(&trainings),
                     sizeof(trainings));
        output.close();
    }
}

void Save::removeSavefile() { std::filesystem::remove(filename); }
