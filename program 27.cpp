#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    // Check if a directory path was provided as a command-line argument
    const char *path = (argc > 1) ? argv[1] : ".";

    // Open the directory
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        exit(1);
    }

    // Read and print the contents of the directory
    struct dirent *entry;
    printf("Contents of directory '%s':\n", path);
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}