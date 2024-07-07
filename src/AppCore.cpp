#include "AppCore.h"

AppCore::AppCore(int argc, char** argv)
{ 
    parser(argc, argv);    // read command arguments
    counter.setTrainings(save.read());    // read save file and set trainings
}

// main program function
int AppCore::run()
{
    switch (parser.getJob())    // do job given in argv
    {
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
    
    save.write(counter.getTrainings());    // write save file
	return 0;
}

// print help (usage)
void AppCore::_printHelp()
{
    out("\nUsage:\n\n"
            "\tTrainingCounter [-h]\t\tPrint \"Usage\";\n"
            "\tTrainingCounter -a <num>\tAdd <num> trainings;\n"
            "\tTrainingCounter -s <num>\tSet <num> trainings;\n"
            "\tTrainingCounter -m\t\tMark completed training;\n"
            "\tTrainingCounter -t\t\tShow remaining trainings.\n");
}

// mark completed training
void AppCore::_markTraining()
{
    counter.markTraining();
    out("Workout marked.");
    _showTrainings();
}

// set trainings to given num
void AppCore::_setTrainings(const uint8_t num)
{
    counter.setTrainings(num);
    out("Set workouts to " + std::to_string(num) + ".");
    _showTrainings();
}

// add given count of trainings
void AppCore::_addTrainings(const uint8_t num)
{
    counter.addTrainings(num);
    out("Added " + std::to_string(num) + " workouts.");
    _showTrainings();
}

// print renaining trainings
void AppCore::_showTrainings()
{
    out("Remaining workouts: " + std::to_string(counter.getTrainings()) + ".");
}
