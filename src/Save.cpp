#include "Save.h"

/*
    Creates cache directory if it's not exists
*/
Save::Save()
{
    std::filesystem::create_directory(m_cacheDir);
}

/*
    Reads save file

    @return number of trainings
*/
const uint32_t Save::read() const
{
    std::ifstream input(filename, std::ios::in | std::ios::binary);
    uint32_t trainings { 0 };

    if (input.is_open()) {
        input.read((char*)&trainings, sizeof(trainings));
        input.close();
    }

    return trainings;
}

/*
    Writes given number into save file

    @param number to write
*/
void Save::write(const uint32_t trainings) const
{
    std::ofstream output(filename, std::ios::out | std::ios::binary);

    if (output.is_open())
    {
        output.write((char*)&trainings, sizeof(trainings));
        output.close();
    }
}
