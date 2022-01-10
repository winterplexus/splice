/*
**  @(#)splice.h
**
**  splice - splice file functions
**  ------------------------------
**
**  copyright (c) 2020-2022 Code Construct Systems (CCS)
*/
#ifndef __SPLICE_H
#define __SPLICE_H

#include <setjmp.h>

/*
** Base name part number format
*/
#ifndef _BASE_NAME_PART_NUMBER_FORMAT
#ifdef  _WINDOWS
#define _BASE_NAME_PART_NUMBER_FORMAT "%s\\%s.%04ld"
#else
#define _BASE_NAME_PART_NUMBER_FORMAT "%s/%s.%04ld"
#endif
#else
#error  _BASE_NAME_PART_NUMBER_FORMAT is defined in another include file
#endif

/*
** Unwind buffer stack pointer
*/
extern jmp_buf unwind_buffer_sp;

/*
** Define exit application macro (unwind stack to last setjmp)
*/
#ifndef EXIT_APPLICATION
#define EXIT_APPLICATION(_code) longjmp(unwind_buffer_sp, _code)
#else
#error  EXIT_APPLICATION is defined in another include file
#endif

#endif /* __SPLICE_H */