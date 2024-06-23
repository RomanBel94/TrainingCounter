#include "AppCore.h"

int AppCore::run()
{
    log("tc started.");
    parser(argc, argv);
    LexerParser::job todo = parser.getJob();
    uint8_t num = parser.getNum();
    counter.setTrainings(save.read());

    switch (todo) {
    case LexerParser::job::help:
        {
         std::string helpMessage =
            "Usage:\n\n"
                "\ttc -a <num>\tAdd <num> workouts;\n"
                "\ttc -s <num>\tSet <num> workouts;\n"
                "\ttc -m\t\tMark completed workout;\n"
                "\ttc [-h]\t\tPrint help;\n"
                "\ttc -w\t\tShow remaining workouts.\n";

        log("printed \"help\"");
        message(helpMessage);
        break;
        }
    case LexerParser::job::mark:
        {
        counter.markTraining();
        std::string msg = 
            "Workout marked. Remaining workouts: " 
            + std::to_string(counter.getTrainings()) + ".";
        log(msg);
        message(msg);
        break;
        }
    case LexerParser::job::set:
        {
        counter.setTrainings(num);
        std::string msg = 
            "Set workouts to " + std::to_string(num) + 
            ". Remaining workouts: " + std::to_string(counter.getTrainings()) + ".";
        log(msg);
        message(msg);
        break;
        }
    case LexerParser::job::add:
        {
        counter.addTrainings(num);
        std::string msg =
            "Added " + std::to_string(num) + " workouts. "
            "Remaining workouts: " + std::to_string(counter.getTrainings()) + ".";
        log(msg);
        message(msg);
        break;
        }
    case LexerParser::job::show:
        {
        std::string msg = "Remaining workouts: " + std::to_string(counter.getTrainings()) + ".";
        log(msg);
        message(msg);
        break;
        }
    }

    log("tc stopped");
    save.write(counter.getTrainings());
	return 0;
}
