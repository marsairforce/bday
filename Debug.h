#ifndef DEBUG_H
#define DEBUG_H

#ifndef EXT
#  ifdef  PUT_STORAGE_HERE
#    define EXT
#  else
#    define EXT                             extern
#  endif
#endif

#if defined(FUNCPROTO) || defined(__STDC__) || defined(__cplusplus) || defined(c_plusplus)
#  ifndef DEBUG_PRINT
#    ifdef DEBUG
#      define DEBUG_PRINT(x) cout x; cout.flush()
#    else
#      define DEBUG_PRINT(x)
#    endif
#  endif
#endif

#ifdef	DEBUG

#include				<stdio.h>

extern	int				debug_flag;

#define	Enter(m) \
char *debug_module = m; \
if( debug_flag >= DEBUG ) \
{ \
  fprintf( stdout, "===> %s\n", m ); \
  fflush( stdout ); \
} \
else

#define	EnterLev(lev,m) \
char *debug_module = m; \
if( debug_flag >= lev ) \
{ \
  fprintf( stdout, "===> %s\n", m ); \
  fflush( stdout ); \
} \
else

#define XEnter(m) \
char *debug_module = m; \
if( 1 ) \
{ \
  debug_flag = DEBUG; \
  fprintf( stdout, "===> %s\n", m ); \
  fflush( stdout ); \
} \
else

#define	Value(f,v) \
if( debug_flag >= DEBUG ) \
{ \
  fprintf( stdout, f, v ); \
  fflush( stdout ); \
} \
else

#define	DExecute(c) \
if( debug_flag >= DEBUG ) \
{ \
  c; \
} \
else

#define	DExecuteLev(lev,c) \
if( debug_flag >= lev ) \
{ \
  c; \
} \
else

#define	Leave(v) \
if( 1 ) \
{ \
  if( debug_flag >= DEBUG ) \
  { \
    fprintf( stdout, "<=== %s: %d\n", debug_module, v ); \
    fflush( stdout ); \
  } \
  return( v ); \
} \
else

#define	LeaveLev(lev,v) \
if( 1 ) \
{ \
  if( debug_flag >= lev ) \
  { \
    fprintf( stdout, "<=== %s: %d\n", debug_module, v ); \
    fflush( stdout ); \
  } \
  return( v ); \
} \
else

#define XLeave(v) \
if( 1 ) \
{ \
  debug_flag = 0; \
  fprintf( stdout, "<=== %s: %d\n", debug_module, v ); \
  fflush( stdout ); \
  return( v ); \
} \
else

#define	NLeave(v) \
if( 1 ) \
{ \
  if( debug_flag >= DEBUG ) \
  { \
    fprintf( stdout, "<=== %s\n", debug_module ); \
    fflush( stdout ); \
  } \
  return( v ); \
} \
else

#define XNLeave(v) \
if( 1 ) \
{ \
  debug_flag = 0; \
  fprintf( stdout, "<=== %s\n", debug_module ); \
  fflush( stdout ); \
  return( v ); \
} \
else

#define	VLeave() \
if( 1 ) \
{ \
  if( debug_flag >= DEBUG ) \
  { \
    fprintf( stdout, "<=== %s\n", debug_module ); \
    fflush( stdout ); \
  } \
  return; \
} \
else

#define	VLeaveLev(lev) \
if( 1 ) \
{ \
  if( debug_flag >= lev ) \
  { \
    fprintf( stdout, "<=== %s\n", debug_module ); \
    fflush( stdout ); \
  } \
  return; \
} \
else

#define XVLeave() \
if( 1 ) \
{ \
  debug_flag = 0; \
  fprintf( stdout, "<=== %s\n", debug_module ); \
  fflush( stdout ); \
  return; \
} \
else

#define	DLeave() \
if( 1 ) \
{ \
  if( debug_flag >= DEBUG ) \
  { \
    fprintf( stdout, "<=== %s\n", debug_module ); \
    fflush( stdout ); \
  } \
} \
else

#define XDLeave() \
if( 1 ) \
{ \
  debug_flag = 0; \
  fprintf( stdout, "<=== %s\n", debug_module ); \
  fflush( stdout ); \
} \
else

#else

#define	Enter(m);
#define	EnterLev(lev,m);
#define	XEnter(m);
#define	Value(f,v);
#define DExecute(c);
#define DExecuteLev(lev,c);
#define	Leave(v)	return(v)
#define	LeaveLev(lev,v)	return(v)
#define	XLeave(v)	return(v)
#define	NLeave(v)	return(v)
#define	XNLeave(v)	return(v)
#define	VLeave()	return
#define	VLeaveLev(lev)	return
#define	XVLeave()	return
#define	DLeave();
#define	XDLeave();

#endif

#define	FATAL(x) \
if( 1 ) \
{ \
  fprintf x ; \
  exit( -1 ); \
} \
else


#endif

