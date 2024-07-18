#include "AppCore.h"
#include "OutputManager.h"

AppCore::AppCore(int argc, char** argv) noexcept
{ 
    parser(argc, argv);    // read command arguments
    counter.setTrainings(save.read());    // read save file and set trainings
}

// main program function
int AppCore::run() noexcept
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
    case LexerParser::remove_log:
        _removeLogfile(); break;
    case LexerParser::show_log:
        _showLog(); break;

    default:
        _showUndefined();
    }

    // write save file
    save.write(counter.getTrainings());
	return 0;
}

// print help (usage)
void AppCore::_printHelp() noexcept
{
    out("\nUsage:\n\n"
            "\tTrainingCounter -h, -H\t\tPrint \"Usage\";\n"
            "\tTrainingCounter -a, -A <num>\tAdd <num> trainings;\n"
            "\tTrainingCounter -s, -S <num>\tSet <num> trainings;\n"
            "\tTrainingCounter -m, -M\t\tMark completed training;\n"
            "\tTrainingCounter -t, -T\t\tShow remaining trainings;\n"
            "\tTrainingCounter -v, -V\t\tShow TrainingCounter version;\n"
            "\tTrainingCounter -r, -R\t\tRemove log file;\n"
            "\tTrainingCounter -l, -L\t\tShow log.\n", 
        OutputManager::cyan,
        false);
}

// mark completed training
void AppCore::_markTraining() noexcept
{
    counter.markTraining();
    if (counter.getTrainings())
        out("Training marked.", OutputManager::magenta);
}

// set trainings to given num
void AppCore::_setTrainings(const uint16_t num) noexcept
{
    uint16_t toSet = num > _UI8_MAX ? _UI8_MAX : num;
    counter.setTrainings(toSet);
    out("Set trainings to " + std::to_string(toSet) + ".", OutputManager::yellow);
}

// add given count of trainings
void AppCore::_addTrainings(const uint16_t num) noexcept
{
    uint16_t toAdd = num > _UI8_MAX ? _UI8_MAX : num;
    counter.addTrainings(toAdd);
    out("Added " + std::to_string(toAdd) + " trainings.", OutputManager::green);
}

// print remaining trainings
void AppCore::_showTrainings() noexcept
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

// remove log file
void AppCore::_removeLogfile() noexcept
{
    if (out.removeLogfile())
        out("Log file has been removed!", OutputManager::yellow, false);
    else
        out("\a[ERROR] Failed to remove log file!", OutputManager::red, false);
}
