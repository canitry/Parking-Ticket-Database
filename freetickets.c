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

#ifndef MYFREETICKETS
TODO(USING THE SOLUTION freetickets.c NOT MY CODE)
#else

/*
 * freetickets
 *      tears down the database freeing all allocated memory
 *      count the number of tickets freed in the database and
 *      print it out before returning
 *
 *      unsigned long cnt = 0UL
 *      printf("Total tickets freed: %lu\n", cnt);
 */
void
freetickets(void)
{
    int empty = 1; // set to zero when there is at least one vehicle in the database

    unsigned long cnt = 0UL;// count of number of tickets freed
    /*
     * walk down each chain
     */
    struct vehicle **endptr = htable+tabsz;//the end of the hash table
    struct vehicle **chain = htable;//traverses hash table to access chain
    while (chain < endptr){
       /*
        * remove all the tickets for all vehicles
        * on this chain
        */
        if (*chain != NULL){
            empty = 0;
            struct vehicle *car=*chain;//traverses the vehicles in the chain
            struct vehicle *nxtCr;//stores next so isn't lost when free car
            while (car != NULL){
                struct ticket *tkt = car -> head;//traverses tickets in vehicle
                struct ticket *nxtTkt;//stores next so not lost on free ticket
                while (tkt != NULL){
                    nxtTkt=tkt -> next;
                    free(tkt);
                    cnt++;
                    tkt=nxtTkt;
                }
               /*
                * free the vehicle
                */
                nxtCr=car -> next;
                free(car -> state);
                free(car -> plate);
                free(car);
                car = nxtCr;
            }

           /*
            * chain is removed, update the htable entry
            */
            *chain = NULL;
        }
        chain++;    
    }

    if (empty)
        printf("Empty Database\n");
    printf("Total tickets freed: %lu\n", cnt);
    return;
}
#endif
