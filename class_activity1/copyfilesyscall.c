#include <fcntl.h>    // for open()
#include <unistd.h>   // for read(), write(), close()
#include <stdio.h>    // for perror()

int main() {
    int source_fd, dest_fd;       // file descriptors
    char buffer[1024];            // temporary storage buffer
    ssize_t bytes_read;           // number of bytes read

    // 1️⃣ Open the source file (read-only)
    source_fd = open("result.txt", O_RDONLY);
    if (source_fd < 0) {
        perror("Error opening result.txt");
        return 1;
    }

    // 2️⃣ Open (or create) the destination file (write-only)
    dest_fd = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd < 0) {
        perror("Error creating copyresult.txt");
        close(source_fd);
        return 1;
    }

    // 3️⃣ Read from source and write to destination
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        if (write(dest_fd, buffer, bytes_read) != bytes_read) {
            perror("Error writing to copyresult.txt");
            close(source_fd);
            close(dest_fd);
            return 1;
        }
    }

    if (bytes_read < 0) {
        perror("Error reading from result.txt");
    }

    // 4️⃣ Close both files
    close(source_fd);
    close(dest_fd);

    return 0;
}
