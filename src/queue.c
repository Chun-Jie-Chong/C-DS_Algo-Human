// The Algorithms
////////////////////////////////////////////////////////////////////////////////
// INCLUDES
#include "queue.h"
#include <string.h>

////////////////////////////////////////////////////////////////////////////////
// GLOBAL VARIABLES
int count;

////////////////////////////////////////////////////////////////////////////////
// MAIN ENTRY POINT

// int main(int argc, char const *argv[])
// {
//     create();
//     enque(5);

//     return 0;
// }

void create()
{
    head = NULL;
    tail = NULL;
}

/**
 * Puts an item into the Queue.
 */
void enque(int x)
{
    if (head == NULL)
    {
        head = (struct node *)malloc(sizeof(struct node));
        head->data = x;
        head->pre = NULL;
        tail = head;
    }
    else
    {
        tmp = (struct node *)malloc(sizeof(struct node));
        tmp->data = x;
        tmp->next = tail;
        tail = tmp;
    }
}

/**
 * Takes the next item from the Queue.
 */
int deque()
{
    int returnData = 0;
    if (head == NULL)
    {
        printf("ERROR: Deque from empty queue.\n");
        exit(1);
    }
    else
    {
        returnData = head->data;
        if (head->pre == NULL)
            head = NULL;
        else
            head = head->pre;
        head->next = NULL;
    }
    return returnData;
}

/**
 * Returns the size of the Queue.
 */
int size() { return count; }

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (!file) {
        printf("Unable to open file %s\n", argv[1]);
        return 1;
    }

    create();
    char operation[10];
    int value;

    while (fscanf(file, "%s", operation) != EOF) {
        if (strcmp(operation, "enqueue") == 0) {
            if (fscanf(file, "%d", &value) == 1) {
                enque(value);
                // viewQueue(q);   // Uncomment for debugging
            }
        } else if (strcmp(operation, "dequeue") == 0) {
            printf("Dequeued: %d\n", deque());
            // viewQueue(q);   // Uncomment for debugging
        } else if (strcmp(operation, "size") == 0) {
            printf("Queue size: %d\n", size());
        }
    }

    fclose(file);
    return 0;
}