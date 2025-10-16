# get_next_line

A function that reads a line from a file descriptor.

## 💡 About
The get_next_line project is a programming function that reads a line ending with a newline character from a file descriptor. When calling the function in a loop, it will then allow you to read the text file pointed to by the file descriptor, one line at a time until the end of the file.

## 🛠️ Function Prototype
```c
char *get_next_line(int fd);
```
## 📋 Usage
```c
#include "get_next_line.h"
#include <fcntl.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## ⚠️ Return Value
* The line that was read when successful
* NULL if there is nothing else to read or if an error occurred

## 📊 Expected Behavior
* Repeated calls to get_next_line() should let you read the text file pointed to by the file descriptor, one line at a time
* The function should return the line that was read
* If there is nothing else to read or if an error occurred, it should return NULL
* The returned line should include the terminating \n character, except if the end of file was reached and does not end with a \n character