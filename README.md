*This project has been created as part of the 42 curriculum by dsisli.*

# Get Next Line

## Description

**Get Next Line** is a core project in the 42 curriculum that challenges students to write a function capable of reading a text file (or any other file descriptor) one line at a time. The primary goal is to learn about static variables in C, dynamic memory allocation, and low-level file manipulation.

This project implements a function `char *get_next_line(int fd)` which returns the next line read from a file descriptor `fd` upon each call, handling buffers of varying sizes efficiently without losing data between calls.

## Instructions

### Compilation

This project is designed to be compiled as a library or directly with a main file. You must define `BUFFER_SIZE` at compilation time.

### Execution
Make a main.c and copy the main function in the .c file
Make also a file.txt
Compile everything with cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c  -o  gnl
Run the compiled executable:
./gnl

### Usage in Code

Include the header in your C file:
```
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## Algorithm Explanation

The core challenge of GNL is maintaining the state of the file reading between function calls. Since the function ends after returning a single line, we must "remember" any extra characters read from the buffer but not yet returned.

### Strategy: Unbuffered Read with Static Storage

1.  **Static Variable (`static char *track`)**:
    We use a static pointer inside `get_next_line` to store the "leftover" data. Unlike local variables, this static variable persists in memory even after the function returns.

2.  **Read and Join Cycle (`ft_gnl_make_line`)**:
    *   We allocate a temporary buffer of size `BUFFER_SIZE`.
    *   We read from the file descriptor into this buffer.
    *   The buffer is immediately joined (`strjoin`) onto our static `track` string.
    *   We repeat this `read` -> `join` process until a newline character (`\n`) is found in the accumulated `track` string or the End Of File (EOF) is reached.

3.  **Extraction (`extract_line`)**:
    *   Once we have a newline in `track`, we calculate the length up to that newline.
    *   We extract the line (including the `\n`) into a new substring to be returned.
    *   The remaining part of the string (everything *after* the `\n`) is saved back into `track`.
    *   The old `track` is freed to prevent leaks, and the static pointer is updated to point to the new remainder.

This approach ensures that even if `BUFFER_SIZE` is very large (reading multiple lines at once) or very small (reading partial lines), the function correctly assembles exactly one line per call.

## Resources

*   **UNIX Manual**: `man 2 read`, `man 3 malloc`, `man 3 free`.
*   **Static Variables**: [GeeksforGeeks - Static Variables in C](https://www.geeksforgeeks.org/static-variables-in-c/)
*   **File Descriptors**: [Wiki - File Descriptor](https://en.wikipedia.org/wiki/File_descriptor)

### AI Usage

Artificial Intelligence (GitHub Copilot / Gemini models) was used in this project for the following tasks:
*   **Code Review**: Analyzing the `get_next_line.c` implementation to identify memory leaks, specifically around the `extract_line` helper function.
*   **Refactoring**: Suggesting a cleaner structure for `ft_gnl_make_line` to reduce line count and improve readability.
*   **Testing**: Generating a comprehensive test suite (`test_gnl.c`) to verify edge cases like empty files, large inputs, and invalid file descriptors.
*   **Documentation**: Drafting this `README.md` file based on the project structure and 42 requirements.
