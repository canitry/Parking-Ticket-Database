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

#ifndef MYDELTICKET
TODO(USING THE SOLUTION delticket.c NOT MY CODE)
#else

/*
 * delticket
 *      remove ticket (summons) from the database
 *      look up the summons for a vehicle and pay it (remove the ticket) 
 *
 *      Find the vehicle by the state and plate. if not found return -1
 *
 *      convert the summ string to a long long int using
 *      using strtosumid. This long long int is how the summons number
 *      is stored in the database in struct ticket.
 *      After being converted you can use it find a summons id match
 *      in the linked list of tickets attached to the strcut vehicle.      
 *
 *      After you have the vehicle, find the summons on the ticket chain
 *      that matches the converted summons string (summid in the example)
 *      example:
 *        unsigned long long summid
 *        if (strtosumid(summ, &summid) != 0)
 *           return -1;
 *        now search the ticket chain to find that summons
 *        struct ticket *tptr;
 *        if (tptr->summons == summid)
 *          found it
 *           
 *      If found, delete it from the ticket chain. If the vehicle
 *      no longer has any tickets, then remove the vehicle from the hash chain
 *      Otherwise you must update the tot_fine and cnt_tickets fields in
 *      the struct vehicle so the are accurate after removing the summons
 *      Make sure to delete all space that malloc()'d 
 *
 * Inputs:
 *  plate   plate id string to be found
 *  state   state id string to be found
 *  summ    summon id string to be found
 *
 * returns 0 if ok -1 if not found or error
 */

struct vehicle ** findPreCar(struct vehicle *curCar, char *plate);

int
delticket(char *plate, char *state, char *summ)
{
    unsigned long long summid;

    /*
     * convert the summons string to a number
     */
    if (strtosumid(summ, &summid) != 0)
        return -1;
    /*
     * first find the vehicle
     */
    struct vehicle *car = vehiclelookup(plate, state);
   /*
    * did we find the vehicle?
    */
    if (car == NULL){
        return -1;
    }
    /*
     * find the ticket
     */
    struct ticket **tkt = &(car -> head);
    
    while (1){
       /*
        * if ticket not found we are done
        */
        if (*tkt == NULL){
            return -1;
        }
        if (summid == (*tkt) -> summons){
            break;
        }
        tkt = &((*tkt) -> next);
    }
    /*
     * update the summary fields and remove the ticket
     */
    (car -> tot_fine) -= fineTab[(*tkt) -> code].fine;
    (car -> cnt_ticket)--;
    
    struct ticket *nxtTkt = (*tkt) -> next;
    free(*tkt);
    *tkt = nxtTkt;
    /*
     * was this the last ticket for the vehicle?
     * if so, remove the vehicle from the hash chain
     */
     if ((car -> cnt_ticket) == 0){
        struct vehicle *nxtCar = car -> next;
        struct vehicle **preCar = findPreCar(car, plate);

        free(car -> plate);
        free(car -> state);
        free(car);
        car = NULL;
        *preCar = nxtCar;
     }
    return 0;
}
/*
 * function findPreCar()
 *
 * Operation: finds the pointer that points to the curCar 
 * in the hash chain, it assumes curCar exists in the chain.
 * params: curCar, plate
 * returns: a pointer to the pointer that points to curCar.
 */
struct vehicle ** findPreCar(struct vehicle *curCar, char *plate){
    struct vehicle **preCar;
    uint32_t hashval;
    hashval = hash(plate) % tabsz;
    preCar = (htable + hashval);
    while (*preCar != curCar){
        preCar = &((*preCar) -> next);
    }
    return preCar;
}
#endif
