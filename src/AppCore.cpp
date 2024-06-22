#include "AppCore.h"

int AppCore::run()
{
    log("tc started.");
    parser(argc, argv);
    LexerParser::job todo = parser.getJob();
    uint8_t num = parser.getNum();
    counter.setTrainings(save.read());

    switch (todo) {
    case LexerParser::job::help:
        {
        log("printed \"help\"");
        message.printHelp();
        break;
        }
    case LexerParser::job::mark:
        {
        counter.markTraining();
        std::string msg = 
            "Workout marked. Remaining workouts: " + std::to_string(counter.getTrainings());
        log(msg);
        message(msg);
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
        std::string msg = "Remaining workouts: " + std::to_string(counter.getTrainings());
        log(msg);
        message(msg);
        break;
        }
    }

    log("tc stopped");
    save.write(counter.getTrainings());
	return 0;
}
