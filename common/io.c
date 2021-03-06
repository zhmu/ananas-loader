#include <loader/types.h>
#include <stdarg.h>
#include <loader/lib.h>
#include <loader/platform.h>

static const uint8_t hextab[16] = "0123456789abcdef";

int
putchar(int c)
{
	platform_putch(c);
	return c;
}

int
puts(const char* s)
{
	int n = 0;
	while(*s) {
		platform_putch(*s++);
		n++;
	}
	platform_putch('\n');
	return n;
}

static void
putnumber(void(*putch)(void*, int), void* v, unsigned int i)
{
	if (i >= 0x10000000) putch(v, hextab[(i >> 28) & 0xf]);
	if (i >= 0x1000000)  putch(v, hextab[(i >> 24) & 0xf]);
	if (i >= 0x100000)   putch(v, hextab[(i >> 20) & 0xf]);
	if (i >= 0x10000)    putch(v, hextab[(i >> 16) & 0xf]);
	if (i >= 0x1000)     putch(v, hextab[(i >> 12) & 0xf]);
	if (i >= 0x100)      putch(v, hextab[(i >>  8) & 0xf]);
	if (i >= 0x10)       putch(v, hextab[(i >>  4) & 0xf]);
	putch(v, hextab[i & 0xf]);
}

static void
putint(void(*putch)(void*, int), void* v, unsigned int n)
{
	/*
	 * Note that 1234 is just 1*10^3 + 2*10^2 + 3*10^1 + 4*10^0 =
	 * 1000 + 200 + 30 + 4. This means we have to figure out the highest power p
	 * of 10 first (p=3 in this case) and then print 'n divide. The digit we
	 * need to print is n % 10^p, so 1234 % 10^3 = 1, 234 % 10^2 = 2 etc)
	 */
	unsigned int i, p = 0, base = 1;
	for (i = n; i >= 10; i /= 10, p++, base *= 10);
	/* Write values from n/(p^10) .. n/1 */
	for (i = 0; i<= p; i++, base /= 10) {
		putch(v, '0' + (n / base) % 10);
	}
}

static void
vapprintf(const char* fmt, void(*putch)(void*, int), void* v, va_list ap)
{
	const char* s;
	uint32_t u32;
	uint64_t u64;

	while(*fmt) {
		if (*fmt != '%') {
			putch(v, *fmt++);
			continue;
		}

		/* formatted output */
		fmt++;

		switch(*fmt) {
			case 's': /* string */
				s = va_arg(ap, const char*);
				if (s != NULL) {
					while (*s)
						putch(v, *s++);
				} else {
					putch(v, '(');
					putch(v, 'n'); putch(v, 'u'); putch(v, 'l'); putch(v, 'l');
					putch(v, ')');
				}
				break;
			case 'c': /* char */
				putch(v, va_arg(ap, unsigned int));
				break;
			case 'x': /* hex int XXX assumed 32 bit */
			case 'X': /* hex int XXX assumed 32 bit */
				putnumber(putch, v, va_arg(ap, unsigned int));
				break;
			case 'u': /* unsigned integer */
			case 'd': /* decimal */
			case 'i': /* integer XXX */
				putint(putch, v, va_arg(ap, unsigned int));
				break;
			case 'p': /* pointer XXX assumed 64 bit */
				u64 = va_arg(ap, addr_t);
				putnumber(putch, v, u64 & 0xffffffff);
				break;
			case '$': /* shift-4: ipv4 address */
				u32 = va_arg(ap, uint32_t);
				putint(putch, v, (u32      ) & 0xff);
				putch(v, '.');
				putint(putch, v, (u32 >>  8) & 0xff);
				putch(v, '.');
				putint(putch, v, (u32 >> 16) & 0xff);
				putch(v, '.');
				putint(putch, v, (u32 >> 24));
				break;
			default: /* unknown, just print it */
				putch(v, '%');
				putch(v, *fmt);
				break;
		}
		fmt++;
	}
}

static void
printf_putch(void* v, int c)
{
	platform_putch(c);
}

void
vaprintf(const char* fmt, va_list ap)
{
	vapprintf(fmt, printf_putch, NULL, ap);
}

int
printf(const char* fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	vaprintf(fmt, ap);
	va_end(ap);

	return 0;
}

static void
sprintf_add(void* v, int c)
{
	char** string = (char**)v;
	**string = c;
	(*string)++;
}

int
sprintf(char* str, const char* fmt, ...)
{
	va_list ap;
	char* source = str;

	va_start(ap, fmt);
	vapprintf(fmt, sprintf_add, &str, ap);
	va_end(ap);
	sprintf_add(&str, 0);

	return str - source;
}

/* vim:set ts=2 sw=2: */
