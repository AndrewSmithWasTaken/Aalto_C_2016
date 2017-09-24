#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "election.h"

int num_candidates;

struct votes *read_votes(const char *filename) {
    num_candidates = 0;
    FILE *fp = fopen(filename, "r");
 
    struct votes *candidates=malloc(sizeof(struct votes));
 
    char dummy_string[40];
 
    while(fgets(dummy_string, 40, fp)){
        int not_in_list = 1;
        struct votes new;
        new.votes = 0;
        strcpy(new.name, dummy_string);
       
        int c = 0;
        while(new.name[c]){
            if(new.name[c]=='\n') {
                new.name[c]='\0';
            }
            c++;
        }
       
        for(int j = 0; j<num_candidates ; j++){
            if(!strcmp(new.name, candidates[j].name)){
                not_in_list = 0;
                candidates[j].votes++;
            }
        }
        if(not_in_list){
            num_candidates++;
            candidates = realloc(candidates, sizeof(struct votes)*(num_candidates));
            candidates[num_candidates-1] = new;
            candidates[num_candidates-1].votes++;
        }
    }
    candidates = realloc(candidates, sizeof(struct votes)*(num_candidates+1));
    struct votes last;
    strcpy(last.name, "\0");
    last.votes = 0;
    candidates[num_candidates] = last;
 
 
    fclose(fp);
    return candidates;
}

int compare_votes(const void *a, const void *b) {
    struct votes *aa = (struct votes*)a;
    struct votes *bb = (struct votes*)b;

    unsigned int val_1 = aa->votes;
    unsigned int val_2 = bb->votes;
    
    return val_2 - val_1;
}

int compare_names(const void *a, const void *b) {
    struct votes *aa = (struct votes*)a;
    struct votes *bb = (struct votes*)b;
    
    char *val_1 = aa->name;
    char *val_2 = bb->name;
    
    return strcmp(val_1, val_2);
}

void results(struct votes *vlist) {
    
    qsort(vlist, num_candidates, sizeof(struct votes), compare_names);
    qsort(vlist, num_candidates, sizeof(struct votes), compare_votes);
    
        
    for (int i = 0; i < num_candidates; i++) {
        printf("%s: %d\n", vlist[i].name, vlist[i].votes);
    }
}