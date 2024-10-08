#include "AppCore.h"

/*
    Main program function

    @return exit code
*/
int AppCore::run()
{
    try
    {   
        parseCommandLine(argc, argv);
        setTrainings(read());
       
        for(char key : getKeys())
        {
            switch (key)// do job given in argv
            {
            case 'v':
                out(std::string("TrainingCounter ") + VERSION, NO_LOG);
                break;
            case 'm':
                _markTraining();
                break;
            case 's':
                _setTrainings(getNum());
                break;
            case 'a':
                _addTrainings(getNum());
                break;
            case 't':
                _showTrainings();
                break;
            case 'r':
                _removeLogfile();
                break;
            case 'l':
                showLog(getNum());
                break;
            default:
                _printHelp();
            }
        }
        // write save file
        write(getTrainings());
    }
    catch (std::exception& ex)
    {
        out(ex.what());
        exit(-1);
    }
    return 0;
}

/*
    Prints help (usage)
*/
void AppCore::_printHelp() noexcept
{
    out("\nUsage:\n\n"
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
        NO_LOG
        );
}

/*
    Marks the completed training
*/
void AppCore::_markTraining()
{
    if (getTrainings() > 0)
    {
        markTraining();
        out("Training marked");
    }
    else
    {
        out("No trainings left", NO_LOG);
    }
}

/*
    Sets trainings to given num

    @param number to set up
*/
void AppCore::_setTrainings(const uint32_t num)
{
    if (num < UINT32_MAX)
    {
        setTrainings(num);
        out("Set trainings to " + std::to_string(num));
    }
    else
    {
        throw std::runtime_error(std::to_string(num) + " is too big number");
    }    
}

/*
    Adds given count of trainings

    @param number to add
*/
void AppCore::_addTrainings(const uint32_t num)
{
    if (getTrainings() + num < UINT32_MAX)
    {
        addTrainings(num);
        out("Added " + std::to_string(num) + " trainings");
    }
    else
    {
        throw std::runtime_error("Can't add " + std::to_string(num) + " trainings");
    }
}

/*
    Removes log file
*/
void AppCore::_removeLogfile()
{
    removeLogfile();
    out("Log file has been removed", NO_LOG);
}
