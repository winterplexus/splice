Splice Application
=================================
Splice is an application that will concatenate files into a single file using files that were created by the slice application <https://github.com/winterplexus/slice/>.

Application defaults include:

* input file directory must contain files with a file name plus a period and part number as a suffix
* part number is 4 digits with leading zeros 
* part number sequence must begin at 1

The application is written in ANSI C for both Windows and Linux operating systems.

### splice
```
usage: splice (options)

options: -i <input file path>
         -b <input file base name>
         -o <output file name>
         -s show file names
         -? print this usage
```		 