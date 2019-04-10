//Zack frame buffer test
//based on this guys thing
//https://gist.github.com/FredEckert/3425429

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <stdint.h>

int main()  {

  int fd, x = 0, y = 0;
  struct fb_var_screeninfo vinfo;
  struct fb_fix_screeninfo finfo;
  uint8_t   *p;
  uint32_t   screensize;
  if ((fd = open("/dev/fb0", O_RDWR)) == -1)  {
  
    puts("shit");
    perror("open() :");
    exit(1);
  }
  
  
  
  if (ioctl(fd, FBIOGET_FSCREENINFO, &finfo) == -1) {
    
    puts("shit set fix");
    exit(1);
  }
  
  if (ioctl(fd, FBIOGET_VSCREENINFO, &vinfo) == -1) {
    
    puts("shit set var");
    exit(1);
  }
  //good call.
  printf("%dx%d, %dbpp\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);
  
  screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8;
  
  printf("buffer size: %d bytes\n", screensize);
  
  if ((p = mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == -1 )  {
	  
    perror("mmap(): ");
    exit(1);
  }
  
  for ( x =  0; x < 0xffff; x++ ) {
	  
    p[x] = 0x30;
  }
  
  munmap(p, screensize);
  close(fd);
  
  return 0;
}
