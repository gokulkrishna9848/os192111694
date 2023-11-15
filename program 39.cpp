#include <stdio.h>
#include <stdlib.h>

// Function to sort an array of integers in ascending order
void sort(int arr[], int n) {
    int temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap arr[j] and arr[j + 1]
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to simulate C-SCAN disk scheduling algorithm
void cscan(int requestQueue[], int n, int initialPosition, int diskSize) {
    int totalHeadMov = 0;
    int currentPosition = initialPosition;

    sort(requestQueue, n); // Sort the request queue in ascending order

    printf("Disk Arm Movement:\n");

    // First, move the disk arm to the end of the disk in the right direction
    while (currentPosition < diskSize) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (requestQueue[i] >= currentPosition) {
                printf("%d -> ", currentPosition);
                totalHeadMov += (requestQueue[i] - currentPosition);
                currentPosition = requestQueue[i];
                found = 1;
                break;
            }
        }

        if (!found) {
            break;
        }
    }

    // Move the disk arm back to the beginning
    printf("%d -> ", currentPosition);
    totalHeadMov += (diskSize - currentPosition);
    currentPosition = 0;

    // Continue moving the disk arm in the right direction
    for (int i = 0; i < n; i++) {
        if (requestQueue[i] >= currentPosition) {
            printf("%d -> ", currentPosition);
            totalHeadMov += (requestQueue[i] - currentPosition);
            currentPosition = requestQueue[i];
        }
    }

    printf("%d\n", currentPosition);
    printf("Total Head Movement = %d\n", totalHeadMov);
}

int main() {
    int n, initialPosition, diskSize;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requestQueue[n];

    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requestQueue[i]);
    }

    printf("Enter the initial position of the disk arm: ");
    scanf("%d", &initialPosition);

    printf("Enter the size of the disk: ");
    scanf("%d", &diskSize);

    cscan(requestQueue, n, initialPosition, diskSize);
return 0;
}