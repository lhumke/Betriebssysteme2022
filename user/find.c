#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char path[], char name[])
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(path, 0)) < 0)
  {
    fprintf(2, "Cannot open given path %s\n", path);
    return;
  }

  if (fstat(fd, &st) < 0)
  {
    fprintf(2, "Cannot get file stats %s\n", path);
    close(fd);
    return;
  }

  if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf)
  {
    printf("path too long\n");
    return;
  }
  strcpy(buf, path);
  p = buf + strlen(buf);
  *p++ = '/';
  while (read(fd, &de, sizeof(de)) == sizeof(de))
  {
    memmove(p, de.name, DIRSIZ);
    if (stat(buf, &st) < 0)
    {
      fprintf(2, "Cannot get file stats %s\n", path);
      continue;
    }
    if (st.type == T_DIR)
    {
      if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0 || strcmp(de.name, "") == 0)
        continue;
      find(buf, name);
    }

    if (strsub(de.name, name))
    {
      printf("%d  %s\n", st.type, buf);
    }
  }
  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    fprintf(2, "Not enough arguements\n");
    exit(0);
  }
  for (int i = 1; i < argc; i++)
    find(".", argv[i]);
  exit(0);
}
