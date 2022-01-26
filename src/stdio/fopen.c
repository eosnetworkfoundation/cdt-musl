#include "stdio_impl.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>

__attribute__((import_name("close_file"))) hidden weak void close_file(int fd);

FILE *fopen(const char *restrict filename, const char *restrict mode)
{
	FILE *f;
	int fd;
	int flags;

	/* Check for valid initial mode character */
	if (!strchr("rwa", *mode)) {
		errno = EINVAL;
		return 0;
	}

#if 0
   /* Compute the flags to pass to open() */
	flags = __fmodeflags(mode);

	fd = sys_open(filename, flags, 0666);
	if (fd < 0) return 0;
	if (flags & O_CLOEXEC)
		__syscall(SYS_fcntl, fd, F_SETFD, FD_CLOEXEC);
#endif
   fd = open_file(filename, strlen(filename), mode, strlen(mode));
	if (fd < 0) return 0;
        
	f = __fdopen(fd, mode);
	if (f) return f;

   // __syscall(SYS_close, fd);
   close_file(fd);
	return 0;
}

weak_alias(fopen, fopen64);
