#include "STDIO.H"
#include "IMPORTANT.H"
#include <stdarg.h>

UINT8 strlen(const char* string) {
    UINT8 len = 0;
    while (*string != '\0')
    {
        len++;
        string++;
    }
    return len;
}

void print_char(char c) {
    __asm {
        mov ah, 0x0e
        mov al, c
        int 0x10
    }
}

void print_string(const char* string) {
    while (*string)
    {
        print_char(*string++);
		if (*string == '\n')
		{
			__asm {
				mov al, 0x0D	// moves the cursor to the beginning of the line
        		int 0x10	// calls int 10h interrupt
			}
		}
		
    }
}

static void print_hexdigit(UINT8 i)
{
	if(i < 10) {
		print_char('0' + i);
	} else {
		print_char('a' + i - 10);
	}
}

static void print_hex(UINT16 i)
{
	int j;
	for(j = 28; j >= 0; j = j - 4) {
		print_hexdigit((i >> j) & 0x0f);
	}
}

static void print_int(UINT16 i)
{
	int f, d;
	if(i < 0 && i != 0) {
		print_char('-');
		i = -i;
	}

	f = 1;
	while((i / f) >= 10) {
		f *= 10;
	}
	while(f > 0) {
		d = i / f;
		print_char('0' + d);
		i = i - d * f;
		f = f / 10;
	}
}

static void print_uint(UINT16 u)
{
	int f, d;
	f = 1;
	while((u / f) >= 10) {
		f *= 10;
	}
	while(f > 0) {
		d = u / f;
		print_char('0' + d);
		u = u - d * f;
		f = f / 10;
	}
}

void printf(const char *s, ...)
{
	va_list args;

	UINT16 u;
	UINT16 i;
	char *str;

	va_start(args, s);

	while(*s) {
		if(*s != '%') {
			print_char(*s);
		} else {
			s++;
			switch (*s) {
			case 'd':
				i = va_arg(args, UINT16);
				print_int(i);
				break;
			case 'u':
				u = va_arg(args, UINT16);
				print_uint(u);
				break;
			case 'x':
				u = va_arg(args, UINT16);
				print_hex(u);
				break;
			case 's':
				str = va_arg(args, char *);
				print_string(str);
				break;
			case 'c':
				u = va_arg(args, UINT16);
				print_char(u);
				break;
			case 0:
				return;
				break;
			default:
				print_char(*s);
				break;
			}
		}
		if (*s == '\n')
		{
			__asm {
				mov al, 0x0D	// moves the cursor to the beginning of the line
        		int 0x10	// calls int 10h interrupt
			}
		}
		s++;
	}
	va_end(args);
}