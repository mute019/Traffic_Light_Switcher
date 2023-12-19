#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    int key = 221;
    int ms_que = msgget(key, IPC_CREAT | 0766);
    printf("Message: %d is created with Key : %d \n", ms_que, key);
    return 0;
}