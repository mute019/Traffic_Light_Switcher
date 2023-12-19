#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX 3
#define CHAR 20

typedef struct autolight
{
    int duration;
    char light[CHAR];
} light;


int main() {
    int ms_que = msgget(221, 0);
    if (ms_que < 0) {
        perror("");
        return 0;
    }

    light combinations[MAX];

    light red;
    red.duration = 60;
    strcpy(red.light, "red");
    //red.light[19] = '\0';

    light green;
    green.duration = 60;
    strcpy(green.light, "green");
    //green.light[19] = '\0';

    light amber;
    amber.duration = 15;
    strcpy(amber.light, "amber");
    //amber.light[19] = '\0';

    combinations[0] = red;
    combinations[1] = amber;
    combinations[2] = green;
    light color = combinations[0];
    int timeoff = combinations[0].duration;
    //int timeoff = 10;
    int color_counter = 0;
    int counter = 1;
    while(counter <= timeoff) {
        int k = 0;
        msgrcv(ms_que, &k, sizeof(k), 0, IPC_NOWAIT);
        if (!k) {
            printf("%s %d \n", color.light, timeoff);
            sleep(1);
            timeoff--;
            if (counter > timeoff) {
                color_counter = (color_counter % 3) + 1;
                color = combinations[color_counter];
                timeoff = color.duration;
                printf("--\n");
                printf("\n\n\n");
                sleep(5);
            }
        } else {
            color_counter = k;
            color = combinations[color_counter];
            timeoff = color.duration;
            k = 0;
        }
    }
}
