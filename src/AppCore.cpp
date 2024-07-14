#include "AppCore.h"
#include "LexerParser.h"
#include "OutputManager.h"

AppCore::AppCore(int argc, char** argv)
{ 
    parser(argc, argv);    // read command arguments
    counter.setTrainings(save.read());    // read save file and set trainings
}

// main program function
int AppCore::run()
{
    switch (parser.getTask())    // do job given in argv
    {
    case LexerParser::help:
        _printHelp(); break;
    case LexerParser::version:
        _printVersion(); break;
    case LexerParser::mark:
        _markTraining(); break;
    case LexerParser::set:
        _setTrainings(parser.getNum()); break;
    case LexerParser::add:
        _addTrainings(parser.getNum()); break;
    case LexerParser::show:
        _showTrainings(); break;
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
            "\tTrainingCounter -t\t\tShow remaining trainings;\n"
            "\tTrainingCounter -v\t\tShow TrainingCounter version.\n", 
        OutputManager::cyan,
        false);
}

// mark completed training
void AppCore::_markTraining()
{
    counter.markTraining();
    if (counter.getTrainings())
        out("Training marked.", OutputManager::magenta);
}

// set trainings to given num
void AppCore::_setTrainings(const uint8_t num)
{
    counter.setTrainings(num);
    out("Set trainings to " + std::to_string(num) + ".", OutputManager::yellow);
}

// add given count of trainings
void AppCore::_addTrainings(const uint8_t num)
{
    counter.addTrainings(num);
    out("Added " + std::to_string(num) + " trainings.", OutputManager::green);
}

void AppCore::_printVersion()
{
        out("TrainingCounter v-1.2.0", OutputManager::white, false);
}

// print renaining trainings
void AppCore::_showTrainings()
{
    auto color = OutputManager::white;

    if (!counter.getTrainings())
        color = OutputManager::red;
    else if (counter.getTrainings() > 3)
        color = OutputManager::green;
    else
        color = OutputManager::yellow;

    out("Remaining trainings: " + std::to_string(counter.getTrainings()) + ".", color);
}
