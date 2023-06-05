#include "ft_nm.h"

int printfmt(int fd, char *fmt, ...) {
	va_list var;
	va_start(var, fmt);
	while (*fmt) {
		char c = *fmt++;
		if (c == '%') {
			switch (*fmt++) {
				char *s;
				case 'c':
					char c = va_arg(var, int);
					write(fd, &c, 1);
					break;
				case 's':
					s = va_arg(var, char *);
					write(fd, s, sstrlen(s));
					break;
				case 'p':
					void *p = va_arg(var, char *);
					s = utohex((unsigned long)p);
					write(fd, s, sstrlen(s));
					break;
				case 'd':
					int i = va_arg(var, int);
					s = itoascii(i);
					write(fd, s, sstrlen(s));
					break;
				case 'u':
					unsigned int u = va_arg(var, unsigned int);
					s = utoascii(u);
					write(fd, s, sstrlen(s));
					break;
				case 'x':
					unsigned int x = va_arg(var, unsigned int);
					s = utohex((unsigned long)x);
					write(fd, s, sstrlen(s));
					break;
			}
		}
		else
			write(fd, &c, 1);
	}
	va_end(var);
	return 0; // to fix, must return the lenght of the printed string
}
