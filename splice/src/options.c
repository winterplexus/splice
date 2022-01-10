/*
**  @(#)options.c
**
**  splice - command line options
**  -----------------------------
**
**  copyright (c) 2020-2022 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Local function prototypes
*/
static void GetOptionValues(int, char **, options_t *);
static void SetDefaultOptions(options_t *);
static void StoreStringOption(int, string_c_t[], int, string_c_t, size_t);
static long ConvertStringToLong(string_c_t);
static void DisplayVersion(int);
static void DisplayUsage(void);

/*
** Get command line options
*/
void GetOptions(int argc, char **argv, options_t *opts) {
    /*
    ** Set default options
    */
    SetDefaultOptions(opts);

    /*
    ** Display usage if no argument; otherwise get option values
    */
    if (argc == 1) {
        DisplayUsage();
    }
    else {
        GetOptionValues(argc, argv, opts);
    }
}

/*
** Get option values
*/
static void GetOptionValues(int argc, char **argv, options_t *opts) {
    int i;

    /*
    ** Process each command line argument
    */
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            DisplayUsage();
        }
        else if (strcmp(argv[i], "-i") == 0) {
            StoreStringOption(argc, argv, ++i, opts->input_file_path, sizeof(opts->input_file_path) - 1);
        }
        else if (strcmp(argv[i], "-b") == 0) {
            StoreStringOption(argc, argv, ++i, opts->input_file_base_name, sizeof(opts->input_file_base_name) - 1);
        }
        else if (strcmp(argv[i], "-o") == 0) {
            StoreStringOption(argc, argv, ++i, opts->output_file_name, sizeof(opts->output_file_name) - 1);
        }
        else if (strcmp(argv[i], "-s") == 0) {
            opts->show_file_names = TRUE;
        }
        else if (strcmp(argv[i], "-v") == 0) {
            DisplayVersion(argc);
        }
        else {
            EXIT_APPLICATION(EXIT_FAILURE);
        }
    }

    /*
    ** Check input file base name
    */
    if (!strlen(opts->input_file_base_name)) {
        printf("error-> input file base name is empty or missing\n");
        EXIT_APPLICATION(EXIT_FAILURE);
    }
}

/*
** Set default options
*/
static void SetDefaultOptions(options_t *opts) {
    memset(opts->input_file_path, 0, _MAX_FILE_NAME_SIZE + 1);
    memset(opts->input_file_base_name, 0, _MAX_FILE_NAME_SIZE + 1);
    memset(opts->output_file_name, 0, _MAX_FILE_NAME_SIZE + 1);
    opts->show_file_names = FALSE;
}

/*
** Store string option
*/
static void StoreStringOption(int argc, string_c_t argv[], int i, string_c_t argument, size_t size) {
    if (argc < i || !argv[i]) {
        DisplayUsage();
    }
    assert(argv[i]);
    strcpy_p(argument, size, argv[i], size);
}

/*
** Convert string to long integer
*/
static long ConvertStringToLong(string_c_t value) {
    char *end;

    long chunk_size = strtol(value, &end, 10);
    if (errno == ERANGE) {
        printf("error-> chunk size value is out of range");
    }
    return (chunk_size);
}

/*
** Display version
*/
static void DisplayVersion(int argc) {
    printf("%s - splice text file utility\n", _VERSION_PRODUCT);
    printf("%s\n\n", _VERSION_RELEASE);

    /*
    ** Exit application (if no other command line arguments)
    */
    if (argc == 2) {
        EXIT_APPLICATION(EXIT_SUCCESS);
    }
}

/*
** Display usage
*/
static void DisplayUsage(void) {
    printf("usage: %s (options)\n\n", _VERSION_PRODUCT);
    printf("where (options) include:\n\n");
    printf("-i  [input file path]\n");
    printf("-b  [input file base name]\n");
    printf("-o  [output file name]\n");
    printf("-s  show file names\n");
    printf("-h  display usage\n");
    printf("-v  display version\n");

    /*
    ** Exit application
    */
    EXIT_APPLICATION(EXIT_SUCCESS);
}