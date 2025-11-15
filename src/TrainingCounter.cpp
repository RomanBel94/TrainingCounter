#include <algorithm>
#include <array>

#include "TrainingCounter.h"
#include "Version.h"
/*
    Ctor
*/
TrainingCounter::TrainingCounter(int argc, char** argv) : argc(argc), argv(argv)
{
    _init_task_table();
    _init_cli_options();
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
            _fill_task_queue(cli->tokens());

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
void TrainingCounter::_init_task_table()
{

    task_table.insert({"v", &TrainingCounter::_printVersion});
    task_table.insert({"version", &TrainingCounter::_printVersion});
    task_table.insert({"h", &TrainingCounter::_printHelp});
    task_table.insert({"help", &TrainingCounter::_printHelp});
    task_table.insert({"m", &TrainingCounter::_markTraining});
    task_table.insert({"s", &TrainingCounter::_setTrainings});
    task_table.insert({"a", &TrainingCounter::_addTrainings});
    task_table.insert({"t", &TrainingCounter::_showTrainings});
    task_table.insert({"T", &TrainingCounter::_showNumTrainings});
    task_table.insert({"l", &TrainingCounter::_showLog});
    task_table.insert({"remove_logfile", &TrainingCounter::_removeLogfile});
    task_table.insert({"remove_savefile", &TrainingCounter::_removeSaveFile});
    task_table.insert({"remove_cache", &TrainingCounter::_removeCache});
    task_table.insert({"meow", &TrainingCounter::_drawCat});
    task_table.insert({"moo", &TrainingCounter::_drawMoo});
}

/*
    Fills CLI with valid options
*/
void TrainingCounter::_init_cli_options()
{
    std::array short_options{'v', 'm', 's', 'a', 't', 'T', 'l', 'h'};
    std::for_each(short_options.begin(), short_options.end(),
                  [this](auto opt) { cli->add_short_option(opt); });
    std::array long_options{"remove_logfile",
                            "remove_savefile",
                            "remove_cache",
                            "meow",
                            "moo",
                            "version",
                            "help"};
    std::for_each(long_options.begin(), long_options.end(),
                  [this](auto opt) { cli->add_long_option(opt); });
}

/*
   Fills task queue
*/
void TrainingCounter::_fill_task_queue(
    const std::list<CLI::CLI::token>& tokens) const noexcept
{
    std::for_each(tokens.begin(), tokens.end(),
                  [this](const auto& token)
                  {
                      if (token.second.empty())
                          task_manager->add_task(task_table.at(token.first));
                      else
                          task_manager->add_task(task_table.at(token.first),
                                                 std::stoi(token.second));
                  });
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
            fmt::format("{} no value\n", __PRETTY_FUNCTION__)};

    char ans{'n'};
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
            fmt::format("{} no value\n", __PRETTY_FUNCTION__)};

    if (counter->getTrainings() + *opt_arg <
        std::numeric_limits<uint32_t>().max())
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
