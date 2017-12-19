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

    signal(SIGINT, sighandler);

    while (1) {
        int from_client;
        int to_client;

        from_client = server_setup();

        int f;
        f = fork();

        if (f == 0) {
            to_client = server_connect(from_client);
            subserver(from_client);
            exit(0);
        }
    }

    return 0;
}

void subserver(int from_client) {

    char buffer[BUFFER_SIZE];
    while( read(from_client, buffer, sizeof(buffer)) ) {
        printf("[subserver] received %s\n", buffer);
        process(buffer);
        printf("[subserver] writing %s\n", buffer);
        write(to_client, buffer, sizeof(buffer));
    }

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
