#include "TrainingCounter.h"

/*
    Ctor
*/
TrainingCounter::TrainingCounter(int argc, char** argv) : argc(argc), argv(argv)
{
    _init_task_set();

    cli->add_opt('v', 'm', 's', 'a', 't', 'T', 'l', 'h');
    cli->add_long_opt("remove_logfile", "remove_savefile", "remove_cache",
                      "meow", "moo", "version", "help");
}

/*
    Main program function

    @return exit code
*/
int TrainingCounter::run() noexcept
{
    try
    {
        cli->parse_args(argc, argv);

        if (cli->tokens().empty())
            task_manager->add_task(&TrainingCounter::_printPrompt);
        else
            _fill_task_queue(*cli);

        task_manager->execute_all_tasks();
    }
    catch (const std::exception& ex)
    {
        log->write(ex.what(), Logger::NO_LOG);
        _printPrompt();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
   Fills task hashmap with class method pointers
*/
void TrainingCounter::_init_task_set()
{

    task_set.insert({"v", &TrainingCounter::_printVersion});
    task_set.insert({"version", &TrainingCounter::_printVersion});
    task_set.insert({"h", &TrainingCounter::_printHelp});
    task_set.insert({"help", &TrainingCounter::_printHelp});
    task_set.insert({"m", &TrainingCounter::_markTraining});
    task_set.insert({"s", &TrainingCounter::_setTrainings});
    task_set.insert({"a", &TrainingCounter::_addTrainings});
    task_set.insert({"t", &TrainingCounter::_showTrainings});
    task_set.insert({"T", &TrainingCounter::_showNumTrainings});
    task_set.insert({"l", &TrainingCounter::_showLog});
    task_set.insert({"remove_logfile", &TrainingCounter::_removeLogfile});
    task_set.insert({"remove_savefile", &TrainingCounter::_removeSaveFile});
    task_set.insert({"remove_cache", &TrainingCounter::_removeCache});
    task_set.insert({"meow", &TrainingCounter::_drawCat});
    task_set.insert({"moo", &TrainingCounter::_drawMoo});
}

/*
   Fills task queue
*/
void TrainingCounter::_fill_task_queue(const CLI::CLI& cli) const noexcept
{
    for (const auto& [task, value] : cli.tokens())
    {
        if (value.empty())
            task_manager->add_task(task_set.at(task));
        else
            task_manager->add_task(task_set.at(task), std::stoi(value));
    }
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
        "\tTrainingCounter -t \t\t\tShow remaining trainings (only number);\n"
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
    Print short prompt
*/
void TrainingCounter::_printPrompt(
    std::optional<std::size_t> opt_arg) const noexcept
{
    log->write("Type \"TrainingCounter -h or --help\" to see instructions",
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
    if (!opt_arg)
        throw std::runtime_error{
            fmt::format("{} {}\n", __PRETTY_FUNCTION__, "no value")};

    char ans;
    if (*opt_arg < counter->getTrainings())
    {
        log->write(
            "You are trying to set trainings to lower amount than you have.",
            Logger::NO_LOG);
        do
        {
            log->write("\aAre you sure? [y/n]:", Logger::NO_LOG);
            std::cin >> ans;
        } while (std::tolower(ans) != 'n' && std::tolower(ans) != 'y');
    }

    if (ans == 'n')
    {
        log->write("Setting trainings canceled", Logger::NO_LOG);
        return;
    }
    counter->setTrainings(*opt_arg);
    log->write(fmt::format("Set trainings to {}", *opt_arg));
}

/*
    Adds given count of trainings

    @param number to add
*/
void TrainingCounter::_addTrainings(std::optional<std::size_t> opt_arg)
{
    if (!opt_arg)
        throw std::runtime_error{
            fmt::format("{} {}\n", __PRETTY_FUNCTION__, "no value")};

    if (counter->getTrainings() + *opt_arg < UINT32_MAX)
    {
        counter->addTrainings(opt_arg.value());
        log->write(fmt::format("Added {} trainings", *opt_arg));
    }
    else
        throw std::runtime_error(
            fmt::format("Can't add {} trainings", *opt_arg));
}

/*
    Removes log file
*/
void TrainingCounter::_removeLogfile(
    std::optional<std::size_t> opt_arg) const noexcept
{
    log->removeLogfile();
    log->write("Log file removed", Logger::NO_LOG);
}

void TrainingCounter::_removeSaveFile(
    std::optional<std::size_t> opt_arg) const noexcept
{
    counter->removeSavefile();
    log->write("Savefile removed");
}

void TrainingCounter::_removeCache(
    std::optional<std::size_t> opt_arg) const noexcept
{
    _removeSaveFile();
    _removeLogfile();
    std::filesystem::remove_all(log->getCacheDir());
    log->write("Cache directory removed");
}

void TrainingCounter::_showTrainings(
    std::optional<std::size_t> opt_arg) const noexcept
{
    log->write(fmt::format("Remaining trainings: {}", counter->getTrainings()),
               Logger::NO_LOG);
}

void TrainingCounter::_showNumTrainings(
    std::optional<std::size_t> opt_arg) const noexcept
{
    log->write(fmt::format("{}", counter->getTrainings()), Logger::NO_LOG);
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
    log->showLog(opt_arg ? *opt_arg : 0);
}
