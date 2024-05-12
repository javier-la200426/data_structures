/*
 * MetroSim.h
 * Javier Laveaga
 * 10/6/2023
 * 
 * CS 15 Project 1: A Metro Simulator
 * 
 * Purpose: Header file of MetroSim. This defines the class. The MetroSim 
 * class contains two lists of passenger queues which represent the 
 * arrival stations and the departure stations of the passengers. The 
 * departure stations list is also the list of passengers in the train.
 * Passengers move from the arrival station list to the train as the 
 * train moves. Separate functions are used for when the train moves, 
 * when adding a passenger, and when writing to the output file. A final 
 * function called run_program is used to combine all the functions and keep
 * prompting for commands. An array of strings is used to save the names of 
 * the stations as well as an integer value to track the position of the train. 
 * 
 */

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"


#include "PassengerQueue.h"
#include <fstream>
#include <sstream>


class MetroSim
{
public:
void run_program (string filename, istream &input, ostream &output);

private:
    //main functions
    string *opening_stations (string filename);
    void initialize_stations ();
    void arrival_departure (int arrivStation_i, int depaStation_i);
    void metro_move (ostream &output);
    //helper functions for main functions
    void output_passenger(ostream &output, Passenger curr_passenger);
    PassengerQueue* get_station (int station_index, 
                                        list<PassengerQueue> *stationList);
    void to_destination (Passenger passenger);
    void print_info ();
    //Variables
    list<PassengerQueue> stations;
    list<PassengerQueue> train_destinations;
    int num_passengers;
    int train_position;
    int numb_stations;
    string *stations_names;
};

#endif
