#include "Save.h"

uint8_t Save::read()
{
	std::string dir = getenv("HOME"); dir += "/.tc/";
	std::string path = dir + "save.sav";

	if (!std::filesystem::exists(dir));
		std::filesystem::create_directory(dir);

	std::ifstream input(path, std::ios::in | std::ios::binary);

 	if (!input)
    {
		std::ofstream output(path, std::ios::out | std::ios::binary);
		output.write(0, sizeof(uint8_t));
		output.close();
		return 0;
	} 
	else 
	{
	uint8_t trainings;
	input.read((char*)&trainings, sizeof(trainings));
	input.close();
	return trainings;
	}
}

void Save::write(uint8_t trainings)
{
    std::string dir = getenv("HOME"); dir += "/.tc/";
    std::string path = dir + "save.sav";

    if (!std::filesystem::exists(dir));        
        std::filesystem::create_directory(dir);
	
	std::ofstream output(path, std::ios::out | std::ios::binary);
	output.write((char*)&trainings, sizeof(trainings));
}
