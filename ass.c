#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int CYLINDERS = 5000;
#define MAX_REQUESTS 1000

void parse_input(char* input, int requests[], int* count) {
    char* token = strtok(input, ",");
    while (token != NULL) {
        requests[*count] = atoi(token);
        (*count)++;
        token = strtok(NULL, ",");
    }
}

void fcfs(int requests[], int count, int head) {
    int total_movement = 0;
    int current_head = head;

    printf("\nFCFS Head Movement Order: ");
    for (int i = 0; i < count; i++) {
        printf("%d ", requests[i]);
        total_movement += abs(requests[i] - current_head);
        current_head = requests[i];
    }

    printf("\nTotal head movement for FCFS: %d\n", total_movement);
}

void scan(int requests[], int count, int head) {
    int total_movement = 0;
    int current_head = head;
    int temp_requests[MAX_REQUESTS];

    for (int i = 0; i < count; i++) {
        temp_requests[i] = requests[i];
    }

    // Sort requests
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (temp_requests[i] > temp_requests[j]) {
                int temp = temp_requests[i];
                temp_requests[i] = temp_requests[j];
                temp_requests[j] = temp;
            }
        }
    }

    printf("\nSCAN Head Movement Order: ");

    // Move towards smaller cylinder numbers first
    int index = 0;
    while (index < count && temp_requests[index] < head) {
        index++;
    }

    // Move downwards from head to 0
    for (int i = index - 1; i >= 0; i--) {
        printf("%d ", temp_requests[i]);
        total_movement += abs(temp_requests[i] - current_head);
        current_head = temp_requests[i];
    }

    // Go to 0 if not already there
    if (current_head != 0) {
        total_movement += current_head;
        current_head = 0;
        printf("0 ");
    }

    // Move upwards from index to the end
    for (int i = index; i < count; i++) {
        printf("%d ", temp_requests[i]);
        total_movement += abs(temp_requests[i] - current_head);
        current_head = temp_requests[i];
    }

    printf("\nTotal head movement for SCAN: %d\n", total_movement);
}

void c_scan(int requests[], int count, int head) {
    int total_movement = 0;
    int current_head = head;
    int temp_requests[MAX_REQUESTS];

    for (int i = 0; i < count; i++) {
        temp_requests[i] = requests[i];
    }

    // Sort requests
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (temp_requests[i] > temp_requests[j]) {
                int temp = temp_requests[i];
                temp_requests[i] = temp_requests[j];
                temp_requests[j] = temp;
            }
        }
    }

    printf("\nC-SCAN Head Movement Order: ");

    int index = 0;
    while (index < count && temp_requests[index] < head) {
        index++;
    }

    // Move up from head to the largest request
    for (int i = index; i < count; i++) {
        printf("%d ", temp_requests[i]);
        total_movement += abs(temp_requests[i] - current_head);
        current_head = temp_requests[i];
    }

    // Move to the end (CYLINDERS - 1)
    if (current_head != CYLINDERS - 1) {
        total_movement += (CYLINDERS - 1 - current_head);
        current_head = CYLINDERS - 1;
        printf("%d ", current_head);
    }

    // Jump to 0
    total_movement += CYLINDERS - 1;
    current_head = 0;
    printf("0 ");

    // Continue from 0 to remaining requests
    for (int i = 0; i < index; i++) {
        printf("%d ", temp_requests[i]);
        total_movement += abs(temp_requests[i] - current_head);
        current_head = temp_requests[i];
    }

    printf("\nTotal head movement for C-SCAN: %d\n", total_movement);
}

int main() {
    int requests[MAX_REQUESTS];
    int head;
    int count = 0;
    char input[1000];

    srand(time(NULL));

    printf("Enter the total number of cylinders: ");
    scanf("%d", &CYLINDERS);

    printf("Enter the list of requested cylinder numbers (comma-separated): ");
    getchar();
    fgets(input, sizeof(input), stdin);
    parse_input(input, requests, &count);

    printf("Enter the initial head position (0 - %d): ", CYLINDERS - 1);
    scanf("%d", &head);

    if (head < 0 || head >= CYLINDERS) {
        printf("Invalid head position. Must be between 0 and %d.\n", CYLINDERS - 1);
        return 1;
    }

    printf("\nInitial head position: %d\n", head);

    fcfs(requests, count, head);
    scan(requests, count, head);
    c_scan(requests, count, head);

    return 0;
}
