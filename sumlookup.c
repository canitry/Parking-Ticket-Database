#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"
#include "hashdb.h"

#ifndef MYSUMLOOKUP
TODO(USING THE SOLUTION sumlookup.c NOT MY CODE)
#else

/*
 * summlookup
 *     find the vehicle with a specified summons number
 * Input:
 *      summ: string of summons number
 * returns:   a pointer to the vehicle
 */
struct vehicle *
sumlookup(char *summ)
{
    unsigned long long summid;
    if (strtosumid(summ, &summid) != 0) {
        fprintf(stderr, "%s:sumlookup bad summons number:%s\n", argv0, summ);
        return NULL;
    }
/* your code here */
    struct vehicle **endptr = htable+tabsz;//end of hash table
    struct vehicle **chain = htable;//traverses hash table
    while (chain < endptr){
        if (*chain != NULL){
            struct vehicle *car=*chain;//traverses vehicles in chain
            while (car != NULL){
                struct ticket *tkt = car -> head;
                while (tkt != NULL){
                    if (tkt -> summons == summid){
                        return car;
                    }
                    tkt=tkt -> next;
                }
                car=car -> next;
            }
        }
        chain++;    
    }
    return NULL;
}
#endif
