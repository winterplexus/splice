/*
**  @(#)slice.c
**
**  splice - splice text file utility functions
**  -------------------------------------------
**
**  copyright (c) 2020-2025 Code Construct Systems (CCS)
*/
#include "modules.h"

/*
** Unwind buffer stack pointer
*/
jmp_buf unwind_buffer_sp;

/*
** Output file stream
*/
static FILE *output_file;

/*
** Input file buffer
*/
static char *input_file_buffer;

/*
** Local function prototypes
*/
static void SetSystemSignals(void);
static void InterruptHandler(int);
static void ProcessFiles(options_t *);
static void ProcessInputFile(options_t *, FILE *, string_c_t);

/*
** Slice text file utility driver
*/
int main(int argc, string_c_t argv[]) {
    options_t opts;

    /*
    ** Set system signals and if stack was unwound, close output file and free input file buffer
    */
    SetSystemSignals();
    if (setjmp(unwind_buffer_sp) != 0) {
        fclose_p(output_file);
        free(input_file_buffer);
        return (EXIT_FAILURE);
    }

    /*
    ** Get options
    */
    GetOptions(argc, argv, &opts);

    /*
    ** Process files
    */
    ProcessFiles(&opts);

    /*
    ** Return success return code
    */
    return (EXIT_SUCCESS);
}

/*
** Set system signals
*/
static void SetSystemSignals(void) {
    signal(SIGINT, InterruptHandler);
    signal(SIGTERM, InterruptHandler);
}

/*
** Interrupt handler
*/
static void InterruptHandler(int signal_number) {
    printf("signal detected (%d)!\n", signal_number);
    EXIT_APPLICATION(EXIT_SUCCESS);
}

/*
** Process files
*/
static void ProcessFiles(options_t *opts) {
    size_t part = 0;
    char input_file_name[_MAX_FILE_NAME_SIZE + 1];
    FILE *input_file;

    /*
    ** Open output file
    */
    fopen_p(&output_file, opts->output_file_name, (string_c_t)_F_RW_BIN);
    if (output_file == NULL) {
        printf("error-> unable to open output file: %s (%d)\n", opts->output_file_name, errno);
        EXIT_APPLICATION(EXIT_FAILURE);
    }

    /*
    ** Process each file in the input file path until either I/O error or when unable to open next file in input file path
    */
    for (;;) {
        memset(input_file_name, 0, sizeof(input_file_name));

        /*
        ** Format input file name using input file path, input file base name and part number
        */
        strfmt_p(input_file_name, _MAX_FILE_NAME_SIZE, (string_c_t)_BASE_NAME_PART_NUMBER_FORMAT, opts->input_file_path, opts->input_file_base_name, ++part);

        /*
        ** Open input file
        */
        fopen_p(&input_file, input_file_name, (string_c_t)_F_RO_BIN);
        if (input_file == NULL) {
            break;
        }

        /*
        ** Process input file
        */
        ProcessInputFile(opts, input_file, input_file_name);

        /*
        ** Close input file
        */
        fclose(input_file);
    }

    /*
    ** Close output file
    */
    fclose(output_file);
}

/*
** Process input file
*/
static void ProcessInputFile(options_t *opts, FILE *input_file, string_c_t input_file_name) {
    struct stat file_info;
    size_t bytes_read;

    /*
    ** Exit if unable to get input file size
    */
    if (stat(input_file_name, &file_info) != EXIT_SUCCESS) {
        printf("error-> unable to get input file size: %s (%d)\n", input_file_name, errno);
        EXIT_APPLICATION(EXIT_SUCCESS);
    }

    /*
    ** Allocate memory for input file buffer
    */
    if ((input_file_buffer = (char *)malloc(file_info.st_size + 1)) != NULL) {
        memset(input_file_buffer, 0, file_info.st_size + 1);

        /*
        ** Read every byte from input file into input file buffer
        */
        bytes_read = fread(input_file_buffer, 1, file_info.st_size, input_file);
        if (bytes_read) {
            if (opts->show_file_names == TRUE) {
                printf("%s\n", input_file_name);
            }

            /*
            ** Write contents of input file buffer to output file
            */
            if (input_file_buffer != NULL) {
                fwrite(input_file_buffer, 1, bytes_read, output_file);
            }

            /*
            ** Check for output file write error
            */
            if (ferror(output_file)) {
                printf("error-> unable to write to output file: %s (%d)\n", opts->output_file_name, errno);
                fclose(output_file);
                EXIT_APPLICATION(EXIT_FAILURE);
            }
        }
        else {
            printf("warning-> input file is empty: %s (%d)\n", input_file_name, errno);
        }

        /*
        ** Free allocated memory for input file buffer
        */
        free(input_file_buffer);
    }
    else {
        printf("error-> memory allocation failed (%d)\n", errno);
        EXIT_APPLICATION(EXIT_FAILURE);
    }
}
