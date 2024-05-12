/*
 * unit_tests.h
 *
 * COMP 15 Project 1: Metrosim
 * 
 * Tests the Passenger structure and PassengerQueue interface
 * Creates 4 passengers and moves them around, then checks with
 * print funciton to compare with the expected information.
 * 
 * Edited by Javier Laveaga (jlavea01) Friday, September 29.
 */

#include "PassengerQueue.h"
#include "MetroSim.h"
#include <cassert>
#include <string>
#include <sstream> //from CS11
using namespace std;

//Initializing passengers for all tests
Passenger p1(1, 1, 2);
Passenger p2(2, 1, 3);
Passenger p3(3, 2, 3);
Passenger p4(4, 2, 3);

void test_passenger () {
    Passenger p5(5, 3, 6);
    assert(p5.id == 5);
    assert(p5.from == 3);
    assert(p5.to == 6);
}

void test_print () {
    PassengerQueue Test;
    stringstream sstream;
    Test.enqueue(p1);
    Test.print(sstream); 
    assert(sstream.str() == "[1, 1->2]");
    sstream.clear();
}

void test_enqueue () {
    PassengerQueue Test;
    stringstream sstream;
    Test.enqueue(p1); 
    Test.enqueue(p2);
    Test.enqueue(p3);
    Test.enqueue(p4);
    Test.print(sstream);
    
    assert(sstream.str() == "[1, 1->2][2, 1->3][3, 2->3][4, 2->3]");
    sstream.clear();
}

void test_dequeue () {
    PassengerQueue Test;
    stringstream sstream;
    stringstream sstream2;
    Test.enqueue(p1); 
    Test.enqueue(p2);
    Test.enqueue(p3);
    Test.enqueue(p4);
    Test.print(sstream);
    assert(sstream.str() == "[1, 1->2][2, 1->3][3, 2->3][4, 2->3]");
    sstream.clear();
    //dequeuing
    Test.dequeue();
    Test.print(sstream2);
    assert(sstream2.str() == "[2, 1->3][3, 2->3][4, 2->3]");
}

void test_front () {
    stringstream sstream;
    PassengerQueue Test;
    Test.enqueue(p1); 
    Test.enqueue(p2);
    Test.enqueue(p3);
    Test.enqueue(p4);
    //get front passenger
    Passenger first = Test.front();
    first.print(sstream);
    assert(sstream.str() == "[1, 1->2]");
    sstream.clear();
}

void test_size () {
    PassengerQueue Test;
    Test.enqueue(p1); 
    Test.enqueue(p2);
    Test.enqueue(p3);
    Test.enqueue(p4);
    int num_passengers = Test.size();
    assert(num_passengers == 4);
}

void test_size_empty () {
    PassengerQueue Test;
    int num_passengers = Test.size();
    assert(num_passengers == 0);
}



//METROSIM CLASS TESTS
void test_opening_stations () {
    MetroSim test;
    string *name_stations = test.opening_stations("stations.txt");
    assert(name_stations[0] == "South Station");
    assert(name_stations[1] == "Madrid");
    assert(name_stations[2] == "Barcelona");
    assert(name_stations[3] == "Paris");
    assert(name_stations[4] == "Berlin");
    assert(name_stations[5] == "Praga");
    assert(name_stations[6] == "Lisbon");
    delete [] name_stations;
}

void test_initialize_stations () {
    MetroSim test;
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    assert(test.stations.size() == test.numb_stations); //private member
    assert(test.train_position == 0); //private member
    assert(test.train_destinations.size() == test.numb_stations);

    delete [] name_stations;
    //test.stations.clear (); //no need since destructor does this for me
}
//Tests adding passengers at first station
void test_arrival_departure () {
    stringstream sstream;
    MetroSim test;
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    //here test begins
    test.arrival_departure(0, 3);
    test.arrival_departure(0, 4);
    test.stations.front().print(sstream);
    assert(sstream.str() == "[1, 0->3][2, 0->4]");
    assert(test.num_passengers == 2); //private member
    delete [] name_stations;
    sstream.clear();
}
//Tests adding passengers in other stations
void test_arrival_departure_2 () {
    stringstream sstream;
    MetroSim test;
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    //here test begins
    test.arrival_departure(3, 6);
    test.arrival_departure(2, 4);
    //'print' contents of station 3
    test.get_station(3, &test.stations)->print(sstream);
    test.get_station(2, &test.stations)->print(sstream);

    assert(sstream.str() == "[1, 3->6][2, 2->4]");
    assert(test.num_passengers == 2); //private member
    delete [] name_stations;
    sstream.clear();
}

//testing with passengers at the first station
void test_mm_boarding () {
    //initializing a metrosim
    //involving passengers only at 0th station
    MetroSim test;
    ofstream outs;
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    //adding passengers to staion 0
    test.arrival_departure(0, 0);
    test.arrival_departure(0, 0);
    //Testing metro move
    assert(test.stations.front().size() == 2);
    test.metro_move(outs);
    assert(test.stations.front().size() == 0);//passengers dequed from station
    assert(test.train_position == 1); //train changed position
    assert(test.train_destinations.front().size() == 2);
    
    delete [] name_stations;
}

//testing involving passengers and 3rth and 2nd station
void test_mm_boarding_2 () {
    //initializing a metrosim
    MetroSim test;
    ofstream outs; // not needed but need to pass stream to move function
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    //adding passengers to staion 0
    test.arrival_departure(3, 6);
    test.arrival_departure(2, 4);
    //move
    test.metro_move(outs);
    test.metro_move(outs);
    assert(test.get_station(2, &test.stations)->size() == 1);
    assert(test.get_station(4, &test.train_destinations)->size() == 0);
    //moving train past station 2
    test.metro_move(outs);
    assert(test.get_station(2, &test.stations)->size() == 0);
    assert(test.get_station(4, &test.train_destinations)->size() == 1);
    
    assert(test.get_station(3, &test.stations)->size() == 1);
    assert(test.get_station(6, &test.train_destinations)->size() == 0);
    //moving train past station 3
    test.metro_move(outs);
    assert(test.get_station(3, &test.stations)->size() == 0);
    assert(test.get_station(6, &test.train_destinations)->size() == 1);
    outs.close();

    delete [] name_stations;
}

//tests going back to 1st station
void test_mm_boarding3 () {
    MetroSim test;
    ofstream outs;
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    test.arrival_departure(3, 6);
    test.arrival_departure(2, 4);
    //moving from 0 6, then back to 0
    //calls metro move 7 times (0-6 stations)
    for(int i = 0; i < test.numb_stations; i++) {
        test.metro_move(outs);
    }
    
    assert(test.train_position == 0);
    assert(test.get_station(6, &test.train_destinations)->size() == 0);
    assert(test.get_station(4, &test.train_destinations)->size() == 0);

    outs.close();

    delete [] name_stations;
}


//Tests a passenger that arrives and leaves at the same station
void test_mm_removing () {
    MetroSim test;
    ofstream outs;
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    //adding passengers to staion 
    test.arrival_departure(1, 1);
    test.arrival_departure(1, 3);
    //moving
    test.metro_move(outs);
    test.metro_move(outs);
    assert(test.get_station(1, &test.train_destinations)->size() == 1);
    assert(test.get_station(3, &test.train_destinations)->size() == 1);
    test.metro_move(outs);
    assert(test.get_station(3, &test.train_destinations)->size() == 0);
    
    //train ends up at position 1 again
    for(int i = 0; i < test.numb_stations + 1; i++) {
        test.metro_move(outs);
    }
    assert(test.get_station(1, &test.train_destinations)->size() == 0);
    outs.close();
    
    delete [] name_stations;
}


void test_output_passenger () {
    stringstream sstream;
    MetroSim test;
    ofstream outs;
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    //adding passengers to staion 
    test.arrival_departure(1, 1);
    test.arrival_departure(1, 3);
    //moving
    for(int i = 0; i < test.numb_stations + 5; i++) {
        test.metro_move(sstream);
    }
    
    string first = "Passenger 2 left train at station Paris";
    string second = "Passenger 1 left train at station Madrid";

    assert(sstream.str() == first + "\n" + second + "\n");
    delete [] name_stations;

    sstream.clear();
}


void test_get_station () {
    stringstream sstream;
    MetroSim test;
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    //here test begins
    test.arrival_departure(3, 6);
    test.arrival_departure(3, 4);
    PassengerQueue *desired_st = test.get_station(3, &test.stations);
    desired_st->print(sstream); 
    assert(sstream.str() == "[1, 3->6][2, 3->4]");

    delete [] name_stations;

    sstream.clear();
}

void test_to_destination () {
    stringstream sstream;
    MetroSim test;
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    //here test begins
    Passenger p5(5, 1, 2);
    test.to_destination(p5);
    PassengerQueue *desired_st = 
    test.get_station(2, &test.train_destinations);
    desired_st->print(sstream); 
    assert(sstream.str() == "[5, 1->2]");

    delete [] name_stations;
    sstream.clear();

}
//Tests the print function
void test_printing () {
    MetroSim test;
    ofstream outs;
    string *name_stations = test.opening_stations("stations.txt");
    test.initialize_stations();
    //adding passengers to staion 0
    test.arrival_departure(3, 6);
    test.arrival_departure(2, 4);
    for(int i = 0; i < test.numb_stations; i++) {
        test.metro_move(outs);
    }
    //test.print_info(); //instead of assert, diff was used to check this
    outs.close();
    delete [] name_stations;
}


