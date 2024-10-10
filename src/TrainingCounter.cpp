#include "AppCore.h"

int main(int argc, char* argv[])
{
	return AppCore::getInstance(argc, argv).run(); // run application
}
