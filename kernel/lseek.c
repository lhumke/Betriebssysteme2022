#include "kernel/types.h"
#include "kernel/fcntl.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

/*
  SEEK_SET
  The file offset is set to offset bytes.

  SEEK_CUR
  The file offset is set to its current location plus offset bytes.

  SEEK_END
  The file offset is set to the size of the file plus offset bytes.
*/

int lseek(int fd, int offset, int whence){
  struct stat st;
  if(fstat(fd, &st) < 0)
    return -1;

  if(fd < 0 || offset < 0 || whence < 0 || whence > 2 || st.type != T_FILE)
  {
    return -1;
  }


  char* buf[offset*8];
  int read_bytes;
  
  switch (whence)
  {
  case SEEK_SET:
    //TODO:I need to reset the file Offset somehow
    return -1;
    break;
  case SEEK_CUR:
    read_bytes = read(fd, buf, offset);
    if(read_bytes < 0){
      return -1;
    }else{
      return read_bytes;
    }
    break;
  case SEEK_END:;  // SEEK_END
    char* byte = "H";
    while(read(fd, byte, sizeof(byte)) != 0);
    read_bytes = read(fd, buf, offset);
    if(read_bytes < 0){
      return -1;
    }else{
      return read_bytes;
    }
    break;
  
  default:
    return -1;
    break;
  }
  return -1;
}
