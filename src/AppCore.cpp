#include "AppCore.h"

int AppCore::run()
{
    log("tc started.");
    parser(argc, argv);
    LexerParser::job todo = parser.getJob();
    uint8_t num = parser.getNum();
    
    switch (todo) {
    case LexerParser::job::help:
        {
        message.printHelp();
        break;
        }
    case LexerParser::job::mark:
        {
        message("mark");
        break;
        }
    case LexerParser::job::set:
        {
        message("set");
        message(std::to_string(num));
        break;
        }
    case LexerParser::job::add:
        {
        message("add");
        message(std::to_string(num));
        break;
        }
    case LexerParser::job::show:
        {
        std::string msg = "Remaining trainings: " + std::to_string(save.read());
        log(msg);
        message(msg);
        break;
        }
    default:
        message("unknown task!");
    }
	return 0;
}
