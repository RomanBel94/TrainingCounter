#include "TrainingCounter.h"

std::shared_ptr<TrainingCounter> TrainingCounter::getInstance(int argc, char** argv) noexcept
{
    static std::shared_ptr<TrainingCounter> app = std::make_unique<TrainingCounter>(argc, argv);
    return app;
}

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
            default:
                _printHelp();
            }
        }
        // write save file
        save->write(counter->getTrainings());
    }
    catch (const std::exception& ex)
    {
        log->out(ex.what(), Logger::NO_LOG);
        exit(-1);
    }
    return 0;
}

/*
    Prints help (usage)
*/
void TrainingCounter::_printHelp() noexcept
{
    log->out("\nUsage:\n\n"
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
    if (num < UINT32_MAX)
    {
        counter->setTrainings(num);
        log->out(fmt::format("Set trainings to {}", num));
    }
    else
    {
        throw std::runtime_error(fmt::format("{} is too large number", num));
    }    
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
void TrainingCounter::_removeLogfile()
{
    log->removeLogfile();
    log->out("Log file has been removed", Logger::NO_LOG);
}

void TrainingCounter::_showTrainings()
{
    log->out(fmt::format("Remaining trainings: {}", counter->getTrainings(), Logger::NO_LOG));
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
