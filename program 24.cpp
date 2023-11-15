#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    int file_descriptor;
    char filename[] = "example_file.txt";
    char buffer[100];
    ssize_t bytes_read, bytes_written;

    // Create a new file or open an existing one for writing
    file_descriptor = open(filename, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1) {
        perror("Error opening the file");
        exit(1);
    }

    // Write data to the file
    char data[] = "Hello, this is a test file.\n";
    bytes_written = write(file_descriptor, data, strlen(data));
    if (bytes_written == -1) {
        perror("Error writing to the file");
        close(file_descriptor);
        exit(1);
    }

    // Close the file
    close(file_descriptor);

    // Reopen the file for reading
    file_descriptor = open(filename, O_RDONLY);
    if (file_descriptor == -1) {
        perror("Error opening the file for reading");
        exit(1);
    }

    // Read and print the contents of the file
    printf("File contents:\n");
    while ((bytes_read = read(file_descriptor, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        perror("Error reading from the file");
        close(file_descriptor);
        exit(1);
    }

    // Close the file
    close(file_descriptor);

    return 0;
}