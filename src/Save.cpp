#include "Save.h"

/*
	Creates cache directory if it's not exists
*/
Save::Save()
{
	if (!std::filesystem::exists(_cacheDir))
		std::filesystem::create_directory(_cacheDir);
}

/*
	Reads save file

	@return number of trainings
*/
const uint16_t Save::read() const
{
	std::ifstream input(_filename, std::ios::in | std::ios::binary);
	uint16_t trainings { 0 };

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
void Save::write(const uint16_t trainings)
{
	std::ofstream output(_filename, std::ios::out | std::ios::binary);

	if (output.is_open())
	{
		output.write((char*)&trainings, sizeof(trainings));
		output.close();
	}
}
