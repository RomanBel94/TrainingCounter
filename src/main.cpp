/** @file main.cpp
 *
 *  @brief Main file.
 *
 */

#include "TrainingCounter.h"

/** @brief Starts the application.
 *
 *  @param[in] Number of given CLI arguments.
 *
 *  @param[in] Arguments given in CLI.
 *
 *  @return Exit code.
 */
int main(int argc, char* argv[])
{
    auto app = TrainingCounter::getInstance(argc, argv);
    return app->run(); // run application
}
