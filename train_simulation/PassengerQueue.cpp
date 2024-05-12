/*
 * PassengerQueue.cpp
 *
 * COMP 15 Project 1: Metrosim - Phase 1
 * 
 * The implementation for the PassengerQueue class. The class uses 
 * a list of passengers from std::list and calls the appropriate
 * functions under that list class when the methods in PassengerQueue
 * are called.
 * 
 * Edited by Javier Laveaga (jlavea01) Friday, September 29.
 */

#include "PassengerQueue.h"

/*
 * name: front     
 * purpose: To get the Passenger at the front of the queue
 * arguments: none
 * returns: Returns the passenger structure at the front
 * effects: None
 */
Passenger PassengerQueue::front() {
    Passenger first = queue.front();
    return first;
}

/*
 * name: dequeue    
 * purpose: To remove the passenger at the front of the queue
 * arguments: None
 * returns: Nonthing
 * effects: Removes the first element, reducing the size by 1
 */
void PassengerQueue::dequeue() {
    queue.pop_front();
}

/*
 * name: enqueue    
 * purpose: To insert a passenger at the end of the queue
 * arguments: the address of a passenger structure
 * returns: Nothing
 * effects: Adds a passenger to the back of the queue
 */
void PassengerQueue::enqueue(const Passenger &passenger) {
    queue.push_back(passenger);
}

/*
 * name: size    
 * purpose: To obtain the size of the Passenger queue
 * arguments: None
 * returns: The size of the list of passengers
 * effects: None
 */
int PassengerQueue::size() {
    return queue.size();
}

/*
 * name: print    
 * purpose: To print the information of each passenger in the queue
 * arguments: A reference to an output stream
 * returns: Nothing
 * effects: It adds each of the passenger's information to the output stream
 */
void PassengerQueue::print(std::ostream &output) {
    //initializing an iterator 'it' to loop through the contents
    //of the queue. queue.end returns an element past the end of queue
    list<Passenger>::iterator it;
    for (it = queue.begin(); it != queue.end(); it++) {
        //Dereference it to access current Passenger
        it->print(output);
    }
}