#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef enum lights {
    Red = 1,
    Amber,
    Green,
    Exit
} light;

int main() {
    int exit = 0;
    int ms_que = msgget(221, 0);
    if (ms_que < 0) {
        perror("");
        return 0;
    }

    while(!exit) {
        light choice;
        printf("\n\nWelcome to Traffic Management System. \n");
        printf("Press 1 to turn on Red \n");
        printf("Press 2 to turn on Amber \n");
        printf("Press 3 to turn on Green \n");
        printf("Press 4 to exit \n");
        
        printf("Enter Your Choice:  ");
        int che;
        scanf("%d", &che);

        choice = (light) che;
        printf("\n\n");

        switch (choice )
        {
        case Red:
            printf("Red light turned on \n");
            //che = (int)choice;
            --che;
            msgsnd(ms_que, &che, sizeof(che), 0);
            break;

        case Amber:
            printf("Amber light turned on \n");
            --che;
            msgsnd(ms_que, &che, sizeof(che), 0);
            break;

        case Green:
            printf("Green light turned on \n");
            --che;
            msgsnd(ms_que, &che, sizeof(che), 0);
            break;

        case Exit:
            exit = 1;
            break;

        default:
            printf("Wrong Choice \n");
            break;
        }

    }
}