#include "AppCore.h"
#include "OutputManager.h"

/*
    Constructor.
    Starts command arguments parsing, reads save file and sets counter.

    @param argc from main
    @param argv from main
*/
AppCore::AppCore(int argc, char** argv) noexcept
{ 
    try
    {
        _parser(argc, argv);
    }
    catch (std::exception& ex)
    {
        _out(OutputManager::error, ex.what());
        exit(-1);
    }
    _counter.setTrainings(_save.read());
}

/*
    Main program function
*/
int AppCore::run() noexcept
{
    for(char key : _parser.getKeys())
        switch (key)// do job given in argv
        {
        case 'h':
            _printHelp(); break;
        case 'v':
            _out(OutputManager::message, std::string("TrainingCounter ") + VERSION, OutputManager::white, false); break;
        case 'm':
            _markTraining(); break;
        case 's':
            _setTrainings(_parser.getNum()); break;
        case 'a':
            _addTrainings(_parser.getNum()); break;
        case 't':
            _showTrainings(); break;
        case 'r':
            _removeLogfile(); break;
        case 'l':
            _out.showLog(_parser.getNum()); break;
        }

    // write save file
    _save.write(_counter.getTrainings());
	return 0;
}

/*
    Prints help (usage)
*/
void AppCore::_printHelp() noexcept
{
    _out(OutputManager::message,
        "\nUsage:\n\n"
            "\tTrainingCounter -h \t\tPrint \"Usage\";\n"
            "\tTrainingCounter -a <num>\tAdd <num> trainings;\n"
            "\tTrainingCounter -s <num>\tSet <num> trainings;\n"
            "\tTrainingCounter -m \t\tMark completed training;\n"
            "\tTrainingCounter -t \t\tShow remaining trainings;\n"
            "\tTrainingCounter -v \t\tShow TrainingCounter version;\n"
            "\tTrainingCounter -r \t\tRemove log file;\n"
            "\tTrainingCounter -l [<num>]\tShow <num> last lines of log. If <num> is not given full log will be printed.\n\n\n"
            "You can pass more than one key, but all keys must be unique.\n\n"
            "Example: TrainingCounter -m -t -l5\n", 
        OutputManager::cyan,
        false);
}
/*
    Marks the completed training
*/
void AppCore::_markTraining() noexcept
{
    _counter.markTraining();
    if (_counter.getTrainings() > 0)
    {
        _out(OutputManager::message, "Training marked.", OutputManager::magenta);
    }
    else
    {
        _out(OutputManager::message, "No trainings left!", OutputManager::red, false);
    }
}

/*
    Sets trainings to given num
*/
void AppCore::_setTrainings(const uint32_t num) noexcept
{
    uint32_t toSet = num > UINT32_MAX ? UINT32_MAX : num;
    _counter.setTrainings(toSet);
    _out(OutputManager::message, "Set trainings to " + std::to_string(toSet) + ".", OutputManager::yellow);
}

/*
    Adds given count of trainings
*/
void AppCore::_addTrainings(const uint32_t num) noexcept
{
    uint32_t toAdd = num > UINT32_MAX ? UINT32_MAX : num;
    _counter.addTrainings(toAdd);
    _out(OutputManager::message, "Added " + std::to_string(toAdd) + " trainings.", OutputManager::green);
}

/*
    Prints remaining trainings
*/
void AppCore::_showTrainings() noexcept
{
    auto color = OutputManager::white;

    if (_counter.getTrainings() == 0)
    {
        color = OutputManager::red;
    }
    else if (_counter.getTrainings() > 3)
    {
        color = OutputManager::green;
    }
    else
    {
        color = OutputManager::yellow;
    }

    _out(OutputManager::message, "Remaining trainings: " + std::to_string(_counter.getTrainings()) + ".", color);
}

/*
    Removes log file
*/
void AppCore::_removeLogfile()
{
    _out.removeLogfile();
    _out(OutputManager::message, "Log file has been removed!", OutputManager::yellow, false);
}
