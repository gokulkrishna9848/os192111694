#include <stdio.h>
#include <stdlib.h>


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


void scan(int requestQueue[], int n, int initialPosition) {
    int totalHeadMov = 0;
    int direction = 1; 
    int currentPosition = initialPosition;

    sort(requestQueue, n); 

    printf("Disk Arm Movement:\n");

    while (1) {
        int found = 0; 
        for (int i = 0; i < n; i++) {
            if (direction == 1 && requestQueue[i] >= currentPosition) {
                printf("%d -> ", currentPosition);
                totalHeadMov += abs(requestQueue[i] - currentPosition);
                currentPosition = requestQueue[i];
                found = 1;
                break;
            } else if (direction == -1 && requestQueue[i] <= currentPosition) {
                printf("%d -> ", currentPosition);
                totalHeadMov += abs(requestQueue[i] - currentPosition);
                currentPosition = requestQueue[i];
                found = 1;
                break;
            }
        }

        if (!found) {
          
            direction = -direction;
        }

      
        if (totalHeadMov == 0) {
            break;
        }
    }

    printf("%d\n", currentPosition);
    printf("Total Head Movement = %d\n", totalHeadMov);
}

int main() {
    int n, initialPosition;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int requestQueue[n];

    printf("Enter the request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &requestQueue[i]);
    }

    printf("Enter the initial position of the disk arm: ");
    scanf("%d", &initialPosition);

    scan(requestQueue, n, initialPosition);

return 0;
}