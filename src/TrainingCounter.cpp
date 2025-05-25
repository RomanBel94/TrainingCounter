#include "TrainingCounter.h"

/*
    Main program function

    @return exit code
*/
int TrainingCounter::run() noexcept
{
    const auto& cli{CLI::CLI::get_instance()};
    cli->add_opt('v', 'm', 's', 'a', 't', 'l', 'h');
    cli->add_long_opt("remove_logfile", "remove_savefile", "remove_cache",
                      "meow", "moo", "version", "help");

    try
    {
        cli->parse_args(argc, argv);

        for (const auto& [task, value] : cli->tokens())
        {
            if (task.size() == 1)
                switch (task[0]) // do job given in argv
                {
                case 'v':
                    log->out(fmt::format("TrainingCounter {}\nCompiled at {}",
                                         VERSION, __TIMESTAMP__),
                             Logger::NO_LOG);
                    break;
                case 'm':
                    _markTraining();
                    break;
                case 's':
                    _setTrainings(value.empty() ? counter->getTrainings()
                                                : std::atoi(value.c_str()));
                    break;
                case 'a':
                    _addTrainings(value.empty() ? 0 : atoi(value.c_str()));
                    break;
                case 't':
                    _showTrainings();
                    break;
                case 'l':
                    log->showLog(value.empty() ? 0 : std::atoi(value.c_str()));
                    break;
                case 'h':
                    _printHelp();
                    break;
                }
            else
            {
                if (task == "remove_logfile")
                    _removeLogfile();
                else if (task == "remove_savefile")
                    _removeSaveFile();
                else if (task == "meow")
                    _drawCat();
                else if (task == "moo")
                    _drawMoo();
                else if (task == "remove_cache")
                    _removeCache();
                else if (task == "help")
                    _printHelp();
            }
        }
    }
    catch (const std::exception& ex)
    {
        log->out(ex.what(), Logger::NO_LOG);
        _printHelp();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/*
    Prints help (usage)
*/
void TrainingCounter::_printHelp() const noexcept
{
    log->out(
        "\nUsage:\n\n"
        "\tTrainingCounter -h, --help\t\tPrint \"Usage\";\n"
        "\tTrainingCounter -a <num>\t\tAdd <num> trainings;\n"
        "\tTrainingCounter -s <num>\t\tSet <num> trainings;\n"
        "\tTrainingCounter -m \t\t\tMark completed training;\n"
        "\tTrainingCounter -t \t\t\tShow remaining trainings;\n"
        "\tTrainingCounter -v, --version\t\tShow TrainingCounter version;\n"
        "\tTrainingCounter -l [<num>]\t\tShow <num> last lines of log.\n"
        "\t\t\t\t\t\tIf <num> is not given full log will be printed;\n"
        "\tTrainingCounter --remove_logfile\tRemove log file;\n"
        "\tTrainingCounter --remove_savefile\tRemove save file;\n"
        "\tTrainingCounter --remove_cache\t\tRemove cache directory.\n\n"
        "Example: TrainingCounter -m -t -l5 --version\n",
        Logger::NO_LOG);
}

/*
    Marks the completed training
*/
void TrainingCounter::_markTraining() noexcept
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
void TrainingCounter::_removeLogfile() const noexcept
{
    log->removeLogfile();
    log->out("Log file has been removed", Logger::NO_LOG);
}

void TrainingCounter::_removeSaveFile() const noexcept
{
    counter->removeSavefile();
    log->out("Savefile has been removed");
}

void TrainingCounter::_removeCache() const noexcept
{
    _removeSaveFile();
    _removeLogfile();
    std::filesystem::remove_all(log->getCacheDir());
    log->out("Cache directory has been removed");
}

void TrainingCounter::_showTrainings() const noexcept
{
    log->out(fmt::format("Remaining trainings: {}", counter->getTrainings()),
             Logger::NO_LOG);
}

void TrainingCounter::_drawCat() const noexcept
{
    log->out("\n"
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
    log->out("\n"
             "                 (__)\n"
             "          ______~(..)~\n"
             "           ,----\\(oo)\n"
             "          /|____|,'\n"
             "         * /\"\\ /\\\n"
             "wWwWwWwWwWwWwWwWwWwWwWwWwWwWw\n"
             "~~~ Have you mooed today? ~~~\n",
             Logger::NO_LOG);
}
