#include <algorithm>
#include <array>

#include "Logger/Logger.h"
#include "TrainingCounter.h"
#include "Version/Version.h"
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
        m_cli->parse_args(argc, argv);

        if (m_cli->tokens().empty())
            m_task_manager->add_task(&TrainingCounter::_printPrompt);
        else
            _fill_task_queue(m_cli->tokens());

        m_task_manager->execute_all_tasks();
    }
    catch (const std::exception& ex)
    {
        Logger::write(ex.what());
        _printPrompt();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

/*
   Fills task hashmap with class method pointers
*/
void TrainingCounter::_init_task_table() noexcept
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
void TrainingCounter::_init_cli_options() noexcept
{
    std::array short_options{'v', 'm', 's', 'a', 't', 'T', 'l', 'h'};
    std::ranges::for_each(short_options,
                          [this](auto opt) { m_cli->add_short_option(opt); });

    std::array long_options{"remove_logfile",
                            "remove_savefile",
                            "remove_cache",
                            "meow",
                            "moo",
                            "version",
                            "help"};
    std::ranges::for_each(long_options,
                          [this](auto opt) { m_cli->add_long_option(opt); });
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
                          m_task_manager->add_task(task_table.at(token.first));
                      else
                          m_task_manager->add_task(task_table.at(token.first),
                                                   std::stoi(token.second));
                  });
}
/*
    Print version of program
*/
void TrainingCounter::_printVersion(
    std::optional<counter_t> opt_arg) const noexcept
{
    Logger::write(std::format("TrainingCounter {}\nCompiled at {}", VERSION,
                              __TIMESTAMP__));
}

/*
    Prints help (usage)
*/
void TrainingCounter::_printHelp(
    std::optional<counter_t> opt_arg) const noexcept
{
    Logger::write(
        "\nUsage:\n\n"
        "\tTrainingCounter -h, --help\t\tPrint \"Usage\";\n"
        "\tTrainingCounter -a <num>\t\tAdd <num> trainings;\n"
        "\tTrainingCounter -s <num>\t\tSet <num> trainings;\n"
        "\tTrainingCounter -m \t\t\tMark completed training;\n"
        "\tTrainingCounter -t \t\t\tShow remaining trainings;\n"
        "\tTrainingCounter -T \t\t\tShow remaining trainings (only number);\n"
        "\tTrainingCounter -v, --version\t\tShow TrainingCounter version;\n"
        "\tTrainingCounter -l [<num>]\t\tShow <num> last lines of log.\n"
        "\t\t\t\t\t\tIf <num> is not given full log will be printed;\n"
        "\tTrainingCounter --remove_logfile\tRemove log file;\n"
        "\tTrainingCounter --remove_savefile\tRemove save file;\n"
        "\tTrainingCounter --remove_cache\t\tRemove cache directory.\n\n"
        "Example: TrainingCounter -m -t -l5 --version\n");
}

/*
    Print short prompt
*/
void TrainingCounter::_printPrompt(
    std::optional<counter_t> opt_arg) const noexcept
{
    Logger::write("Type \"TrainingCounter -h or --help\" to see instructions");
}

/*
    Marks the completed training
*/
void TrainingCounter::_markTraining(std::optional<counter_t> opt_arg) noexcept
{
    if (m_counter->get())
    {
        m_counter->count();
        Logger::write("Training marked", Logger::LOGFILE);
    }

    if (!m_counter->get())
        // red color of message
        Logger::write("\x1b[1;31mNo trainings left\x1b[0m");
}

/*
    Sets trainings to given num

    @param number to set up
*/
void TrainingCounter::_setTrainings(std::optional<counter_t> opt_arg) noexcept
{
    if (!opt_arg)
    {
        Logger::write(std::format("{} no value\n", __PRETTY_FUNCTION__));
        return;
    }

    char ans{};
    if (*opt_arg < m_counter->get())
    {
        Logger::write(
            "You are trying to set trainings to lower amount than you have.");
        do
        {
            Logger::write("\aAre you sure? [y/n]:");
            std::cin >> ans;
        } while (std::tolower(ans) != 'n' && std::tolower(ans) != 'y');
    }

    if (ans == 'n')
    {
        Logger::write("Setting trainings canceled");
        return;
    }
    m_counter->set(*opt_arg);
    Logger::write(std::format("Set trainings to {}", *opt_arg),
                  Logger::LOGFILE);
}

/*
    Adds given count of trainings

    @param number to add
*/
void TrainingCounter::_addTrainings(std::optional<counter_t> opt_arg) noexcept
{
    if (!opt_arg)
    {
        Logger::write(std::format("{} no value\n", __PRETTY_FUNCTION__));
        return;
    }

    m_counter->add(*opt_arg);
    Logger::write(std::format("Added {} trainings", *opt_arg), Logger::LOGFILE);
}

/*
    Removes log file
*/
void TrainingCounter::_removeLogfile(
    std::optional<counter_t> opt_arg) const noexcept
{
    Logger::remove_logfile();
    Logger::write("Log file removed");
}

void TrainingCounter::_removeSaveFile(
    std::optional<counter_t> opt_arg) const noexcept
{
    m_counter->remove_savefile();
    Logger::write("Savefile removed");
}

void TrainingCounter::_removeCache(
    std::optional<counter_t> opt_arg) const noexcept
{
    _removeSaveFile();
    _removeLogfile();
    std::filesystem::remove_all(Logger::get_cache_dir());
    Logger::write("Cache directory removed");
}

void TrainingCounter::_showTrainings(
    std::optional<counter_t> opt_arg) const noexcept
{
    Logger::write(std::format("Remaining trainings: {}", m_counter->get()));
}

void TrainingCounter::_showNumTrainings(
    std::optional<counter_t> opt_arg) const noexcept
{
    Logger::write(std::format("{}", m_counter->get()));
}

void TrainingCounter::_drawCat(std::optional<counter_t> opt_arg) const noexcept
{
    Logger::write("\n"
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
                  "      `*-*   `*-*  `*-*'\n\n");
}

void TrainingCounter::_drawMoo(std::optional<counter_t> opt_arg) const noexcept
{
    Logger::write("\n"
                  "                 (__)\n"
                  "          ______~(..)~\n"
                  "           ,----\\(oo)\n"
                  "          /|____|,'\n"
                  "         * /\"\\ /\\\n"
                  "wWwWwWwWwWwWwWwWwWwWwWwWwWwWw\n"
                  "~~~ Have you mooed today? ~~~\n");
}

void TrainingCounter::_showLog(std::optional<counter_t> opt_arg) const noexcept
{
    Logger::show_logfile(opt_arg ? *opt_arg : 0);
}
