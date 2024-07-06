#include "AppCore.h"

int AppCore::run()
{
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
    out("\nUsage:\n\n"
            "\tTrainingCounter [-h]\t\tPrint \"Usage\";\n"
            "\tTrainingCounter -a <num>\tAdd <num> trainings;\n"
            "\tTrainingCounter -s <num>\tSet <num> trainings;\n"
            "\tTrainingCounter -m\t\tMark completed training;\n"
            "\tTrainingCounter -t\t\tShow remaining trainings.\n");
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
    out("Set workouts to " + std::to_string(num) + ".");
    _showTrainings();
}

void AppCore::_addTrainings(const uint8_t num)
{
    counter.addTrainings(num);
    out("Added " + std::to_string(num) + " workouts.");
    _showTrainings();
}

void AppCore::_showTrainings()
{
    out("Remaining workouts: " + std::to_string(counter.getTrainings()) + ".");
}
