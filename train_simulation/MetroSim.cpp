/*
 * MetroSim.cpp
 * Javier Laveaga
 * 10/6/2023
 * 
 * CS 15 Project 1: A Metro Simulator
 * 
 * Purpose: To implement the MetroSim class. This implementation uses
 * functions that read and write to files as well others that are designed 
 * for each of the commands, including moving the train and adding passengers.
 * It also includes functions for printing the information and helper 
 * functions that obtain the station at the desired index. A final function
 * which combines the majority of the functions is used to read in commands 
 * either from the user or from a file.
 *  
 */

#include "MetroSim.h"

/*
 * name: opening_stations
 * purpose: To open the stations file and create a string array with
 * the station names. 
 * arguments: the name of a file
 * returns: Nothing
 * effects: Allocates new memory for an array with the size of 
 * the number of stations
 */
string* MetroSim::opening_stations (string filename) {
    int num_stations = 0;
    ifstream infile(filename); //opening file 
    if (not infile.is_open()) {
        cerr << "Error: could not open file " + filename << endl;
        exit(EXIT_FAILURE);
    }
    //Get number of lines/stations
    string line_in;
    while(getline(infile, line_in)) {
        num_stations++;
    }
    //allocate array of size = num_stations
    string *name_stations = new string [num_stations];
    infile.close();
    infile.open(filename);
    //fill in array with name of stations
    int i = 0;
    while(getline(infile, line_in)) {
        name_stations[i] = line_in;
        i++;
    }
    infile.close();
    numb_stations = num_stations;
    stations_names = name_stations;
    return name_stations;
}

/*
 * name: initialize_stations
 * purpose: To initialize the station queues and definining the initial train
 * position.
 * arguments: None
 * returns: Nothing
 * effects: It allocates new space for each of the station queues by resizing 
 * them.
 */
void MetroSim::initialize_stations () {
    // allocate space for stations
    stations.resize(this->numb_stations); 
    num_passengers = 0;
    train_position = 0;
    train_destinations.resize(this->numb_stations);
}

/*
 * name: arrival_departure
 * purpose: To create and insert a passenger into its corresponding 
 * arrival station
 * arguments: The indeces of the arrival station and the departure station
 * returns: Nothing
 * effects: Creates and adds a new passenger to the queue of its arrival
 * station
 */
void MetroSim::arrival_departure (int arrivStation_i, int depaStation_i) {
    //initializing passenger info
    Passenger passenger(num_passengers + 1, arrivStation_i, depaStation_i);
    //obtaining correct station from the arrival stations list
    PassengerQueue *arrivalStation = 
    this->get_station(arrivStation_i, &stations);
    //it is now the arrival station
    //adding passenger to station
    arrivalStation->enqueue(passenger);
    num_passengers++;
}

/*
 * name: to_destination 
 * purpose: To add a passenger to the queue of its destination station  
 * arguments: a passenger that has a destination (to) station number
 * returns: Nothing
 * effects: Adds a passenger to the corresponding destination station
 */
void MetroSim::to_destination (Passenger passenger) {
    PassengerQueue *destinationStation = this->get_station(passenger.to,
                                                     &train_destinations);
    destinationStation->enqueue(passenger);
}

/*
 * name: metro_move
 * purpose: To board all the passengers at the current station to the train 
 * (destination station). Then, kick off the passengers from the train 
 * whose arrival station is the station the train moved to.
 * arguments: An address to an output file stream 
 * returns: Nothing
 * effects: Sends passengers from the arrival stations to the train by
 * dequeuing from the arrival station. Writes the passengers that are
 * kicked off from the train to the output file stream. Increments the
 * train position by one.
 */
void MetroSim::metro_move (ostream &output) {
    //Boarding on train (from station to train/train_destination)
    //getting station where the train is located
    PassengerQueue *current_station = 
    this->get_station(train_position, &stations);
    //Sending all passengers to their destination station
    //then pop all of them from current station
    while (current_station->size() != 0) {
        to_destination(current_station->front());
        current_station->dequeue();
    }
    //kick off passengers (from train_destination to nowhere):
    //gets desitnation station at current train position
    PassengerQueue *destinationStation = this->
    get_station(((train_position + 1) % numb_stations), &train_destinations); 
    // % to prevent access to outofrange
    //Kick all passengers out of train until there are no more
    while (destinationStation->size() != 0) {
        Passenger curr_passenger = destinationStation->front();
        output_passenger(output, curr_passenger);
        destinationStation->dequeue();      
    }
    //if train position equals # of stations - 1
    // move to train position 0.
    if (train_position == numb_stations - 1) {
        train_position = 0;
    } else {
        train_position++;
    }
}

/*
 * name: get_station 
 * purpose: To obtain the station specified at the given index
 * arguments: Takes in an index and the type of station, whether it is
 * a destination or arrival station
 * returns: Returns the PassengerQueue which represents a station.
 * effects: None
 */
PassengerQueue* MetroSim::get_station (int station_index, 
                                    list<PassengerQueue> *stationList) {
    list<PassengerQueue> ::iterator it;
    int count = 0;
    //Iterate until you get to desired destination
    for (it = stationList->begin(); count < station_index; it++) {
        count++;
    }
    //dereference it to get PassengerQueue object. Then get address
    // to pass a pointer to the PassengerQueue object.
    PassengerQueue *station = &(*it);
    return station;
}

/*
 * name: print_info
 * purpose: To print the information containing the passengers in the train
 * and in the individual stations.
 * arguments: None
 * returns: Nothing
 * effects: Prints to the standard output stream
 */
void MetroSim::print_info () {
    cout << "Passengers on the train: {";
    for (int i = 0; i < numb_stations; i++)  {
        this->get_station(i, &train_destinations)->print(cout);
    }
    
    cout << "}" << endl;
    
    for (int i = 0; i < numb_stations; i++) {
        if (train_position == i) {
            cout << "TRAIN: ";
        } else {
            cout << "       ";
        }
        cout << "[" + to_string(i) << "] " + stations_names[i] + " " + 
        "{"; 
        this->get_station(i, &stations)->print(cout);
        cout << "}";
        cout << endl;
    }
    cout << "Command? ";
}

 /*
 * name: run_program
 * purpose: To keep asking for commands and calling the appropriate 
 * functions including moving the train and adding new passengers.
 * arguments: A file name containing the stations, and input 
 * and output stream.
 * returns: Nothing
 * effects: Moves the train and adds passengers according to the 
 * commands provided. Prints to the screen every iteration
 */
void MetroSim::run_program (string filename, istream &input, ostream &output) {
    string *name_stations = this->opening_stations(filename);
        this->initialize_stations();
        int number;
        string character, line_in;
        stringstream sstream;
        this->print_info();
        bool run = true; //when user types m f
        while (run and getline(input, line_in)) {
                if (line_in == "m m") {
                     this->metro_move(output);
                } else if (line_in == "m f") {
                        cout << "Thanks for playing MetroSim. Have a nice day!"
                         << endl;
                        run = false; //to break out of loop
                } else { // when it is p, read in user input
                     sstream.str(line_in);
                     sstream >> character; //skip over p
                     sstream >> number;
                     int arrivStation_i = number;
                     sstream >> number;
                     int depaStation_i = number;
                     this->arrival_departure (arrivStation_i, depaStation_i);
                }
                sstream.clear(); //very important
                if (run) {
                    this->print_info();
                }
        }
        delete [] name_stations;
}

/*
 * name: output_passenger 
 * purpose: To write the passengers that leave to the output stream 
 * arguments: An address to an output stream and a passenger who is kicked
 * off from the train.
 * returns: Nothing
 * effects: Adds passengers to the output stream provided.
 */
void MetroSim::output_passenger(ostream &output, Passenger curr_passenger) {
    output << "Passenger " + to_string(curr_passenger.id) + 
    " left train at station " + stations_names[curr_passenger.to]; 
    output << endl;
}

