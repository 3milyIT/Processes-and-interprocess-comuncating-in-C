# Processes-and-interprocess-comuncating-in-C

## Interprocess Communication using Message Queues in C

In this tutorial, we'll explore how to implement a simple message queue for interprocess communication using the `msgget`, `msgsnd`, and `msgrcv` functions in C. Message queues provide a reliable and efficient way for processes to exchange data.

### Setting up the Message Queue

To create a message queue, we need to generate a unique key using the `ftok` function. Let's take a look at the code snippet:

```c
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

    // Generating a unique key using ftok
    key = ftok("hello", 65);

    // Creating the message queue with the key
    msgqid = msgget(key, 0666 | IPC_CREAT);

    if (msgqid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Message queue created. ID: %d\n", msgqid);

    // ... message sending and receiving code

    return 0;
}
```

In the code above, we generate a unique key using `ftok` and create the message queue using `msgget`. We specify the key and provide the appropriate flags (`0666 | IPC_CREAT`) to indicate the permissions and creation mode of the message queue.

### Sending and Receiving Messages

Now that we have a message queue, let's send and receive messages between processes.

```c
// ... previous code

int main()
{
    // ... previous code

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork() function error");
    } else if (pid > 0) {
        // Parent process: sending a message
        printf("Parent process - sending a message. ID: %d\n", getpid());

        // Filling the message structure
        message.mesg_type = 1;
        printf("Write message: ");
        fgets(message.mesg_text, 100, stdin);

        // Sending the message
        msgsnd(msgqid, &message, sizeof(message), 0);

        printf("Message sent: %s", message.mesg_text);
    } else {
        // Child process: receiving a message
        printf("Child process - receiving a message. ID: %d\n", getpid());

        // Receiving the message
        msgrcv(msgqid, &message, sizeof(message), 1, 0);

        printf("Message received: %s", message.mesg_text);
    }

    // ... previous code

    return 0;
}
```

In the updated code, we fork a child process using `fork()`. The parent process sends a message, while the child process receives the message. The `msgsnd` function is used to send a message to the message queue, and `msgrcv` is used to receive a message from the message queue.

### Cleaning up the Message Queue

Once we are done using the message queue, it's important to clean up and remove it.

```c
// ... previous code

int main()
{
    // ... previous code

    // Cleaning up the message queue
    msgctl(msgqid, IPC_RMID, NULL);

    return 0;
}
```

In the code above, we use the `msgctl` function with the `IPC_RMID` flag to remove

 the message queue specified by `msgqid`.

### Conclusion

In this tutorial, we learned how to implement a simple message queue for interprocess communication using the `msgget`, `msgsnd`, and `msgrcv` functions in C. Message queues provide a reliable and efficient way for processes to exchange data. By following the examples and understanding the usage of these functions, you can incorporate message queues into your own interprocess communication mechanisms.

Remember to handle errors appropriately and clean up the message queue after use to ensure proper functioning of your programs.

That's it for this tutorial! Feel free to experiment further and explore more advanced concepts in interprocess communication using message queues. Happy coding!



.

Oczywiście! Oto artykuł na GitHubie w języku polskim na podstawie dostarczonych informacji:

## Komunikacja międzyprocesowa przy użyciu kolejek komunikatów w C

W tym samouczku omówimy, jak zaimplementować prostą kolejkę komunikatów do komunikacji międzyprocesowej przy użyciu funkcji `msgget`, `msgsnd` i `msgrcv` w języku C. Kolejki komunikatów zapewniają niezawodny i wydajny sposób wymiany danych między procesami.

### Konfiguracja kolejki komunikatów

Aby utworzyć kolejkę komunikatów, musimy wygenerować unikalny klucz przy użyciu funkcji `ftok`. Przyjrzyjmy się fragmentowi kodu:

```c
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

    // Generowanie unikalnego klucza za pomocą ftok
    key = ftok("hello", 65);

    // Tworzenie kolejki komunikatów z użyciem klucza
    msgqid = msgget(key, 0666 | IPC_CREAT);

    if (msgqid == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Kolejka komunikatów została utworzona. ID: %d\n", msgqid);

    // ... kod wysyłania i odbierania komunikatów

    return 0;
}
```

W powyższym kodzie generujemy unikalny klucz za pomocą `ftok` i tworzymy kolejkę komunikatów przy użyciu `msgget`. Podajemy klucz oraz odpowiednie flagi (`0666 | IPC_CREAT`), które określają uprawnienia i tryb tworzenia kolejki komunikatów.

### Wysyłanie i Odbieranie Komunikatów

Teraz, gdy mamy kolejkę komunikatów, możemy wysyłać i odbierać komunikaty między procesami.

```c
// ... wcześniejszy kod

int main()
{
    // ... wcześniejszy kod

    pid_t pid = fork();
    if (pid < 0) {
        perror("Błąd funkcji fork()");
    } else if (pid > 0) {
        // Proces nadrzędny: wysyłanie komunikatu
        printf("Proces nadrzędny - wysyłanie komunikatu. ID: %d\n", getpid());

        // Wypełnienie struktury komunikatu
        message.mesg_type = 1;
        printf("Wprowadź wiadomość: ");
        fgets(message.mesg_text, 100, stdin);

        // Wysyłanie komunikatu
        msgsnd(msgqid, &message, sizeof(message), 0);

        printf("Wysłana wiadomość: %s", message.mesg_text);
    } else {
       

 // Proces potomny: odbieranie komunikatu
        printf("Proces potomny - odbieranie komunikatu. ID: %d\n", getpid());

        // Odbieranie komunikatu
        msgrcv(msgqid, &message, sizeof(message), 1, 0);

        // Wyświetlanie otrzymanej wiadomości
        printf("Otrzymana wiadomość: %s", message.mesg_text);
    }

    // ... kod zwalniania zasobów kolejki

    return 0;
}
```

W powyższym kodzie używamy funkcji `fork`, aby utworzyć nowy proces potomny. Proces nadrzędny jest odpowiedzialny za wysyłanie komunikatu, podczas gdy proces potomny odbiera komunikat.

Najpierw proces nadrzędny wypełnia strukturę `message` danymi i wysyła ją do kolejki komunikatów za pomocą `msgsnd`. Proces potomny odbiera komunikat z kolejki za pomocą `msgrcv` i wyświetla otrzymaną wiadomość.

### Obsługa Błędów i Zwalnianie Zasobów

Ważne jest, aby obsłużyć ewentualne błędy podczas tworzenia kolejki komunikatów i odbierania oraz wysyłania komunikatów. W poniższym kodzie przedstawiamy przykład obsługi błędów przy użyciu funkcji `perror`.

```c
// ... wcześniejszy kod

int main()
{
    key_t key;
    int msgqid;

    key = ftok("hello", 65);
    if (key == -1) {
        perror("Błąd ftok");
        exit(1);
    }

    msgqid = msgget(key, 0666 | IPC_CREAT);
    if (msgqid == -1) {
        perror("Błąd msgget");
        exit(1);
    }

    // ... kod wysyłania i odbierania komunikatów

    return 0;
}
```

Ponadto, ważne jest, aby zwolnić zasoby kolejki komunikatów po zakończeniu używania. Możemy to zrobić za pomocą funkcji `msgctl` z flagą `IPC_RMID`, która usuwa kolejkę komunikatów.

```c
// ... wcześniejszy kod

int main()
{
    // ... wcześniejszy kod

    // Usunięcie kolejki komunikatów
    msgctl(msgqid, IPC_RMID, NULL);

    return 0;
}
```

### Podsumowanie

W tym samouczku nauczyliśmy się, jak zaimplementować prostą kolejkę komunikatów do komunikacji międzyprocesowej przy użyciu funkcji `msgget`, `msgsnd` i `msgrcv` w języku C. Kolejki komunikatów zapewniają niezawodny i wydajny sposób wymiany danych między procesami. Dzięki przykładom i zrozumieniu użycia tych funkcji możesz włączyć kolejki komunikatów do

 swoich projektów z komunikacją międzyprocesową.
