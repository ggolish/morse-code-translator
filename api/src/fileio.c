#include "fileio.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_ERROR 1024

// Will be set if an error occurs
static char error_msg[MAX_ERROR];

char *read_file(const char *path)
{
  int fd = open(path, O_RDONLY);

  if(fd == -1) {
    sprintf(error_msg, "Unable to open file '%s'.", path);
    return NULL;
  }

  off_t file_size = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);

  char *contents = (char *)malloc(sizeof(char) * file_size + file_size);
  ssize_t nbytes = read(fd, contents, sizeof(char) * file_size);

  if(nbytes != file_size) {
    close(fd);
    sprintf(error_msg, "Unable to read file '%s'.", path);
    return NULL;
  }

  close(fd);
  return contents;
}

char *fileio_error()
{
  return error_msg;
}
