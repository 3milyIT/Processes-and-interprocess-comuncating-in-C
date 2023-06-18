//MY SOLUTION
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgqid;
    //generate a unique key
    key = ftok("hello", 65);

    //msgget -> create a message queue using the key, 0666|IPC_CREAT is necessary
    msgqid = msgget(key, 0666 | IPC_CREAT);
    printf("Message queue has been created. ID: %d\n", msgqid);

    //send a message to the queue
    message.mesg_type = 1; //set the message type
    printf("Write message: ");
    fgets(message.mesg_text, 100, stdin);
    printf("\n");
    msgsnd(msgqid, &message, sizeof(message), 0);

    //receive a message from the queue
    msgrcv(msgqid, &message, sizeof(message), 1, 0);
    //display the message
    printf("%s", message.mesg_text);

    msgctl(msgqid, IPC_RMID, NULL);

    return 0;
}


//MY SOLUTION - errors handling
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgqid;
    //generate a unique key
    key = ftok("hello", 65);
    if (key == -1) {
        perror("key");
        exit(1);
    }
    //msgget -> create a message queue using the key, 0666|IPC_CREAT is necessary
    msgqid = msgget(key, 0666 | IPC_CREAT);
    if (msgqid == -1) {
        perror("msgqid");
        exit(1);
    }
    printf("Message queue has been created. ID: %d\n", msgqid);

    //send a message to the queue
    message.mesg_type = 1; //set the message type
    printf("Write data: ");
    fgets(message.mesg_text, 100, stdin);
    printf("\n");
    msgsnd(msgqid, &message, sizeof(message), 0);

    //receive a message from the queue
    msgrcv(msgqid, &message, sizeof(message), 1, 0);
    //display the message
    printf("%s", message.mesg_text);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgqid;
    //generate a unique key
    key = ftok("hello", 65);

    //msgget -> create a message queue using the key, 0666|IPC_CREAT is necessary
    msgqid = msgget(key, 0666 | IPC_CREAT);
    message.mesg_type = 1; //set the message type
    printf("Message queue has been created. ID: %d\n", msgqid);

    printf("Write message: ");
    fgets(message.mesg_text, 100, stdin);
    printf("\n");

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() function error");
    }
    else if (pid > 0) {
        printf("First process - sending a message. ID: %d\n", getpid());
        //send a message to the queue
        msgsnd(msgqid, &message, sizeof(message), 0);
        printf("Message sent: %s", message.mesg_text);
    }
    else {
        printf("Second process - getting a message. ID: %d\n", getpid());
        //receive a message from the queue
        msgrcv(msgqid, &message, sizeof(message), 1, 0);
        //display the message
        printf("Message received: %s", message.mesg_text);
    }

    msgctl(msgqid, IPC_RMID, NULL);

    return 0;
}











//MOJE ROZWIĄZANIE
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgqid;
    //tworzenie unikalnego klucza
    key = ftok("hello",65);

    //msgget -> tworzenie kolejki komunikatów z użyciem klucza, 0666}IPC_CREAT musi być
    msgqid = msgget(key,0666|IPC_CREAT);
    printf("Kolejka komunikatów została utworzona. ID: %d\n",msgqid);

    //wysyłanie wiadomości do kolejki
    message.mesg_type=1; //ustawianie typu wiadomości
    printf("Write message: ");
    fgets(message.mesg_text,100,stdin);
    printf("\n");
    msgsnd(msgqid,&message,sizeof(message),0);

    //odbieranie wiadomości z kolejki
    msgrcv(msgqid,&message,sizeof(message),1,0);
    //wyświtlanie wiadomości
    printf("%s",message.mesg_text);

     msgctl(msgqid, IPC_RMID, NULL);

    return 0;
}






//MOJE ROZWIĄZANIE - errors handling
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgqid;
    //tworzenie unikalnego klucza
    key = ftok("hello",65);
    if(key==-1) {
        perror("key");
        exit(1);
    }
    //msgget -> tworzenie kolejki komunikatów z użyciem klucza, 0666}IPC_CREAT musi być
    msgqid = msgget(key,0666|IPC_CREAT);
    if(msgqid==-1) {
        perror("msgqid");
        exit(1);
    }
    printf("Kolejka komunikatów została utworzona. ID: %d\n",msgqid);

    //wysyłanie wiadomości do kolejki
    message.mesg_type=1; //ustawianie typu wiadomości
    printf("Write data: ");
    fgets(message.mesg_text,100,stdin);
    printf("\n");
    msgsnd(msgqid,&message,sizeof(message),0);

    //odbieranie wiadomości z kolejki
    msgrcv(msgqid,&message,sizeof(message),1,0);
    //wyświtlanie wiadomości
    printf("%s",message.mesg_text);

    return 0;
}










#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <unistd.h>

struct mesg_buffer {
    long mesg_type;
    char mesg_text[100];
} message;

int main()
{
    key_t key;
    int msgqid;
    //tworzenie unikalnego klucza
    key = ftok("hello",65);

    //msgget -> tworzenie kolejki komunikatów z użyciem klucza, 0666}IPC_CREAT musi być
    msgqid = msgget(key,0666|IPC_CREAT);
    message.mesg_type=1; //ustawianie typu wiadomości
    printf("Kolejka komunikatów została utworzona. ID: %d\n",msgqid);

    printf("Write message: ");
    fgets(message.mesg_text,100,stdin);
    printf("\n");

    pid_t pid = fork();
    if(pid < 0) {
        perror("fork() function error");
    }
    else if(pid > 0) {
        printf("First process - sending a message. ID: %d\n",getpid());
        //wysyłanie wiadomości do kolejki
        msgsnd(msgqid,&message,sizeof(message),0);
        printf("Message sent: %s",message.mesg_text);
    }
    else {
        printf("Second process - getting a message. ID: %d\n",getpid());
    //odbieranie wiadomości z kolejki
    msgrcv(msgqid,&message,sizeof(message),1,0);
    //wyświtlanie wiadomości
    printf("Message received: %s",message.mesg_text);
    }

     msgctl(msgqid, IPC_RMID, NULL);

    return 0;
}
