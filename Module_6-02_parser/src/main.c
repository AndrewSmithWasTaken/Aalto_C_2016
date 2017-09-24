#include <stdio.h>
#include "getopt.h"


int main(int argc, char *argv[])
{
    // If you are not using command line, add some other code to fill the
    // content for argc and argv.
    argv[0] = "Prog Name";
    argv[1] = "-a";
    argv[2] = "Option";
    argv[3] = "-b";
    argv[4] = "Boption";
    argv[5] = "-c";
    argv[6] = "Coption";
    argv[7] = "-d";
    argv[8] = "Doption";
    argc = 9;
    
    struct options *opt = get_options(argc, argv);
    
    const char ochars[] = { 'a', 'b', 'c', 'd' };
    for (unsigned int i = 0; i < sizeof(ochars) / sizeof(char); i++) {
        if (is_option(opt, ochars[i])) {
            printf("Option '%c' was given.\n", ochars[i]);
        }
        char *oarg = get_optarg(opt, ochars[i]);
        if (oarg) {
            printf("Option '%c' had argument '%s'.\n", ochars[i], oarg);
        }
    }
    
    free_options(opt);
}
