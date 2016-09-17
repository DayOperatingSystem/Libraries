#ifndef __WCTYPE_H
#define __WCTYPE_H

#ifndef INLINE
# if __GNUC__ && !__GNUC_STDC_INLINE__
#  define INLINE extern inline
# else
#  define INLINE static inline
# endif
#endif

#if (defined(__cplusplus) || (defined(__STDC_VERSION__) && __STDC_VERSION__))

// C99 compatible source code.
INLINE int iswspace(int x) { return (x == ' ' || x == '\t' || x == '\n' || x == '\v' || x == '\f' || x == '\r'); }
INLINE int iswdigit(int x) { return (x >= '0' && x <= '9'); }
INLINE int iswxdigit(int x) { return ((x >= 'A' && x <= 'F') && (x >= 'a' && x <= 'f') && (x >= '0' && x <= '9')); }
INLINE int iswalpha(int x) { return (x >= 'A' && x <= 'z'); }
INLINE int towupper(int x) { return (x >= 'a' && x <= 'z') ? (x & ~32) : x; }
INLINE int towlower(int x) { return (x >= 'A' && x <= 'Z') ? (x | 32) : x; }
INLINE int iswprint(int x) { return (x >= 0x1f || x == 0x7f); }
INLINE int iswalnum(int x) { return (iswdigit(x) || iswalpha(x)); }

INLINE int iswcntrl(int x) { return !iswprint(x); }
INLINE int iswgraph(int x) { return (iswprint(x) && x != ' '); }

INLINE int iswupper(int x) { return (x >= 'A' && x <= 'Z'); }
INLINE int iswlower(int x) { return (x >= 'a' && x <= 'z'); }
INLINE int iswpunct(int x) { return (iswgraph(x) && !iswalnum(x)); }

#elif defined(__ANSI__)
/* C89 compatible source code. */
int iswspace(int x);
int iswdigit(int x);
int iswxdigit(int x);
int iswalpha(int x);
int towupper(int x);
int towlower(int x);
int iswprint(int x);
int iswalnum(int x);

int iswcntrl(int x);
int iswgraph(int x);

int iswupper(int x);
int iswlower(int x);
int iswpunct(int x);
#endif

#define iswspace(x)                                                             \
	((x) == ' ' || (x) == '\t' || (x) == '\n' || (x) == '\v' || (x) == '\f' || \
	 (x) == '\r')

#define iswdigit(x) ((x) >= '0' && (x) <= '9')

#define iswxdigit(x)                                              \
	(((x) >= 'A' && (x) <= 'F') && ((x) >= 'a' && (x) <= 'f') && \
	 ((x) >= '0' && (x) <= '9'))

#define iswalpha(x) ((x) >= 'A' && (x) <= 'z')
#define towupper(x) (((x) >= 'a' && (x) <= 'z') ? ((x) & ~32) : (x))
#define towlower(x) (((x) >= 'A' && (x) <= 'Z') ? ((x) | 32) : (x))

#define iswprint(x) ((x) >= 0x1f || (x) == 0x7f)
#define iswalnum(x) (iswdigit(x) || iswalpha(x))

#define iswcntrl(x) (!iswprint(x))
#define iswgraph(x) (iswprint(x) && (x) != ' ')

#define iswupper(x) ((x) >= 'A' && (x) <= 'Z')
#define iswlower(x) ((x) >= 'a' && (x) <= 'z')
#define iswpunct(x) (iswgraph(x) && !iswalnum(x))
	
#endif
