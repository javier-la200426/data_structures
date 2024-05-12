/*
 * PassengerQueue.h
 * 
 * COMP 15 Project 1: Metrosim - Phase 1
 * 
 * The interface for a PassengerQueue. It holds a list of 
 * passengers, which are represented with the passenger structure, 
 * and allows for manipulation of the queue. This is done, for example, by 
 * accessing the elements at the front, or dequeuing or enqueuing
 * a passenger.
 * 
 * Edited by Javier Laveaga (jlavea01) Friday, September 29.
 */


#ifndef __PASSENGERQUEUE_H__
#define __PASSENGERQUEUE_H__

#include <iostream> 
#include "Passenger.h"
#include <list> 
using namespace std;

class PassengerQueue {
    public:
    //Getter
    Passenger front();
    int size();
    //Setters
    void dequeue();
    void enqueue(const Passenger &passenger);
    void print(ostream &output);

    private:
    list<Passenger> queue;
};

#endif