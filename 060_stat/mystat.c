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
   case S_IFBLK:  fileType = "block special file"; break;
   case S_IFCHR:  fileType = "character special file"; break;
   case S_IFDIR:  fileType = "directory"; break;
   case S_IFIFO:  fileType = "fifo"; break;
   case S_IFLNK:  fileType = "symbolic link"; break;
   case S_IFREG:  fileType = "regular file"; break;
   case S_IFSOCK: fileType = "socket"; break;
   default:       fileType = "unknown?"; break;
  }
    
  printf("  Size: %-10lu\tBlocks: %-10lu IO Block: %-6lu %s\n",
	 buf->st_size, buf->st_blocks, buf->st_blksize, fileType);
    
}

/*
line3() takes a pointer to a stat struct and prints line 3 from stat
*/
void line3(struct stat * buf){
  printf("Device: %lxh/%lud\tInode: %-10lu  Links: %lu\n",
	 buf->st_dev,buf->st_dev,buf->st_ino,buf->st_nlink);
}

/*
line4() takes a pointer to a stat struct and prints Access portion of 
line 4 from stat.
Uses switch/case to construct human-readable description of permissions.
 */

void line4_Access(struct stat * buf){
  char permissions[10+1] = "----------\0";

  // checks filetype using macros for interpretting bits
  switch (buf->st_mode & S_IFMT){
   case S_IFBLK: permissions[0] = 'b'; break;
   case S_IFCHR: permissions[0] = 'c'; break;
   case S_IFDIR: permissions[0] = 'd'; break;
   case S_IFIFO: permissions[0] = 'p'; break;
   case S_IFLNK: permissions[0] = 'l'; break;
   case S_IFREG: permissions[0] = '-'; break;
   case S_IFSOCK: permissions[0] = 's'; break;
  }

  // check read,write, and executable permissions for owner
  if (!((buf->st_mode & S_IRUSR) == 0)) {
    permissions[1] = 'r';
  }
  if (!((buf->st_mode & S_IWUSR) == 0)) {
    permissions[2] = 'w';
  }
  if (!((buf->st_mode & S_IXUSR) == 0)) {
    permissions[3] = 'x';
  }

  // check read,write, and executable permissions for group
  if (!((buf->st_mode & S_IRGRP) == 0)) {
    permissions[4] = 'r';
  }
  if (!((buf->st_mode & S_IWGRP) == 0)) {
    permissions[5] = 'w';
  }
  if (!((buf->st_mode & S_IXGRP) == 0)) {
    permissions[6] = 'x';
  }

  // check read,write, and executable permissions for others
  if (!((buf->st_mode & S_IROTH) == 0)) {
    permissions[7] = 'r';
  }
  if (!((buf->st_mode & S_IWOTH) == 0)) {
    permissions[8] = 'w';
  }
  if (!((buf->st_mode & S_IXOTH) == 0)) {
    permissions[9] = 'x';
  }
  
  printf("Access: (%04o/%s)", (buf->st_mode & ~S_IFMT), permissions);
}

/*
line4_UidGid() takes pointer to stat struct and prints Uid and Gid part
 of line 4 from stat. Uses getpwuid() and getgrgid() methods to get
username and group name.
 */

void line4_UidGid(struct stat * buf){
  struct passwd *pwd;
  struct group *grp;

  // create passwd struct with user id and username info
  pwd = getpwuid(buf->st_uid);
  // create group struct with group id and group name info
  grp = getgrgid(buf->st_gid);
  
  printf("  Uid: (%5d/%8s)   Gid: (%5d/%8s)\n",
	 buf->st_uid,pwd->pw_name,buf->st_gid,grp->gr_name);
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

/*
printTimeStrings() takes a stat struct and prints the time of last access,
modification, and status change associated with the file.
Makes a call to time2str() to construct time string.
 */
void printTimeStrings (struct stat buf){
  char *accessStr = time2str(&buf.st_atime, buf.st_atim.tv_nsec);
  char *modStr = time2str(&buf.st_mtime, buf.st_mtim.tv_nsec);
  char *changeStr = time2str(&buf.st_ctime, buf.st_ctim.tv_nsec);
  
  printf("Access: %s\nModify: %s\nChange: %s\n Birth: -\n",
	 accessStr, modStr, changeStr);
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

  // print 3rd line of stat
  line3(& fileInfo);

  // print 4th line of stat
  line4_Access(& fileInfo); line4_UidGid(& fileInfo);

  // print 4 time strings from stat
  printTimeStrings(fileInfo);

}
