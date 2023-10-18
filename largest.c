#include <limits.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include "parking.h"

#ifndef MYLARGEST
TODO(USING THE SOLUTION largest.c NOT MY CODE)
#else

/*
 * largest
 *     find the vehicle with the largest number of
 *     tickets and largest fine in database
 *     and print it
 */
void
largest(void)
{
    struct vehicle *count = NULL; // vehicle with largest number of tickets
    struct vehicle *fine = NULL;  // vehicle with largest total fine

/* your code here */
    unsigned int gFine=0;//greatest fine amount so far
    unsigned int gTkt=0;//greatest ticket amount so far
    struct vehicle **endptr = htable+tabsz;//end of hash table
    struct vehicle **chain = htable;//traverses hash table

    while (chain < endptr){
        if (*chain != NULL){
            struct vehicle *car=*chain;//traverse vehicles in chain
            while (car != NULL){
                if ((car -> tot_fine) >= gFine){
                    fine = car;
                    gFine = car -> tot_fine;
                }
                if ((car -> cnt_ticket) >= gTkt){
                    count = car;
                    gTkt = car -> cnt_ticket;
                }
                car=car -> next;
            }
        }
        chain++;    
    }

    if ((count == NULL) || (fine == NULL)) {
        printf("Empty database\n");
        return;
    }
    printf("Most tickets Plate: %s, State: %s tickets: %u, total fine: $%u\n",
            count->plate, count->state, count->cnt_ticket, count->tot_fine);
    printf("Largest fine Plate: %s, State: %s tickets: %u, total fine: $%u\n",
            fine->plate, fine->state, fine->cnt_ticket, fine->tot_fine);
    return;
}
#endif
