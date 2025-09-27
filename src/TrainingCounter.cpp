#include "TrainingCounter.h"

/*
    Main program function

    @return exit code
*/
int TrainingCounter::run() noexcept
{
    const auto& cli{CLI::CLI::get_instance()};
    cli->add_opt('v', 'm', 's', 'a', 't', 'l', 'h');
    cli->add_long_opt("remove_logfile", "remove_savefile", "remove_cache_dir",
                      "meow", "moo", "version", "help");

    try
    {
        cli->parse_args(argc, argv);
    }
    catch (const std::exception& ex)
    {
        log->write(ex.what(), Logger::NO_LOG);
        _printHelp();
        return EXIT_FAILURE;
    }

    if (cli->tokens().empty())
        _printHelp();

    for (const auto& [task, value] : cli->tokens())
    {
        if (task.size() == 1)
            switch (task[0]) // do job given in argv
            {
            case 'v':
                task_manager->add_task(&TrainingCounter::_printVersion);
                task_manager->add_task(&TrainingCounter::_printVersion);
                task_manager->add_task(&TrainingCounter::_printVersion);
                task_manager->execute_all_tasks();
                break;
            case 'm':
                _markTraining();
                break;
            case 's':
                _setTrainings(value.empty() ? counter->getTrainings()
                                            : std::atoi(value.c_str()));
                break;
            case 'a':
                _addTrainings(value.empty() ? 0 : std::atoi(value.c_str()));
                break;
            case 't':
                _showTrainings();
                break;
            case 'l':
                log->showLog(value.empty() ? 0 : std::atoi(value.c_str()));
                break;
            default:
                _printHelp();
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
            else if (task == "remove_cache_dir")
                _removeCache();
            else if (task == "version")
                _printVersion();
            else
                _printHelp();
        }
    }
    return EXIT_SUCCESS;
}

/*
    Print version of program
*/
void TrainingCounter::_printVersion(
    std::optional<std::size_t> opt_arg) const noexcept
{
    log->write(fmt::format("TrainingCounter {}\nCompiled at {}", VERSION,
                           __TIMESTAMP__),
               Logger::NO_LOG);
}

/*
    Prints help (usage)
*/
void TrainingCounter::_printHelp(
    std::optional<std::size_t> opt_arg) const noexcept
{
    log->write(
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
void TrainingCounter::_markTraining(std::optional<std::size_t> opt_arg) noexcept
{
    if (counter->getTrainings())
    {
        counter->markTraining();
        log->write("Training marked");
    }

    if (!counter->getTrainings())
        log->write("No trainings left", Logger::NO_LOG);
}

/*
    Sets trainings to given num

    @param number to set up
*/
void TrainingCounter::_setTrainings(std::optional<std::size_t> opt_arg)
{
    if (opt_arg.has_value())
        throw std::runtime_error{
            fmt::format("{} {}\n", __PRETTY_FUNCTION__, " no value")};
    counter->setTrainings(opt_arg.value());
    log->write(fmt::format("Set trainings to {}", opt_arg.value()));
}

/*
    Adds given count of trainings

    @param number to add
*/
void TrainingCounter::_addTrainings(std::optional<std::size_t> opt_arg)
{
    if (opt_arg.has_value())
        throw std::runtime_error{
            fmt::format("{} {}\n", __PRETTY_FUNCTION__, " no value")};
    if (counter->getTrainings() + opt_arg.value() < UINT32_MAX)
    {
        counter->addTrainings(opt_arg.value());
        log->write(fmt::format("Added {} trainings", opt_arg.value()));
    }
    else
    {
        throw std::runtime_error(
            fmt::format("Can't add {} trainings", opt_arg.value()));
    }
}

/*
    Removes log file
*/
void TrainingCounter::_removeLogfile(
    std::optional<std::size_t> opt_arg) const noexcept
{
    log->removeLogfile();
    log->write("Log file has been removed", Logger::NO_LOG);
}

void TrainingCounter::_removeSaveFile(
    std::optional<std::size_t> opt_arg) const noexcept
{
    counter->removeSavefile();
    log->write("Savefile has been removed");
}

void TrainingCounter::_removeCache(
    std::optional<std::size_t> opt_arg) const noexcept
{
    _removeSaveFile();
    _removeLogfile();
    std::filesystem::remove_all(log->getCacheDir());
    log->write("Cache directory has been removed");
}

void TrainingCounter::_showTrainings(
    std::optional<std::size_t> opt_arg) const noexcept
{
    log->write(fmt::format("Remaining trainings: {}", counter->getTrainings()),
               Logger::NO_LOG);
}

void TrainingCounter::_drawCat(
    std::optional<std::size_t> opt_arg) const noexcept
{
    log->write("\n"
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

void TrainingCounter::_drawMoo(
    std::optional<std::size_t> opt_arg) const noexcept
{
    log->write("\n"
               "                 (__)\n"
               "          ______~(..)~\n"
               "           ,----\\(oo)\n"
               "          /|____|,'\n"
               "         * /\"\\ /\\\n"
               "wWwWwWwWwWwWwWwWwWwWwWwWwWwWw\n"
               "~~~ Have you mooed today? ~~~\n",
               Logger::NO_LOG);
}
