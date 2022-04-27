#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "user/user.h"

void clearBuffer(char *buf)
{
  for (int i = 0; i < 10; i++)
  {
    buf[i] = 0;
  }
}

int lseektest(void)
{

  char prepared_buf[10] = "ABCDEFGHI\n";

  int failed = 0;

  int fd = open("/TESTFILE", O_RDONLY);
  if (fd < 0)
  {
    fprintf(2, "Failed to Open /TESTFILE\n");
    return -1;
  }

  int ret = lseek(fd, 3, SEEK_SET);
  if (ret < 0)
  {
    fprintf(2, "lseek failed with SEEK_SET");
    return -1;
  }

  char buffer[10];
  read(fd, buffer, 10);
  if (strcmp(buffer, &prepared_buf[3]) == 0)
  {
    fprintf(1, "Test passed ==> SEEK_SET\n");
  }
  else
  {
    fprintf(2, "Test failed =/=> SEEK_SET\n");
    fprintf(2, "Buffer: %s Should be: %s\n", buffer, &prepared_buf[3]);
    failed = 1;
  }

  lseek(fd, 3, SEEK_SET);
  clearBuffer(buffer);

  ret = lseek(fd, 2, SEEK_CUR);
  if (ret < 0)
  {
    fprintf(2, "lseek failed with SEEK_CUR\n");
    return -1;
  }

  read(fd, buffer, 10);
  if (strcmp(buffer, &prepared_buf[5]) != 0)
  {
    fprintf(2, "Test failed =/=> SEEK_CUR\n");
    fprintf(2, "Buffer: %s Should be: %s\n", buffer, &prepared_buf[5]);
    failed = 1;
  }
  else
  {
    fprintf(1, "Test passed ==> SEEK_CUR\n");
  }

  lseek(fd, 0, SEEK_SET);
  clearBuffer(buffer);

  // Test lseek: SEEK_END
  ret = lseek(fd, -2, SEEK_END);
  if (ret < 0)
  {
    fprintf(2, "lseek with SEEK_END\n");
    return -1;
  }

  read(fd, buffer, 10);
  if (strcmp(buffer, &prepared_buf[8]) == 0)
  {
    printf("Test passed ==> SEEK_END\n");
  }
  else
  {
    printf("Test failed at: SEEK_END\n");
    printf("--> \"%s\" != \"%s\"\n\n", buffer, &prepared_buf[8]);
    failed = 1;
  }

  lseek(fd, 0, SEEK_SET);
  clearBuffer(buffer);

  ret = lseek(fd, 4, SEEK_END);
  if (ret < 0)
  {
    fprintf(1, "Test passed ==> SEEK_END - Go beyond file size\n");
    fprintf(1, "lseek returend: %d\n", ret);
  }
  else
  {
    fprintf(2, "Test failed =/=> SEEK_END - Go beyond file size\n");
    fprintf(2, "lseek returend: %d\n", ret);
  }

  lseek(fd, 0, SEEK_SET);
  clearBuffer(buffer);

  ret = lseek(fd, -12, SEEK_END);
  if (ret < 0)
  {
    fprintf(1, "Test passed ==> SEEK_END - Go to negativ Offset\n");
    fprintf(1, "lseek returend: %d\n", ret);
  }
  else
  {
    fprintf(2, "Test failed =/=> SEEK_END - Go to negativ Offset\n");
    fprintf(2, "lseek returend: %d\n", ret);
  }

  lseek(fd, 0, SEEK_SET);
  clearBuffer(buffer);

  ret = lseek(fd, 12, SEEK_SET);
  if (ret < 0)
  {
    fprintf(1, "Test passed ==> SEEK_SET - Go beyond file size\n");
    fprintf(1, "lseek returend: %d\n", ret);
  }
  else
  {
    fprintf(2, "Test failed =/=> SEEK_SET - Go beyond file size\n");
    fprintf(2, "lseek returend: %d\n", ret);
  }

  lseek(fd, 0, SEEK_SET);
  clearBuffer(buffer);

  ret = lseek(fd, -3, SEEK_SET);
  if (ret < 0)
  {
    fprintf(1, "Test passed ==> SEEK_SET - Go to negativ Offset\n");
    fprintf(1, "lseek returend: %d\n", ret);
  }
  else
  {
    fprintf(2, "Test failed =/=> SEEK_SET - Go to negativ Offset\n");
    fprintf(2, "lseek returend: %d\n", ret);
  }

  if (failed)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

int main(int argc, char *argv[])
{
  if (lseektest() == 0)
  {
    fprintf(1, "Congratulations your lseek implementation is working correctly\n");
  }
  else
  {
    fprintf(2, "[X] One or more tests failed!\n");
  }
  exit(0);
}
