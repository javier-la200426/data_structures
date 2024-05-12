/*
 * Passenger.h
 *
 * COMP 15 Project 1: Metrosim - Phase 1
 * 
 * The Passenger structure that is used to print the
 * information about the passenger. The Passenger holds, an ID, and the
 * indeces of the its arriaval and departure stations.
 *  
 * Edited by Javier Laveaga (jlavea01) Friday, September 29.
 */

#ifndef __PASSENGER_H__
#define __PASSENGER_H__

#include <iostream>

struct Passenger
{

        int id, from, to;
        
        Passenger()
        {
                id   = -1;
                from = -1;
                to   = -1;
        }

        Passenger(int newId, int arrivalStation, int departureStation)
        {
                id   = newId;
                from = arrivalStation;
                to   = departureStation;
        }

        
        void print(std::ostream &output);

};

#endif
