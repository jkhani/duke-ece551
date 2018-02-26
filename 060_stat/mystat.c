#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <pwd.h>
#include <grp.h>
#include <unistd.h>

/*
line2() takes a pointer to a stat struct, checks the fileType against a set 
of possible cases to set fileType string
 */
void line2(struct stat * buf){
  // holds fileType string
  char * fileType;
  switch (buf->st_mode & S_IFMT){
   case S_IFBLK: fileType = "block special file"; break;
   case S_IFCHR: fileType = "character special file"; break;
   case S_IFDIR: fileType = "directory"; break;
   case S_IFIFO: fileType = "fifo"; break;
   case S_IFLNK: fileType = "symbolic link"; break;
   case S_IFREG: fileType = "regular file"; break;
   case S_IFSOCK: fileType = "socket"; break;
  }
    
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",buf->st_size,
	 buf->st_blocks, buf->st_blksize, fileType);
    
}
  

//This function is for Step 4
char * time2str(const time_t * when, long ns) {
  char * ans = malloc(128 * sizeof(*ans));
  char temp1[64];
  char temp2[32];
  const struct tm * t= localtime(when);
  strftime(temp1,512,"%Y-%m-%d %H:%M:%S",t);  
  strftime(temp2,32,"%z",t);
  snprintf(ans,128,"%s.%09ld %s", temp1, ns, temp2);
  return ans;
}

int main(int argc, char ** argv){
  // create struct for holding info from lstat (defined in <sys/stat.h>)
  struct stat fileInfo;

  // return error if path to specific file not provided
  if (argc !=2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    return EXIT_FAILURE;
  }

  // return error and explanation of error returned by lstat()
  if (lstat(argv[1], &fileInfo) < 0 ) {
    fprintf(stderr,"lstat() returned error\n");
    return EXIT_FAILURE;
  }

  // print 1st line of stat
  printf("  File: ‘%s’\n",argv[1]);

  // print 2nd line of stat
  line2(& fileInfo);

    
}
