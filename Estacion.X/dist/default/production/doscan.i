# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 285 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include/language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2


# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/ctype.h" 1 3







# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/features.h" 1 3
# 9 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/ctype.h" 2 3

int isalnum(int);
int isalpha(int);
int isblank(int);
int iscntrl(int);
int isdigit(int);
int isgraph(int);
int islower(int);
int isprint(int);
int ispunct(int);
int isspace(int);
int isupper(int);
int isxdigit(int);
int tolower(int);
int toupper(int);
# 4 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/errno.h" 1 3
# 12 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/errno.h" 3
extern int errno;
# 5 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdarg.h" 1 3




# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/musl_xc8.h" 1 3
# 6 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdarg.h" 2 3


# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 1 3
# 12 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef void * va_list[1];
# 174 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef __int24 int24_t;
# 210 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef __uint24 uint24_t;
# 9 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdarg.h" 2 3

#pragma intrinsic(__va_start)
#pragma intrinsic(__va_arg)

extern void * __va_start(void);
extern void * __va_arg(void *, ...);
# 6 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stddef.h" 1 3
# 19 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stddef.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 1 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef long int wchar_t;
# 128 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned size_t;
# 138 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef int ptrdiff_t;
# 20 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stddef.h" 2 3
# 7 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdint.h" 1 3
# 26 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 1 3
# 133 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned __int24 uintptr_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef __int24 intptr_t;
# 164 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;
# 179 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef long int32_t;





typedef long long int64_t;
# 194 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef long long intmax_t;





typedef unsigned char uint8_t;




typedef unsigned short uint16_t;
# 215 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned long uint32_t;





typedef unsigned long long uint64_t;
# 235 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef unsigned long long uintmax_t;
# 27 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdint.h" 2 3

typedef int8_t int_fast8_t;

typedef int64_t int_fast64_t;


typedef int8_t int_least8_t;
typedef int16_t int_least16_t;

typedef int24_t int_least24_t;
typedef int24_t int_fast24_t;

typedef int32_t int_least32_t;

typedef int64_t int_least64_t;


typedef uint8_t uint_fast8_t;

typedef uint64_t uint_fast64_t;


typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;

typedef uint24_t uint_least24_t;
typedef uint24_t uint_fast24_t;

typedef uint32_t uint_least32_t;

typedef uint64_t uint_least64_t;
# 148 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/stdint.h" 1 3
typedef int16_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint16_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 149 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdint.h" 2 3
# 8 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdio.h" 1 3
# 24 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdio.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 1 3
# 17 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef void * __isoc_va_list[1];
# 143 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef __int24 ssize_t;
# 255 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef long long off_t;
# 409 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef struct _IO_FILE FILE;
# 25 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdio.h" 2 3
# 52 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdio.h" 3
typedef union _G_fpos64_t {
 char __opaque[16];
 double __align;
} fpos_t;

extern FILE *const stdin;
extern FILE *const stdout;
extern FILE *const stderr;





FILE *fopen(const char *restrict, const char *restrict);
FILE *freopen(const char *restrict, const char *restrict, FILE *restrict);
int fclose(FILE *);

int remove(const char *);
int rename(const char *, const char *);

int feof(FILE *);
int ferror(FILE *);
int fflush(FILE *);
void clearerr(FILE *);

int fseek(FILE *, long, int);
long ftell(FILE *);
void rewind(FILE *);

int fgetpos(FILE *restrict, fpos_t *restrict);
int fsetpos(FILE *, const fpos_t *);

size_t fread(void *restrict, size_t, size_t, FILE *restrict);
size_t fwrite(const void *restrict, size_t, size_t, FILE *restrict);

int fgetc(FILE *);
int getc(FILE *);
int getchar(void);





int ungetc(int, FILE *);
int getch(void);

int fputc(int, FILE *);
int putc(int, FILE *);
int putchar(int);





void putch(char);

char *fgets(char *restrict, int, FILE *restrict);

char *gets(char *);


int fputs(const char *restrict, FILE *restrict);
int puts(const char *);

__attribute__((__format__(__printf__, 1, 2)))
int printf(const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int fprintf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 2, 3)))
int sprintf(char *restrict, const char *restrict, ...);
__attribute__((__format__(__printf__, 3, 4)))
int snprintf(char *restrict, size_t, const char *restrict, ...);

__attribute__((__format__(__printf__, 1, 0)))
int vprintf(const char *restrict, __isoc_va_list);
int vfprintf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 2, 0)))
int vsprintf(char *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__printf__, 3, 0)))
int vsnprintf(char *restrict, size_t, const char *restrict, __isoc_va_list);

__attribute__((__format__(__scanf__, 1, 2)))
int scanf(const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int fscanf(FILE *restrict, const char *restrict, ...);
__attribute__((__format__(__scanf__, 2, 3)))
int sscanf(const char *restrict, const char *restrict, ...);

__attribute__((__format__(__scanf__, 1, 0)))
int vscanf(const char *restrict, __isoc_va_list);
int vfscanf(FILE *restrict, const char *restrict, __isoc_va_list);
__attribute__((__format__(__scanf__, 2, 0)))
int vsscanf(const char *restrict, const char *restrict, __isoc_va_list);

void perror(const char *);

int setvbuf(FILE *restrict, char *restrict, int, size_t);
void setbuf(FILE *restrict, char *restrict);

char *tmpnam(char *);
FILE *tmpfile(void);




FILE *fmemopen(void *restrict, size_t, const char *restrict);
FILE *open_memstream(char **, size_t *);
FILE *fdopen(int, const char *);
FILE *popen(const char *, const char *);
int pclose(FILE *);
int fileno(FILE *);
int fseeko(FILE *, off_t, int);
off_t ftello(FILE *);
int dprintf(int, const char *restrict, ...);
int vdprintf(int, const char *restrict, __isoc_va_list);
void flockfile(FILE *);
int ftrylockfile(FILE *);
void funlockfile(FILE *);
int getc_unlocked(FILE *);
int getchar_unlocked(void);
int putc_unlocked(int, FILE *);
int putchar_unlocked(int);
ssize_t getdelim(char **restrict, size_t *restrict, int, FILE *restrict);
ssize_t getline(char **restrict, size_t *restrict, FILE *restrict);
int renameat(int, const char *, int, const char *);
char *ctermid(char *);







char *tempnam(const char *, const char *);
# 9 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdlib.h" 1 3
# 21 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdlib.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 1 3
# 22 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdlib.h" 2 3

int atoi (const char *);
long atol (const char *);

long long atoll (const char *);

double atof (const char *);


float strtof (const char *restrict, char **restrict);
double strtod (const char *restrict, char **restrict);
long double strtold (const char *restrict, char **restrict);



long strtol (const char *restrict, char **restrict, int);
unsigned long strtoul (const char *restrict, char **restrict, int);

long long strtoll (const char *restrict, char **restrict, int);
unsigned long long strtoull (const char *restrict, char **restrict, int);


unsigned long __strtoxl(const char * s, char ** endptr, int base, char is_signed);

unsigned long long __strtoxll(const char * s, char ** endptr, int base, char is_signed);
# 55 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdlib.h" 3
int rand (void);
void srand (unsigned);

void *malloc (size_t);
void *calloc (size_t, size_t);
void *realloc (void *, size_t);
void free (void *);

          void abort (void);
int atexit (void (*) (void));
          void exit (int);
          void _Exit (int);

void *bsearch (const void *, const void *, size_t, size_t, int (*)(const void *, const void *));







__attribute__((nonreentrant)) void qsort (void *, size_t, size_t, int (*)(const void *, const void *));

int abs (int);
long labs (long);

long long llabs (long long);


typedef struct { int quot, rem; } div_t;
typedef struct { long quot, rem; } ldiv_t;

typedef struct { long long quot, rem; } lldiv_t;


div_t div (int, int);
ldiv_t ldiv (long, long);

lldiv_t lldiv (long long, long long);


typedef struct { unsigned int quot, rem; } udiv_t;
typedef struct { unsigned long quot, rem; } uldiv_t;
udiv_t udiv (unsigned int, unsigned int);
uldiv_t uldiv (unsigned long, unsigned long);
# 10 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/string.h" 1 3
# 25 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/string.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 1 3
# 421 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/alltypes.h" 3
typedef struct __locale_struct * locale_t;
# 26 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/string.h" 2 3

void *memcpy (void *restrict, const void *restrict, size_t);
void *memmove (void *, const void *, size_t);
void *memset (void *, int, size_t);
int memcmp (const void *, const void *, size_t);
void *memchr (const void *, int, size_t);

char *strcpy (char *restrict, const char *restrict);
char *strncpy (char *restrict, const char *restrict, size_t);

char *strcat (char *restrict, const char *restrict);
char *strncat (char *restrict, const char *restrict, size_t);

int strcmp (const char *, const char *);
int strncmp (const char *, const char *, size_t);

int strcoll (const char *, const char *);
size_t strxfrm (char *restrict, const char *restrict, size_t);

char *strchr (const char *, int);
char *strrchr (const char *, int);

size_t strcspn (const char *, const char *);
size_t strspn (const char *, const char *);
char *strpbrk (const char *, const char *);
char *strstr (const char *, const char *);
char *strtok (char *restrict, const char *restrict);

size_t strlen (const char *);

char *strerror (int);




char *strtok_r (char *restrict, const char *restrict, char **restrict);
int strerror_r (int, char *, size_t);
char *stpcpy(char *restrict, const char *restrict);
char *stpncpy(char *restrict, const char *restrict, size_t);
size_t strnlen (const char *, size_t);
char *strdup (const char *);
char *strndup (const char *, size_t);
char *strsignal(int);
char *strerror_l (int, locale_t);
int strcoll_l (const char *, const char *, locale_t);
size_t strxfrm_l (char *restrict, const char *restrict, size_t, locale_t);




void *memccpy (void *restrict, const void *restrict, int, size_t);
# 11 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 1 "C:/Program Files (x86)/Microchip/MPLABX/v5.35/packs/Microchip/PIC18Fxxxx_DFP/1.2.26/xc8\\pic\\include/inline.h" 1 3
# 12 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/stdbool.h" 1 3
# 13 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/limits.h" 1 3
# 10 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/limits.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/bits/limits.h" 1 3
# 11 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\include\\c99/limits.h" 2 3
# 14 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c" 2
# 54 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c"
static _Bool asup;
static int width;


static int ncnv, nmatch;
# 71 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c"
static char dbuf[80];


static void skipws(FILE *fp)
{
    int c;

    while ((c = fgetc(fp)) != (-1)) {
        if (!(((c == ' ') || ((unsigned char)((c)-'\t') < 5)))) {
            ungetc(c, fp);
            break;
        }
    }
}
# 112 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c"
static int atod(FILE *fp, long long *pll)
{
    char *ep;
    int c, i, w;


    skipws(fp);


    w = width ? width : sizeof(dbuf) - 1;
    i = 0;
    while ((i < w) && (i < (sizeof(dbuf) - 1))) {
        c = fgetc(fp);
        if (c == (-1) && (width || i==0)) {
            return c;
        }
        if (!i && ((c == '+') || (c == '-'))) {
            dbuf[i] = (char)c;
            ++i;
            ++nmatch;
            continue;
        }
        if (!(((unsigned char)((c)-'0')) < 10)) {
   if (c != (-1)) {
    ungetc(c, fp);
   }
            break;
        }
        dbuf[i] = (char)c;
        ++i;
        ++nmatch;
    }
    dbuf[i] = '\0';



    *pll = (long long)__strtoxll(&dbuf[0],&ep,10,1);




    return (errno || !i) ? (-1) - 1 : !asup;
}
# 274 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c"
static int is_inf_nan(FILE *fp, char first, int pos, int n) {
 int c, i, w;
 const char *m[2] = { "inf", "nan" };


 if (n < pos + 3) {
  return 0;
 }
 i = pos;
 w = ((((unsigned char)((first)-'A')) < 26) ? (first)|0x20 : (first)) == 'i' ? 0 : 1;
 dbuf[i++] = first;
 while (i < pos + 3) {
  c = fgetc(fp);
  if (c == (-1)) {
   return c;
  }
  if (((((unsigned char)((c)-'A')) < 26) ? (c)|0x20 : (c)) != m[w][i-pos]) {

   break;
  }
  dbuf[i++] = (char)c;
 }

 if (i < pos + 3) {

  ungetc(c, fp);
  while (i > pos) {
   ungetc(dbuf[--i], fp);
  }
  return 0;
 }
 return 3;
}

static int atoaefg(FILE *fp, long double *pld)
{
    char *ep;
    int c, e, i, w, s, j, n;
 _Bool d, hex;


    skipws(fp);


    w = width ? width : sizeof(dbuf) - 1;
    n = w < (sizeof(dbuf) - 1) ? w : sizeof(dbuf) - 1;
    s = e = i = 0;
 hex = d = s = 0;
    while (i < n) {
        c = fgetc(fp);
        if (c == (-1) && (width || i==0)) {
            return c;
        }
        if (!s && ((c == '+') || (c == '-'))) {

            if (!(i == 0 || i == e)) {
                ungetc(c, fp);
                break;
            }
            s = 1;
            dbuf[i] = (char)c;
            ++i;
            ++nmatch;
            continue;
        }
        if (!d && (c == '.')) {

            if (e) {
                ungetc(c, fp);
                break;
            }
            d = 1;
            dbuf[i] = (char)c;
            ++i;
            ++nmatch;
            continue;
        }
        if (!e && (hex ? (((((unsigned char)((c)-'A')) < 26) ? (c)|0x20 : (c)) == 'p') : (((((unsigned char)((c)-'A')) < 26) ? (c)|0x20 : (c)) == 'e'))) {
            e = i + 1;
            s = 0;
            dbuf[i] = (char)c;
            ++i;
            ++nmatch;
            continue;
        }
        if (!e && i == s + 1 && ((((unsigned char)((c)-'A')) < 26) ? (c)|0x20 : (c)) == 'x' && dbuf[i-1] == '0') {

            hex = 1;
            dbuf[i] = (char)c;
            ++i;
            ++nmatch;
            continue;
        }
        if (!(hex ? ((((unsigned char)((c)-'0')) < 10) || ((unsigned char)((c|32) - 'a') < 6)) : (((unsigned char)((c)-'0')) < 10))) {



   j = ((((unsigned char)((c)-'A')) < 26) ? (c)|0x20 : (c));
   if (s == i && (j == 'i' || j == 'n')) {
    j = is_inf_nan(fp, (char)c, i, n);
    if (j <= 0) {
     break;
    }
                i += j;
                nmatch += j;
   }
   else {
    ungetc(c, fp);
   }
   break;
        }
        dbuf[i] = (char)c;
        ++i;
        ++nmatch;
    }
    dbuf[i] = '\0';



 e = errno;
 errno = 0;
    *pld = strtof(&dbuf[0],&ep);

 d = errno != 0 && errno != 34;
 errno = e;

    return (d || !i || ep == &dbuf[0]) ? (-1) - 1 : !asup;
}
# 672 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c"
static int vfsfcnvrt(FILE *fp, char *fmt[], va_list ap)
{
    char *cp, ct[3];
    int c, i;
    long long ll;
    unsigned long long llu;
    long double f;
    void *vp;


    if ((*fmt)[0] == '%') {
        ++*fmt;

        asup = width = 0;
# 697 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c"
        width = atoi(*fmt);
        while ((((unsigned char)(((*fmt)[0])-'0')) < 10)) {
            ++*fmt;
        }




        ct[0] = (char)((((unsigned char)(((int)(*fmt)[0])-'A')) < 26) ? ((int)(*fmt)[0])|0x20 : ((int)(*fmt)[0]));
        if (ct[0]) {
            ct[1] = (char)((((unsigned char)(((int)(*fmt)[1])-'A')) < 26) ? ((int)(*fmt)[1])|0x20 : ((int)(*fmt)[1]));
            if (ct[1]) {
                ct[2] = (char)((((unsigned char)(((int)(*fmt)[2])-'A')) < 26) ? ((int)(*fmt)[2])|0x20 : ((int)(*fmt)[2]));
            }
        }
# 759 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c"
        if (*fmt[0] == 'd') {

            ++*fmt;
            i = atod(fp, &ll);
            if (!(i < 1)) {
                vp = (void *)(*(int * *)__va_arg(*(int * **)ap, (int *)0));
                *(int *)vp = (int)ll;
            }
            return i;
        }
# 955 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c"
        if ((ct[0] == 'a') || (ct[0] == 'e') || (ct[0] == 'f') || (ct[0] == 'g')) {


            ++*fmt;
            i = atoaefg(fp, &f);
            if (!(i < 1)) {
                vp = (void *)(*(float * *)__va_arg(*(float * **)ap, (float *)0));
                *(float *)vp = (float)f;
            }
            return i;
        }
        if (!strncmp(ct, "la", ((sizeof("le")/sizeof("le"[0]))-1)) || !strncmp(ct, "le", ((sizeof("lf")/sizeof("lf"[0]))-1)) || !strncmp(ct, "lf", ((sizeof("lf")/sizeof("lf"[0]))-1)) || !strncmp(ct, "lg", ((sizeof("lg")/sizeof("lg"[0]))-1))) {




            i = atoaefg(fp, &f);
            if (!(i < 1)) {
                if ((((unsigned char)(((int)(*fmt)[0])-'A')) < 26)) {
                    vp = (void *)(*(long double * *)__va_arg(*(long double * **)ap, (long double *)0));
                    *(long double *)vp = f;
                } else {
                    vp = (void *)(*(double * *)__va_arg(*(double * **)ap, (double *)0));
                    *(double *)vp = (double)f;
                }
            }
            *fmt += ((sizeof("la")/sizeof("la"[0]))-1);
            return i;
        }
# 1448 "C:\\Program Files\\Microchip\\xc8\\v3.00\\pic\\sources\\c99\\common\\doscan.c"
        if ((*fmt)[0] == '%') {
   skipws(fp);
   c = fgetc(fp);
   if (c == '%') {
    ++*fmt;
    ++nmatch;
    return 0;
   }
   else if (c != (-1)) {
    ungetc(c, fp);
   }
   return (-1) - 1;
        }


        ++*fmt;
        return 0;
    }


    c = fgetc(fp);
 if ((((*fmt[0] == ' ') || ((unsigned char)((*fmt[0])-'\t') < 5)))) {

  do {
   ++*fmt;
  } while((((*fmt[0] == ' ') || ((unsigned char)((*fmt[0])-'\t') < 5))));

  while ((((c == ' ') || ((unsigned char)((c)-'\t') < 5)))) {
   ++nmatch;
   c = fgetc(fp);
  }
  if (c != (-1)) {
   ungetc(c, fp);
  }
 }
 else if (c == *fmt[0]) {
        ++*fmt;
        ++nmatch;
    } else {
  if (c == (-1)) {
   return (-1);
  }
        ungetc(c, fp);
        return (-1) - 1;
    }

    return 0;
}

int vfscanf(FILE *fp, const char *fmt, va_list ap)
{
    char *cfmt;
    int n, saved_errno;

    cfmt = (char *)fmt;
    ncnv = nmatch = 0;
 saved_errno = errno;
    while (*cfmt) {
  errno = 0;
        n = vfsfcnvrt(fp, &cfmt, ap);
        if (n < 0) {
            break;
        }
        ncnv += n;
    }
 errno = saved_errno;
    if (n == (-1) && ncnv == 0) {
        return n;
    }

    return ncnv;
}
