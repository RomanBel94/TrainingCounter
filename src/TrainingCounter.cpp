#include "TrainingCounter.h"

/*
    Main program function

    @return exit code
*/
int TrainingCounter::run()
{
    try
    {   
        parser->parseCommandLine(argc, argv);
        counter->setTrainings(save->read());
       
        for(const auto& task : parser->getTasks())
        {
            switch (task.job)// do job given in argv
            {
            case Task::jobType::show_version:
                log->out(fmt::format("TrainingCounter {}", VERSION), Logger::NO_LOG);
                break;
            case Task::jobType::mark_training:
                _markTraining();
                break;
            case Task::jobType::set_trainings:
                _setTrainings(task.number);
                break;
            case Task::jobType::add_trainings:
                _addTrainings(task.number);
                break;
            case Task::jobType::show_trainings:
                _showTrainings();
                break;
            case Task::jobType::remove_logfile:
                _removeLogfile();
                break;
            case Task::jobType::show_log:
                log->showLog(task.number);
                break;
            case Task::jobType::draw_cat:
                _drawCat();
                break;
            case Task::jobType::draw_moo:
                _drawMoo();
                break;
            case Task::jobType::show_help:
                _printHelp();
                break;
            case Task::jobType::remove_cache:
                _removeCache();
                break;
            default:
                log->out("Uknown task, use flag -h to see help.", Logger::NO_LOG);
            }
        }
        // write save file
        save->write(counter->getTrainings());
    }
    catch (const std::exception& ex)
    {
        save->write(counter->getTrainings());
        log->out(ex.what(), Logger::NO_LOG);
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}

/*
    Prints help (usage)
*/
void TrainingCounter::_printHelp() noexcept
{
    log->out("\nUsage:\n\n"
            "\tTrainingCounter -h, --help\t\tPrint \"Usage\";\n"
            "\tTrainingCounter -a <num>\t\tAdd <num> trainings;\n"
            "\tTrainingCounter -s <num>\t\tSet <num> trainings;\n"
            "\tTrainingCounter -m \t\t\tMark completed training;\n"
            "\tTrainingCounter -t \t\t\tShow remaining trainings;\n"
            "\tTrainingCounter -v, --version\t\tShow TrainingCounter version;\n"
            "\tTrainingCounter --remove_logfile\tRemove log file;\n"
            "\tTrainingCounter --remove_cache\tRemove cache directory;\n"
            "\tTrainingCounter -l [<num>]\t\tShow <num> last lines of log. If <num> is not given full log will be printed.\n\n\n"
            "Example: TrainingCounter -m -t -l5 --version\n", 
        Logger::NO_LOG
        );
}

/*
    Marks the completed training
*/
void TrainingCounter::_markTraining()
{
    if (counter->getTrainings() > 0)
    {
        counter->markTraining();
        log->out("Training marked");
    }
    else
    {
        log->out("No trainings left", Logger::NO_LOG);
    }
}

/*
    Sets trainings to given num

    @param number to set up
*/
void TrainingCounter::_setTrainings(const uint32_t num)
{
    counter->setTrainings(num);
    log->out(fmt::format("Set trainings to {}", num));
}

/*
    Adds given count of trainings

    @param number to add
*/
void TrainingCounter::_addTrainings(const uint32_t num)
{
    if (counter->getTrainings() + num < UINT32_MAX)
    {
        counter->addTrainings(num);
        log->out(fmt::format("Added {} trainings", num));
    }
    else
    {
        throw std::runtime_error(fmt::format("Can't add {} trainings", num));
    }
}

/*
    Removes log file
*/
void TrainingCounter::_removeLogfile() const
{
    log->removeLogfile();
    log->out("Log file has been removed", Logger::NO_LOG);
}

void TrainingCounter::_removeCache() const
{
    save->removeSavefile();
    log->out("Savefile has been removed");
    _removeLogfile();
    std::filesystem::remove_all(log->getCacheDir());
    log->out("Cache directory has been removed");
}

void TrainingCounter::_showTrainings() const noexcept
{
    log->out(fmt::format("Remaining trainings: {}", counter->getTrainings()), Logger::NO_LOG);
}

void TrainingCounter::_drawCat() const noexcept
{
    log->out(
        "\n"
        "       _\n"
        "       \\`*-.\n"
        "        )  _`-.\n"
        "       .  : `. .\n"
        "       : _   '  \\\n"
        "       ; *` _.   `*-._\n"
        "       `-.-'          `-.\n"
        "         ;       `       `.\n"
        "         :.       .        \\\n"
        "         . \\  .   :   .-'   .\n"
        "         '  `+.;  ;  '      :\n"
        "         :  '  |    ;       ;-.\n"
        "         ; '   : :`-:     _.`* ;\n"
        "[bug] .*' /  .*' ; .*`- +'  `*'\n"
        "      `*-*   `*-*  `*-*'\n\n",
        Logger::NO_LOG);
}

void TrainingCounter::_drawMoo() const noexcept
{
    log->out(
            "\n"
        "                 (__)\n"
        "          ______~(..)~\n"
        "           ,----\\(oo)\n"
        "          /|____|,'\n"
        "         * /\"\\ /\\\n"
        "wWwWwWwWwWwWwWwWwWwWwWwWwWwWw\n"
        "~~~ Have you mooed today? ~~~\n",
        Logger::NO_LOG);
}
