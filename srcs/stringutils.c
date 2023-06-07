#include "ft_nm.h"

/* --------------------------------------------------- */

int stringlen(const char *str) {
	int i = 0;

	while (str && str[i])
		i++;
	return i;
}

/* --------------------------------------------------- */

const char* stringerror(int errnum) {
    static const char* error_table[] = {
        "Success",
        "Operation not permitted",
        "No such file or directory",
        "No such process",
        "Interrupted system call",
        "Input/output error",
        "No such device or address",
        "Argument list too long",
        "Exec format error",
        "Bad file descriptor",
        "No child processes",
        "Resource temporarily unavailable",
        "Cannot allocate memory",
        "Permission denied",
        "Bad address",
        "Block device required",
        "Device or resource busy",
        "File exists",
        "Invalid cross-device link",
        "No such device",
        "Not a directory",
        "Is a directory",
        "Invalid argument",
        "Too many open files in system",
        "Too many open files",
        "Inappropriate ioctl for device",
        "Text file busy",
        "File too large",
        "No space left on device",
        "Illegal seek",
        "Read-only file system",
        "Too many links",
        "Broken pipe",
        "Numerical argument out of domain",
        "Numerical result out of range",
        "Resource deadlock avoided",
        "File name too long",
        "No locks available",
        "Function not implemented",
        "Directory not empty",
        "Too many levels of symbolic links",
        "Unknown error 41",
        "No message of desired type",
        "Identifier removed",
        "Channel number out of range",
        "Level 2 not synchronized",
        "Level 3 halted",
        "Level 3 reset",
        "Link number out of range",
        "Protocol driver not attached",
        "No CSI structure available",
        "Level 2 halted",
        "Invalid exchange",
        "Invalid request descriptor",
        "Exchange full",
        "No anode",
        "Invalid request code",
        "Invalid slot",
        "Unknown error 58",
        "Bad font file format",
        "Device not a stream",
        "No data available",
        "Timer expired",
        "Out of streams resources",
        "Machine is not on the network",
        "Package not installed",
        "Object is remote",
        "Link has been severed",
        "Advertise error",
        "Srmount error",
        "Communication error on send",
        "Protocol error",
        "Multihop attempted",
        "RFS specific error",
        "Bad message",
        "Value too large for defined data type",
        "Name not unique on network",
        "File descriptor in bad state",
        "Remote address changed",
        "Can not access a needed shared library",
        "Accessing a corrupted shared library",
        ".lib section in a.out corrupted",
        "Attempting to link in too many shared libraries",
        "Cannot exec a shared library directly",
        "Invalid or incomplete multibyte or wide character",
        "Interrupted system call should be restarted",
        "Streams pipe error",
        "Too many users",
        "Socket operation on non-socket",
        "Destination address required",
        "Message too long",
        "Protocol wrong type for socket",
        "Protocol not available",
        "Protocol not supported",
        "Socket type not supported",
        "Operation not supported",
        "Protocol family not supported",
        "Address family not supported by protocol",
        "Address already in use",
        "Cannot assign requested address",
        "Network is down",
        "Network is unreachable",
        "Network dropped connection on reset",
        "Software caused connection abort",
        "Connection reset by peer",
        "No buffer space available",
        "Transport endpoint is already connected",
        "Transport endpoint is not connected",
        "Cannot send after transport endpoint shutdown",
        "Too many references: cannot splice",
        "Connection timed out",
        "Connection refused",
        "Host is down",
        "No route to host",
        "Operation already in progress",
        "Operation now in progress",
        "Stale file handle",
        "Structure needs cleaning",
        "Not a XENIX named type file",
        "No XENIX semaphores available",
        "Is a named type file",
        "Remote I/O error",
        "Disk quota exceeded",
        "No medium found",
        "Wrong medium type",
        "Operation canceled",
        "Required key not available",
        "Key has expired",
        "Key has been revoked",
        "Key was rejected by service",
        "Owner died",
        "State not recoverable",
        "Operation not possible due to RF-kill",
        "Memory page has hardware error"
    };

    // Check if the errnum is within the valid range
    if (errnum >= 0 && (long unsigned int)errnum < sizeof(error_table) / sizeof(error_table[0]))
        return error_table[errnum];

    // Return a generic error message for invalid errnum
    return "Unknown error";
}

/* --------------------------------------------------- */

void printerror(const char* message) {
    int errnum = errno;
    printfmt(STDERR_FILENO, "%s: %s\n", message, stringerror(errnum));
}

/* --------------------------------------------------- */

int stringcmp(const char* str1, const char* str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }

    return *(unsigned char*)str1 - *(unsigned char*)str2;
}

/* --------------------------------------------------- */

static char	*protected_malloc(char *str, int size_n) {
	str = malloc(sizeof(char) * size_n + 1);
	if (!str)
		return (0);
	str[size_n] = 0;
	return (str);
}

/* --------------------------------------------------- */

static int	sizeof_n_i(int n) {
	int				size;
	unsigned int	tmp;

	if (n) {
		if (n < 0) {
			size = 1;
			tmp = n * -1;
		}
		else {
			size = 0;
			tmp = n;
		}
		while (tmp) {
			tmp = tmp / 10;
			size++;
		}
	}
	else
		size = 1;
	return (size);
}

static void	inttoascii(char *str, long int tmp, int size_n) {
	if (tmp < 0) {
		tmp = tmp * -1;
		str[0] = '-';
	}
	while (tmp) {
		str[size_n--] = tmp % 10 + 48;
		tmp = tmp / 10;
	}
}

char	*itoascii(int n) {
	int			size_n;
	char		*str;
	long int	tmp;

	str = NULL;
	tmp = n;
	size_n = sizeof_n_i(n) - 1;
	str = protected_malloc(str, sizeof_n_i(n));
	if (n && str)
		inttoascii(str, tmp, size_n);
	else if (!n && str)
		str[size_n] = '0';
	else
		return (0);
	return (str);
}

/* --------------------------------------------------- */

static int	sizeof_n_u(unsigned int n) {
	int				size;
	unsigned int	tmp;

	if (n) {
		size = 0;
		tmp = n;
		while (tmp) {
			tmp = tmp / 10;
			size++;
		}
	}
	else
		size = 1;
	return (size);
}

static void	unstoascii(char *str, unsigned long int tmp, int size_n) {
	while (tmp) {
		str[size_n--] = tmp % 10 + 48;
		tmp = tmp / 10;
	}
}

char	*utoascii(unsigned int n) {
	int					size_n;
	unsigned long int	tmp;
	char				*str;

	str = NULL;
	tmp = n;
	size_n = sizeof_n_u(n) - 1;
	str = protected_malloc(str, sizeof_n_u(n));
	if (n && str)
		unstoascii(str, tmp, size_n);
	else if (!n && str)
		str[size_n] = '0';
	else
		return (0);
	return (str);
}

/* --------------------------------------------------- */

static int	len_str(unsigned long nb) {
	int	len;

	if (nb == 0)
		return (1);
	len = 0;
	while (nb) {
		nb = nb / 16;
		len++;
	}
	return (len);
}

char	*utohex(unsigned long nb) {
	char	*str;
	char	*hexbase_low;
	int		len;

	hexbase_low = "0123456789abcdef";
	len = len_str(nb);
	str = (char *)malloc(sizeof(char) * len + 1);
	if (str == NULL)
		return (NULL);
	if (nb == 0)
		str[0] = '0';
	str[len] = 0;
	while (nb) {
		str[len - 1] = *(hexbase_low + nb % 16);
		nb = nb / 16;
		len--;
	}
	return (str);
}

/* --------------------------------------------------- */

void *memoryset(void *s, int c, size_t n) {
	while (n) {
		*((unsigned char *)s + n - 1) = (unsigned char)c;
		n--;
	}
	return (s);
}

/* --------------------------------------------------- */

char* unsignedlong_to_hex_string(unsigned long number) {
	int length = 0;
	unsigned long temp = number;

	// Calculate the length of the resulting hexadecimal string
	do {
		length++;
		temp >>= 4;  // Shift right by 4 bits (equivalent to dividing by 16)
	} while (temp != 0);

	char* str = malloc((length + 1) * sizeof(char));  // Allocate memory for the string

	// Convert the number to a hexadecimal string
	str[length] = '\0';  // Add null terminator

	// Build the hexadecimal string from right to left
	while (length-- > 0) {
		int remainder = number & 0xF;  // Extract the lowest 4 bits
		str[length] = (remainder < 10) ? ('0' + remainder) : ('a' + remainder - 10);
		number >>= 4;  // Shift right by 4 bits
	}

	return str;
}

/* --------------------------------------------------- */

char* convert_ulong_to_hex(unsigned long number, bool padding) {
	char* str = unsignedlong_to_hex_string(number);

	if (padding) {
		int paddingLength = 16 - stringlen(str);
		if (paddingLength > 0) {
			char* paddedStr = malloc((16 + 1) * sizeof(char));

			memoryset(paddedStr, '0', paddingLength);
			paddedStr[paddingLength] = '\0';

			stringcat(paddedStr, str);
			free(str);

			return paddedStr;
		}
	}

	return str;
}

/* --------------------------------------------------- */

void printfmt(int fd, char *fmt, ...) {
	va_list var;
	va_start(var, fmt);
	while (*fmt) {
		char c = *fmt++;
		if (c == '%') {
			bool padding = false;
			if (*fmt == '0') {
				padding = true;
				fmt++;
			}
			switch (*fmt++) {
				char *s;
				case 'c':
					char c = va_arg(var, int);
					write(fd, &c, 1);
					break;
				case 's':
					s = va_arg(var, char *);
					write(fd, s, stringlen(s));
					break;
				case 'p':
					void *p = va_arg(var, char *);
					s = utohex((unsigned long)p);
					write(fd, s, stringlen(s));
					free(s);
					break;
				case 'd':
					int i = va_arg(var, int);
					s = itoascii(i);
					write(fd, s, stringlen(s));
					free(s);
					break;
				case 'u':
					unsigned int u = va_arg(var, unsigned int);
					s = utoascii(u);
					write(fd, s, stringlen(s));
					free(s);
					break;
				case 'x':
					unsigned int x = va_arg(var, unsigned int);
					s = utohex((unsigned long)x);
					write(fd, s, stringlen(s));
					free(s);
					break;
				case 'l':
					if (*fmt++ == 'x') {
						unsigned int x = va_arg(var, unsigned int);
						s = convert_ulong_to_hex((unsigned long)x, padding);
						write(fd, s, stringlen(s));
						free(s);
						break;
					}
			}
		}
		else
			write(fd, &c, 1);
	}
	va_end(var);
	// An improvment of the function is to return the length of the printed string
}

/* --------------------------------------------------- */

char	*stringdup(const char *str) {
	int		i;
	char	*ptr;

	ptr = malloc(sizeof(char) * stringlen(str) + 1);
	if (!ptr)
		return (0);
	i = 0;
	while (*(str + i)) {
		*(ptr + i) = *(str + i);
		i++;
	}
	*(ptr + i) = 0;
	return (ptr);
}

/* --------------------------------------------------- */


size_t	stringcat(char *dest, const char *src) {
	unsigned int i = 0;

	while (dest[i] != '\0')
		i++;
	while (*src != '\0') {
		dest[i] = *src;
		src++;
		i++;
	}
	dest[i] = '\0';
	return stringlen(dest);
}

/* --------------------------------------------------- */

void sprintfmt(char *str, char *fmt, ...) {
	va_list var;
	va_start(var, fmt);
	while (*fmt) {
		char c[2] = {0};
		c[0] = *fmt++;
		if (c[0] == '%') {
			bool padding = false;
			if (*fmt == '0') {
				padding = true;
				fmt++;
			}
			switch (*fmt++) {
				char *s;
				case 'c':
					char c[2] = {0};
					c[0] = va_arg(var, int);
					stringcat(str, c);
					break;
				case 's':
					s = va_arg(var, char *);
					stringcat(str, s);
					break;
				case 'p':
					void *p = va_arg(var, char *);
					s = utohex((unsigned long)p);
					stringcat(str, s);
					free(s);
					break;
				case 'd':
					int i = va_arg(var, int);
					s = itoascii(i);
					stringcat(str, s);
					free(s);
					break;
				case 'u':
					unsigned int u = va_arg(var, unsigned int);
					s = utoascii(u);
					stringcat(str, s);
					free(s);
					break;
				case 'x':
					unsigned int x = va_arg(var, unsigned int);
					s = utohex((unsigned long)x);
					stringcat(str, s);
					free(s);
					break;
				case 'l':
					if (*fmt++ == 'x') {
						unsigned int x = va_arg(var, unsigned int);
						s = convert_ulong_to_hex((unsigned long)x, padding);
						stringcat(str, s);
						free(s);
						break;
					}
			}
		}
		else
			stringcat(str, c);
	}
	va_end(var);
	// An improvment of the function is to return the length of the writed string
}