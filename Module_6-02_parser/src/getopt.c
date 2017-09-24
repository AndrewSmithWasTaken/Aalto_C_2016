#include <stdlib.h>
#include "getopt.h"
#include <string.h>
#include <ctype.h>


/* a) Returns the list of options given on command line arguments
 * indicated in <argc> and <argv>. These parameters are used similarly as
 * in the main function.
 * 
 * Function returns pointer to the start of linked list that contains the
 * options.
 */
struct options *get_options(int argc, char *argv[])
{
    struct options *start = NULL;
    struct options *prev = NULL;
    
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            struct options *new = malloc(sizeof(struct options));
            new->optchar = argv[i][1];
            new->next = NULL;
            if ((i-1 < argc) && (argv[i+1][0] != '-')) {
                new->oarg = malloc(strlen(argv[i+1]) +1);
                strcpy(new->oarg, argv[i+1]);
            }
            else {
                new->oarg = NULL;
            }
            if (!start) {
                start = new;
                prev = new;
            }
            else {
                prev->next = new;
                prev = new;
            }
        }
    }
    return start;
}

/* a) Free the memory allocated for the linked list at <opt>.
 */
void free_options(struct options *opt)
{
    struct options *crawler = opt;
    while (opt) {
        crawler = opt;
        opt = crawler->next;
        free(crawler->oarg);
        free(crawler);
    }
}

/* b) Returns non-zero if option character <optc> is included in the
 * linked list pointed to by <opt>
 */
int is_option(struct options *opt, char optc)
{
    while (opt) {
        if (opt->optchar == optc) {
            return 1;
        }
        opt = opt->next;
    }
    return 0;
}

/* b) Returns the argument given with option <optc>. If argument or
 * the option was not given, the function returns NULL.
 */
char *get_optarg(struct options *opt, char optc)
{
    while (opt) {
        if (opt->optchar == optc) {
            return opt->oarg;
        }
        opt = opt->next;
    }
    return NULL;
}
