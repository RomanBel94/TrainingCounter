#include "AppCore.h"

int AppCore::run()
{
    parser(argc, argv);
    LexerParser::job todo = parser.getJob();
    uint8_t num = parser.getNum();
    message(std::to_string(todo));
    message(std::to_string(num));
	log("tc started");
	message("Remaining trainings: " + std::to_string(save.read()));
	save.write(11);
	return 0;
}
