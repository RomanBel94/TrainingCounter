/**
 * @file TrainingCounter.cpp
 *
 * @brief TrainingCounter implementation
 */

#include <algorithm>
#include <array>
#include <iostream>

#include "Logger/Logger.h"
#include "TrainingCounter.h"
#include "Version/Version.h"
#include <format>

TrainingCounter::TrainingCounter(int argc, char** argv)
    : argc(argc), argv(argv), m_counter(std::make_unique<Counter<counter_t>>()),
      m_task_manager(std::make_unique<TaskManager>(this)),
      m_cli(std::make_unique<CLI::CLI>())
{
    _init_task_table();
    _init_cli_options();
}

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
        m_task_manager->add_task(&TrainingCounter::_printPrompt);
        m_task_manager->execute_all_tasks();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

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

void TrainingCounter::_fill_task_queue(
    const cli_token_list& tokens) const noexcept
{
    std::ranges::for_each(tokens,
                          [this](const auto& token)
                          {
                              std::optional<counter_t> argument{std::nullopt};
                              if (!token.second.empty())
                                  argument = std::stoi(token.second);

                              m_task_manager->add_task(
                                  task_table.at(token.first), argument);
                          });
}

void TrainingCounter::_printVersion(opt_arg) const noexcept
{
    Logger::write(std::format("TrainingCounter v{}\nCompiled at: {}", VERSION,
                              __TIMESTAMP__));
}

void TrainingCounter::_printHelp(opt_arg) const noexcept
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

void TrainingCounter::_printPrompt(opt_arg) const noexcept
{
    Logger::write("Type \"TrainingCounter -h or --help\" to see instructions");
}

void TrainingCounter::_markTraining(opt_arg) noexcept
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

void TrainingCounter::_setTrainings(opt_arg num) noexcept
{
    if (!num)
        *num = 0;

    char ans{};
    if (*num < m_counter->get())
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
    m_counter->set(*num);
    Logger::write(std::format("Set trainings to {}", *num), Logger::LOGFILE);
}

void TrainingCounter::_addTrainings(opt_arg num) noexcept
{
    if (!num)
        num = 0;

    m_counter->add(*num);
    Logger::write(std::format("Added {} trainings", *num), Logger::LOGFILE);
}

void TrainingCounter::_removeLogfile(opt_arg) const noexcept
{
    Logger::remove_logfile();
    Logger::write("Log file removed");
}

void TrainingCounter::_removeSaveFile(opt_arg) const noexcept
{
    m_counter->remove_savefile();
    Logger::write("Savefile removed");
}

void TrainingCounter::_removeCache(opt_arg) const noexcept
{
    m_counter->remove_savefile();
    Logger::remove_logfile();
    std::filesystem::remove_all(Logger::get_cache_dir());
    Logger::write("Cache directory removed");
}

void TrainingCounter::_showTrainings(opt_arg) const noexcept
{
    Logger::write(std::format("Remaining trainings: {}", m_counter->get()));
}

void TrainingCounter::_showNumTrainings(opt_arg) const noexcept
{
    Logger::write(std::format("{}", m_counter->get()));
}

void TrainingCounter::_showLog(opt_arg lines) const noexcept
{
    Logger::show_logfile(lines ? *lines : 0);
}

void TrainingCounter::_drawCat(opt_arg) const noexcept
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

void TrainingCounter::_drawMoo(opt_arg) const noexcept
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
