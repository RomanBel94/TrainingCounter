#include "AppCore.h"

int AppCore::run()
{
	log("tc started");
	message("Remaining trainings: " + std::to_string(save.read()));
	save.write(11);
	return 0;
}
