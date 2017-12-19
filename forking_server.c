#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
    if (signo == SIGINT) {
        remove("luigi");
        exit(0);
    }
}

int main() {
}

void subserver(int from_client) {
}

void process(char * s) {
    unsigned int i;
    for (i = 0; i < strlen(s); i++) {
        if (i % 2 == 0) {
            s[i] = toupper(s[i]);
        } else {
            s[i] = tolower(s[i]);
        }
    }
}
