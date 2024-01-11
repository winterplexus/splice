/*
**  @(#)modules.h
**
**  splice - modules
**  ----------------
**
**  copyright (c) 2020-2024 Code Construct Systems (CCS)
*/
#ifndef __MODULES_H
#define __MODULES_H

/*
** Standard C header files
*/
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <setjmp.h>
#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

/*
** Windows C header files
*/
#ifdef _WIN32
#include <fcntl.h>
#include <io.h>
#endif

/*
** Local modules header files
*/
#include "common.h"
#include "splice.h"
#include "options.h"
#include "platform.h"
#include "port.h"
#include "version.h"

#endif /* __MODULES_H */
