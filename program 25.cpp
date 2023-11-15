#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int main() {
    
    int file_descriptor = open("example.txt", O_RDWR);
    if (file_descriptor == -1) {
        perror("Error opening the file");
        exit(1);
    }

 
    int flags = fcntl(file_descriptor, F_GETFL);
    if (flags == -1) {
        perror("Error getting file flags");
    }
    printf("File flags: %d\n", flags);

    
    int new_flags = fcntl(file_descriptor, F_SETFL, flags | O_APPEND);
    if (new_flags == -1) {
        perror("Error setting file flags");
    }

    
    off_t offset = lseek(file_descriptor, 10, SEEK_SET);
    if (offset == -1) {
        perror("Error seeking in the file");
    }
    printf("New file pointer position: %ld\n", (long)offset);

   
    struct stat file_info;
    if (fstat(file_descriptor, &file_info) == -1) {
        perror("Error getting file information");
    }
    printf("File size: %lld bytes\n", (long long)file_info.st_size);

    
    struct dirent *entry;
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("Error opening directory");
    } else {
        printf("Files in the current directory:\n");
        while ((entry = readdir(dir)) != NULL) {
            printf("%s\n", entry->d_name);
        }
        closedir(dir);
    }

   
    close(file_descriptor);

    return 0;
}