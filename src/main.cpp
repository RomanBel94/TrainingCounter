/**
 * @file main.cpp
 *
 * @brief Main file.
 */

#include "TrainingCounter.h"

/**
 * @brief Starts the application.
 *
 * @param[in] argc - number of CLI arguments.
 * @param[in] argv - values of CLI arguments.
 *
 * @return Exit code.
 */
int main(int argc, char* argv[])
{
    auto& app = TrainingCounter::get_instance(argc, argv);
    return app.run();
}
