#include "Save.h"

// creates cache directory if it's not exists
Save::Save()
{
	if (!std::filesystem::exists(dir))
		std::filesystem::create_directory(dir);
}

// read save file
const uint16_t Save::read() const
{
	std::ifstream input(filename, std::ios::in | std::ios::binary);
	uint16_t trainings { 0 };

 	if (input.is_open()) {
		input.read((char*)&trainings, sizeof(trainings));
		input.close();
	}

	return trainings;
}

// write save file
void Save::write(const uint16_t trainings)
{
	std::ofstream output(filename, std::ios::out | std::ios::binary);

	if (output.is_open())
	{
		output.write((char*)&trainings, sizeof(trainings));
		output.close();
	}
}
