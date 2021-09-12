//
// Created by vince on 25.07.21.
//

#ifndef LMQTT__SERVER_CLIMODE_H
#define LMQTT__SERVER_CLIMODE_H

enum CLIMode {
    CONNECT_MODE, SUBSCRIBE_MODE, PUBLISH_MODE, UNSUBSCRIBE_MODE
};

namespace CLIModes {

    static const char* toString(CLIMode cliMode){
        switch (cliMode) {
            case CONNECT_MODE:
                return "connect";
            case SUBSCRIBE_MODE:
                return "subscribe";
            case PUBLISH_MODE:
                return "publish";
        }
    }

    static void printUsageInformation(char* programName, CLIMode mode){
        switch (mode) {
            case CONNECT_MODE:
                fprintf(stderr, "Usage: %s %s -u username -p password -i clientId [-r (reset)] ip port\n", programName, CLIModes::toString(mode));
            case SUBSCRIBE_MODE:
                fprintf(stderr, "Usage: %s %s -t topic -i clientId -q qos ip port\n", programName, CLIModes::toString(mode));
            case PUBLISH_MODE:
                fprintf(stderr, "Usage: %s %s -t topic -i clientId msg ip port\n", programName, CLIModes::toString(mode));
            case UNSUBSCRIBE_MODE:
                fprintf(stderr, "Usage: %s %s -t topic -i clientId ip port\n", programName, CLIModes::toString(mode));
        }
    }

    static CLIMode findCliMode(char *mode) {
        if (strcmp(mode, "connect") == 0) {
            return CONNECT_MODE;
        }
        if (strcmp(mode, "subscribe") == 0) {
            return SUBSCRIBE_MODE;
        }
        if (strcmp(mode, "unsubscribe") == 0) {
            return UNSUBSCRIBE_MODE;
        }
        fprintf(stderr, "%s", "Invalid cli mode\n");
        fprintf(stderr, "valid modes are: %s, %s, %s\n", "connect", "subscribe, unsubscribe");
        if (strcmp(mode,"publish") == 0){
            return PUBLISH_MODE;
        }
        exit(1);
    }

}

#endif //LMQTT__SERVER_CLIMODE_H
