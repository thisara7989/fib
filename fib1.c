#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void generate_fibonacci(int n) {
    int a = 0, b = 1, next;
    for (int i = 0; i < n; i++) {
        if (i == 0) {
            printf("%d ", a);
        } else if (i == 1) {
            printf("%d ", b);
        } else {
            next = a + b;
            printf("%d ", next);
            a = b;
            b = next;
        }
    }
    printf("\n");
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr,"!! you forgot to enter the number !! enter as ./fib 5 \n");
        return 1;
    }
   
    char *endptr;
    long input = strtol(argv[1], &endptr, 10);

    if (*endptr !='\0'){
         fprintf(stderr, "!! invalid input.enter valid integer !!\n");
         return 1;
    }

    if (input < 0) {
        fprintf(stderr, "Please enter a non-negative number.\n");
        return 1;
    }
     int n = (int)input;
    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    } else if (pid == 0) { // Child process
        printf("Child Process Created..! ID: %d\n", getpid());
        printf("Here is the Fibonacci Sequence: ");
        generate_fibonacci(n);
        exit(0);
    } else { // Parent process
        wait(NULL); // Wait for child to finish
        printf("Child process has completed successfully...!.\n");
    }

    return 0;
}
