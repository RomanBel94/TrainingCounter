#include "Save.h"

Save::Save()
{
	if (!std::filesystem::exists(dir))
		std::filesystem::create_directory(dir);
}

uint8_t Save::read()
{
	std::ifstream input(file, std::ios::in | std::ios::binary);
	uint8_t trainings { 0 };

 	if (input.is_open()) {
		input.read((char*)&trainings, sizeof(trainings));
		input.close();
	}

	return trainings;
}

void Save::write(uint8_t trainings)
{
	std::ofstream output(file, std::ios::out | std::ios::binary);
	output.write((char*)&trainings, sizeof(trainings));
	output.close();
}
