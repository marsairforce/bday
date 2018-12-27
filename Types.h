// some common types used in this package
#ifndef TYPES_H
#define TYPES_H
enum Status { Failure=-1, Success=0};

#ifndef Boolean
enum Boolean { False=0, True=1};
#endif

#ifndef byte
#define byte unsigned char
#endif

#ifndef word
#define word unsigned short int
#endif

#ifndef dword
#define dword unsigned long int
#endif


#ifndef NULL
#  if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#      define NULL    0
#  else
#      define NULL    0L
#  endif
#endif

#endif