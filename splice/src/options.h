/*
**  @(#)options.h
**
**  splice - command line options
**  -----------------------------
**
**  copyright (c) 2020-2022 Code Construct Systems (CCS)
*/
#ifndef __OPTIONS_H
#define __OPTIONS_H

/*
** Command line options structure and type
*/
typedef struct options_s {
        char input_file_path[_MAX_FILE_NAME_SIZE + 1];
        char input_file_base_name[_MAX_FILE_NAME_SIZE + 1];
        char output_file_name[_MAX_FILE_NAME_SIZE + 1];
        bool_c_t show_file_names;
} options_t;

/*
** Function prototypes
*/
extern void GetOptions(int, char **, options_t *);

#endif /* __OPTIONS_H */