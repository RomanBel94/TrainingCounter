#include "TrainingCounter.h"

int main(int argc, char* argv[])
{
    auto app = TrainingCounter::getInstance(argc, argv);
    return app->run(); // run application
}
