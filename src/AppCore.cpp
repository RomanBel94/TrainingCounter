#include "AppCore.h"

int AppCore::run()
{
    parser(argc, argv);
    LexerParser::job todo = parser.getJob();
    uint8_t num = parser.getNum();
    counter.setTrainings(save.read());

    switch (todo) {
    case LexerParser::job::help:
        {
            _printHelp();
            break;
        }
    case LexerParser::job::mark:
        {
            _markTraining();
            break;
        }
    case LexerParser::job::set:
        {
            _setTrainings(num);
            break;
        }
    case LexerParser::job::add:
        {
            _addTrainings(num);
            break;
        }
    case LexerParser::job::show:
        {
            _showTrainings();
            break;
        }
    }

    save.write(counter.getTrainings());
	return 0;
}

void AppCore::_printHelp()
{
    std::string msg =
        "Usage:\n\n"
            "\ttc -a <num>\tAdd <num> workouts;\n"
            "\ttc -s <num>\tSet <num> workouts;\n"
            "\ttc -m\t\tMark completed workout;\n"
            "\ttc [-h]\t\tPrint help;\n"
            "\ttc -w\t\tShow remaining workouts.\n";

    log("printed \"help\"");
    message(msg);
}

void AppCore::_markTraining()
{
    counter.markTraining();
    std::string msg = "Workout marked.";
    log(msg);
    message(msg);
    _showTrainings();
}

void AppCore::_setTrainings(uint8_t num)
{
   counter.setTrainings(num);
    std::string msg = "Set workouts to " + std::to_string(num) + ".";
    log(msg);
    message(msg);
    _showTrainings();
}

void AppCore::_addTrainings(uint8_t num)
{
    counter.addTrainings(num);
    std::string msg = "Added " + std::to_string(num) + " workouts.";
    log(msg);
    message(msg);
    _showTrainings();
}

void AppCore::_showTrainings()
{
    std::string msg = "Remaining workouts: " + std::to_string(counter.getTrainings()) + ".";
    log(msg);
    message(msg);
}
