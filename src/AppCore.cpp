#include "AppCore.h"

int AppCore::run()
{
    parser(argc, argv);
    counter.setTrainings(save.read());

    switch (parser.getJob()) {
    case LexerParser::job::help:
            _printHelp();
            break;
    case LexerParser::job::mark:
            _markTraining();
            break;
    case LexerParser::job::set:
            _setTrainings(parser.getNum());
            break;
    case LexerParser::job::add:
            _addTrainings(parser.getNum());
            break;
    case LexerParser::job::show:
            _showTrainings();
            break;
    }
    
    save.write(counter.getTrainings());
	return 0;
}

void AppCore::_printHelp()
{
    std::string msg =
        "Usage:\n\n"
            "\tTrainingCounter -a <num>\tAdd <num> workouts;\n"
            "\tTrainingCounter -s <num>\tSet <num> workouts;\n"
            "\tTrainingCounter -m\t\tMark completed workout;\n"
            "\tTrainingCounter [-h]\t\tPrint help;\n"
            "\tTrainingCounter -t\t\tShow remaining workouts.\n";
    out(msg);
}

void AppCore::_markTraining()
{
    counter.markTraining();
    out("Workout marked.");
    _showTrainings();
}

void AppCore::_setTrainings(const uint8_t num)
{
   counter.setTrainings(num);
    std::string msg = "Set workouts to " + std::to_string(num) + ".";
    out(msg);
    _showTrainings();
}

void AppCore::_addTrainings(const uint8_t num)
{
    counter.addTrainings(num);
    std::string msg = "Added " + std::to_string(num) + " workouts.";
    out(msg);
    _showTrainings();
}

void AppCore::_showTrainings()
{
    std::string msg = "Remaining workouts: " + std::to_string(counter.getTrainings()) + ".";
    out(msg);
}
