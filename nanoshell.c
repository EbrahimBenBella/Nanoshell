#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT 1024

typedef struct Variable {
    char *name;
    char *value;
    struct Variable *next;
} Variable;

Variable *head = NULL;

void set_local_variable(char *name, char *value) {
    Variable *temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0) {
            free(temp->value);
            temp->value = strdup(value);
            return;
        }
        temp = temp->next;
    }

  
    Variable *new_var = (Variable *)malloc(sizeof(Variable));
    new_var->name = strdup(name);
    new_var->value = strdup(value);
    new_var->next = head;
    head = new_var;
}


char *get_local_variable(char *name) {
    Variable *temp = head;
    while (temp) {
        if (strcmp(temp->name, name) == 0)
            return temp->value;
        temp = temp->next;
    }
    return NULL;
}


void export_variable(char *name) {
    char *value = get_local_variable(name);
    if (value) {
        setenv(name, value, 1);
    } else {
        printf("Variable %s not found\n", name);
    }
}


void execute_command(char *input) {
    if (strcmp(input, "exit") == 0) {
        printf("Good Bye :)\n");
        exit(0);
    }

   
    if (strcmp(input, "pwd") == 0) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s\n", cwd);
        }
        return;
    }

  
    if (strncmp(input, "cd ", 3) == 0) {
        char *dir = input + 3;
        if (chdir(dir) != 0) {
            perror("cd failed");
        }
        return;
    }

  
    if (strncmp(input, "export ", 7) == 0) {
        export_variable(input + 7);
        return;
    }

   
    if (strncmp(input, "echo ", 5) == 0) {
        char *msg = input + 5;
        if (msg[0] == '$') {
            char *value = get_local_variable(msg + 1);
            printf("%s\n", value ? value : "");
        } else {
            printf("%s\n", msg);
        }
        return;
    }

   
    char *equals = strchr(input, '=');
    if (equals) {
        *equals = '\0';
        char *name = input;
        char *value = equals + 1;

        if (strchr(name, ' ') || strchr(value, ' ')) {
            printf("Invalid command\n");
            return;
        }

        set_local_variable(name, value);
        return;
    }

    
    pid_t pid = fork();
    if (pid == 0) {
        char *args[] = { "/bin/sh", "-c", input, NULL };
        execvp(args[0], args);
        perror("Execution failed");
        exit(1);
    } else if (pid > 0) {
        wait(NULL);
    } else {
        perror("Fork failed");
    }
}

int main() {
    char input[MAX_INPUT];

    while (1) {
        printf("Nano Shell Prompt > ");
        if (fgets(input, MAX_INPUT, stdin) == NULL)
            break;

        
        input[strcspn(input, "\n")] = 0;

        execute_command(input);
    }

    return 0;
}

