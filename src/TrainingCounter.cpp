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
        task_manager->add_task(&TrainingCounter::_printHelp);

    for (const auto& [task, value] : cli->tokens())
    {
        if (task == "v" || task == "version")
            task_manager->add_task(&TrainingCounter::_printVersion);
        else if (task == "m")
            task_manager->add_task(&TrainingCounter::_markTraining);
        else if (task == "s")
            task_manager->add_task(&TrainingCounter::_setTrainings,
                                   value.empty() ? counter->getTrainings()
                                                 : std::stoi(value));
        else if (task == "a")
            task_manager->add_task(&TrainingCounter::_addTrainings,
                                   value.empty() ? 0 : std::stoi(value));
        else if (task == "t")
            task_manager->add_task(&TrainingCounter::_showTrainings);
        else if (task == "l")
            task_manager->add_task(&TrainingCounter::_showLog,
                                   value.empty() ? 0 : std::stoi(value));
        else if (task == "remove_logfile")
            task_manager->add_task(&TrainingCounter::_removeLogfile);
        else if (task == "remove_savefile")
            task_manager->add_task(&TrainingCounter::_removeSaveFile);
        else if (task == "meow")
            task_manager->add_task(&TrainingCounter::_drawCat);
        else if (task == "moo")
            task_manager->add_task(&TrainingCounter::_drawMoo);
        else if (task == "remove_cache_dir")
            task_manager->add_task(&TrainingCounter::_removeCache);
        else
            task_manager->add_task(&TrainingCounter::_printHelp);
    }

    task_manager->execute_all_tasks();
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
    if (!opt_arg.has_value())
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
    if (!opt_arg.has_value())
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

void TrainingCounter::_showLog(std::optional<std::size_t> opt_arg) const
{
    if (!opt_arg.has_value())
        throw std::runtime_error{
            fmt::format("{} {}\n", __PRETTY_FUNCTION__, " no value")};

    log->showLog(opt_arg.value());
}
