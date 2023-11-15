#include <stdio.h>
#include <stdlib.h>

int main() {
   
    FILE *file = fopen("example.txt", "w");
    if (file == NULL) {
        perror("Error creating the file");
        exit(1);
    }

   
    const char *content = "This is the first line of the file.\n";
    fputs(content, file);

 
    fclose(file);

  
    file = fopen("example.txt", "r");
    if (file == NULL) {
        perror("Error opening the file for reading");
        exit(1);
    }

   
    printf("File contents:\n");
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }

   
    fclose(file);

    
    file = fopen("example.txt", "a");
    if (file == NULL) {
        perror("Error opening the file for appending");
        exit(1);
    }

    const char *additionalContent = "This is the second line of the file.\n";
    fputs(additionalContent, file);

    
    fclose(file);

   
    if (remove("example.txt") != 0) {
        perror("Error deleting the file");
        exit(1);
    }

    printf("File 'example.txt' has been deleted.\n");

    return 0;
}