#include "stdio_impl.h"
//#include <sys/ioctl.h>

size_t __stdout_write(FILE *f, const unsigned char *buf, size_t len)
{
  /*
  struct winsize wsz;
  f->write = __stdio_write;
  if (!(f->flags & F_SVB) && __syscall(SYS_ioctl, f->fd, TIOCGWINSZ, &wsz))
          f->lbf = -1;

  return __stdio_write(f, buf, len);
  */
  prints_l((char*)(f->wbase), f->wpos-f->wbase);
  prints_l((void*)buf, len);

  f->wend = f->buf + f->buf_size;
  f->wpos = f->wbase = f->buf;
  return f->wpos-f->wbase + len;
}
