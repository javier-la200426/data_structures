/*
 * RPNCalc.cpp
 *
 * COMP 15 Project 2: CalcYouLater 
 * 
 * Purpose: The implementation for the RPNCalc class. This acts like Reverse 
 * Polish Notation (RPN) calculator. The class uses a stack to store Datum 
 * objects which contain integers, rstrings, or booleans. It is responsible 
 * for the operations performed on the elements like addition, 
 * mulplication, swapping elements, adding elements, or performing
 * comparisons that result in a boolean. Additionnaly, the class features more
 * complex operations that allow for the execution of commands inside an 
 * rstring, reading commands from a file, and using "if" to execute one rstring
 * or the other based on a boolean condition. It also handles errors that occur
 * if invalid commands are inputted as well as if certain commands are used 
 * incorrectly.
 * However, the Calculator will continue to read input even if an error occurs.
 * The run function is responsible for reading in commands from the standard
 * input. Each command is separated by whitespace.
 * 
 * Edited by Javier Laveaga (jlavea01) Sunday, October 22.
 */

#include "RPNCalc.h"

/*
 * name: RPNCalc
 * purpose: to Initialize a RPNCalc object 
 * arguments: None
 * returns: Nothing
 * effects: Initialize a DatumStack
 */
RPNCalc::RPNCalc() {

}

/*
 * name: ~RPNCalc
 * purpose: to destruct an RPNCalc object
 * arguments: None
 * returns: Nothing
 * effects: Deletes, destroys, recycles any heap allocated memory
 */
RPNCalc::~RPNCalc() {

}

/*
 * name: push_datum
 * purpose: to push a datum object onto the stack
 * arguments: A datum object
 * returns: Nothing 
 * effects: It adds one element to the stack, which is a Datum containing
 * either a rstring, integer, or boolean
 */
void RPNCalc::push_datum(Datum datum) {
    stack.push(datum);
}

/*
 * name: print
 * purpose: to print the Datum element at the top of the stack if the command
 * is print
 * arguments: Takes in a string representing a command
 * returns: Nothing
 * effects: It prints to standard output the top element of the stack
 */
void RPNCalc::print(string command) {
    if (command == "print") {
        cout << stack.top().toString() << endl;
    }
}

/*
 * name: clear
 * purpose: to remove all Datum elements from the stack if the command is
 * clear
 * arguments: Takes in a string representing a command 
 * returns: Nothing
 * effects: It deallocates memory of all the datum elements in the stack and 
 * makes the stack empty
 */
void RPNCalc::clear(string command) {
    if (command == "clear") {
        stack.clear();
    }
}

/*
 * name: drop
 * purpose: To remove the top element from the stack if the command is drop
 * arguments: Takes in a string representing a command
 * returns: Nothing
 * effects: It deallocates memory by removing the top element. Throws an error
 * if the stack is empty.
 */
void RPNCalc::drop(string command) {
    if (command == "drop") {
        stack.pop();
    }
}

/*
 * name: dup
 * purpose: To duplicate the top element of the stack if the command is dup
 * arguments: Takes in a string representing a command
 * returns: Nothing
 * effects: It creates a copy of the top element and pushes it on top of the
 * stack. Throws error if stack is empty.
 */
void RPNCalc::dup(string command) {
    if (command == "dup") {
        Datum top_ele = stack.top();
        stack.push(top_ele);
    }
}

/*
 * name: swap
 * purpose: To swap the top two elements of the stack if the command is swap
 * arguments: Takes in a string representing a command
 * returns: Nothing
 * effects: It pops the top two elements, and adds the first, then the second 
 * element to the top of the stack. Throws error if stack is empty
 */
void RPNCalc::swap(string command) {
    if (command == "swap") {
        Datum first = stack.top();
        stack.pop();
        Datum second = stack.top();
        stack.pop();
        stack.push(first);
        stack.push(second);
    }
}

/*
 * name: not_datum
 * purpose: Takes the top element, a boolean, and makes it the opposite 
 * boolean value if the command is not 
 * arguments: Takes in a string representing a command
 * returns: Nothing
 * effects: It pops the top element. If it is not a boolean, it throws a
 * runtime error. If it is a boolean, it pushes a Datum element with the
 * opposite boolean value. Throws error if stack is empty
 */
void RPNCalc::not_datum(string command) {
    if (command == "not") {
        Datum datum = stack.top();
        stack.pop(); //pop off even if it is not bool
        //if not boolean, then getBool should throw error
        bool new_boolean = not datum.getBool(); //change from T to F or F to T
        stack.push(Datum(new_boolean)); //push bool with opposit value
    }
}

/*
 * name: operation
 * purpose: To perform the necessary arithmetic operation based on 
 * the command and push the result on top of the stack.
 * arguments: Takes in a string representing a command. Assumes that
 * the command is one of the arithmetic commands.
 * returns: Nothing
 * effects: Pops the top two elements and pushes the result on top of the 
 * stack. Throws a runtime error when dividing by zero, when the elements
 * are not integers, or when the stack is empty.
 */
void RPNCalc::operation(string command) {
    Datum first = stack.top();
    stack.pop();
    Datum second = stack.top(); //deeper element (1st operand)
    stack.pop();
    int result = 0;
    if (command == "+") {
        result = second.getInt() + first.getInt();
    } else if (command == "-") {
        result = second.getInt() - first.getInt();
    } else if (command == "*") {
        result = second.getInt() * first.getInt();
    } else if (command == "/") {
        if (first.getInt() == 0) {
            throw runtime_error("division by 0.");
        }
        result = second.getInt() / first.getInt();
    } else if (command == "mod"){
        if (first.getInt() == 0) {
            throw runtime_error("division by 0.");
        }
        result = second.getInt() % first.getInt();
    }
    Datum new_datum(result);
    stack.push(new_datum);
}

/*
 * name: bool_operation
 * purpose: To perform an equality/comparison operation based on 
 * the command and push the boolean result on top of the stack. 
 * arguments: Takes in a string representing a command. Assumes that
 * the command is one of the equality/comparison commands
 * returns: Nothing
 * effects: Pops the top two elements and pushes the result on top of the 
 * stack. Throws a runtime error when when the elements are not integers 
 * (except for ==) or when the stack is empty.
 */
void RPNCalc::bool_operation(string command) {
    Datum first = stack.top();
    stack.pop();
    Datum second = stack.top(); //deeper element (1st operand)
    stack.pop();
    bool result = true;
    if (command == "<") {
        result = second.getInt() < first.getInt();
    } else if (command == ">") {
        result = second.getInt() > first.getInt();
    } else if (command == "<=") {
        result = second.getInt() <= first.getInt();
    } else if (command == ">=") {
        result = second.getInt() >= first.getInt();
    } else if (command == "==") { //== //can be any type
        result = second == first;
    }
    Datum new_datum(result); 
    stack.push(new_datum);
}

/*
 * name: exec
 * purpose: To take the top element of the stack and process its contents as
 * as series of commands.
 * arguments: Takes in a string representing a command. Will execute the rest
 * of exec if the command is exec
 * returns: Nothing
 * effects: Pops the top element from the stack and throws a runtime error if 
 * the element is not an rstring
 */
void RPNCalc::exec(string command) {
    if (command == "exec") {
        Datum first = stack.top();
        stack.pop();
        string commands = first.getRString(); //if not an rstring, error thrown
        istringstream ss;
        ss.str(commands); //converts string to input stream
        //aka feeds in string to input stream
        //passs in stringstream to function with while loop
        string skip;
        ss >> skip; //skip over "{"" to prevent it from it being a command
        run_loop(ss);
    }
}

/*
 * name: file
 * purpose: Pop the top element of the stack, reads the contents of the 
 * named file in the rstring, and proccesses its commands as if they had 
 * been typed into the command loop.
 * arguments: Takes in a string representing a command. Executes rest of file 
 * function if the command is file
 * returns: Nothing
 * effects: If the element is not an rstring, it throws a runtime error. If 
 * the file cannot be opened or read, it prints an error message to std::cerr.
 */
void RPNCalc::file(string command) {
    if (command == "file") {
        Datum first = stack.top();
        stack.pop();
        string rstring = first.getRString(); //throws error if not rstring
        string skip;
        string filename;
        //get the filename from the rstring
        istringstream ss;
        ss.str(rstring);
        ss >> skip; //skip over {
        ss >> filename;
        ss.clear(); //done with it
        ifstream input;
        //check to see if it can open the file (also links stream to file)
        open_check(input, filename);
        run_loop(input);
        input.clear();
        input.close();
    }
}

/*
 * name: if_c
 * purpose: To execute the if command by popping the top three elements from 
 * the stack. It will execute the proper rstring based on the boolean condition.
 * arguments: Takes in a string representing a command
 * returns: Nothing
 * effects: If any of the elements are of the wrong type, an error message 
 * will be throwned.
 */
void RPNCalc::if_c(string command) {
    if (command == "if") {
        //save and pop first 3 Datum elements
        Datum first = stack.top();
        stack.pop();
        Datum second = stack.top();
        stack.pop();
        Datum third = stack.top();
        stack.pop();
        third.getBool(); //throw an error if not bool
        first.getRString(); //throw an error if not r string
        second.getRString(); //throw an error if not r string
        //if bool is true, execute second
        if (third.getBool()) { 
            stack.push(second);
            exec("exec");
        } else {
            stack.push(first);
            exec("exec");
        }
    } 
}

/*
 * name: run_loop
 * purpose: To keep reading input from an input stream and execute the 
 * proper operations based on the commands until the end of the file or when
 * the command 'quit' is inputted.
 * arguments: An input stream representing the user (cin), a file, or 
 * a istringstream
 * returns: Nothing
 * effects: Catches runtime errors and prints the appropriate error messages
 * to std::cerr. 
 */
void RPNCalc::run_loop(istream &input) {
    string curr_c; //current command
    bool run = true; //when quitting
    while (run and input >> curr_c and (not input.eof())) {
        bool runtime_error_thrown = false;
        std::string error_message = "";
        try {
            //check that command is valid or an integer
            check_valid_command(curr_c);
            //check to see if command is exec
            exec(curr_c);
            file(curr_c); //check to see if command is file
            //check to see if command is quit or an arithmetic operation
            quit_or_operation(curr_c, &run);
            //check to see if command is one of the other ones
            simple_commands(curr_c); 
            easy_commands(curr_c, input);
            if_c(curr_c);
        }
        catch (const std::runtime_error &e) {
            runtime_error_thrown = true;
            error_message = e.what();
        }
        error_messages(runtime_error_thrown, curr_c, error_message);
    } 
}

/*
 * name: error_messages
 * purpose: To print the appropriate error message (if there is 
 * a runtime error) based on the error message and the command
 * arguments: A boolean representing whether or not an error was 
 * detected, a string with the current command, and a message 
 * representing the error message catched by the run_loop function.
 * returns: Nothing
 * effects: Prints the appropriate error message to std:: cerr.
 */
void RPNCalc::error_messages (bool runtime_error, string curr_c, 
                                string message) {
    if (runtime_error and (message == "datum_not_bool" 
        or message == "datum_not_rstring") ) {
        //error might have comed from 'if' command
        if (curr_c == "if") {
            if (message == "datum_not_bool") {
                cerr << "Error: expected boolean in if test\n";
            } else if (message == "datum_not_rstring") {
                cerr << "Error: expected rstring in if branch\n";
            } 
        } else if (curr_c == "file") {
            cerr << "Error: file operand not rstring\n";
        } else { //if it is bool or rstring error, but not "if" or "file"
            //print normally
            cerr << "Error: " << message << "\n";
        }
    } else if (runtime_error) { //if it is an error that is not rstring or bool
        //print normally
            cerr << "Error: " << message << "\n";
    }
}

/*
 * name: run
 * purpose: To run the RPN Calculator by calling the run_loop function
 * and passing standard input as a parameter.
 * arguments: None
 * returns: Nothing
 * effects: It prompts the user for commands to enter and performs the 
 * appropriate operations, printing, and error messaging based on the 
 * commands. 
 */
void RPNCalc::run() {
    run_loop(cin);
    cerr << "Thank you for using CalcYouLater.\n";
}

/*
 * name: quit_or_operation
 * purpose: To determine which of the arithmetic or equality commands 
 * is being asked for and call the appropriate functions responsible for 
 * executing that command. If 'quit' is the commmand, it signals to stop 
 * reading in commands.
 * arguments: Takes in a string representing a command and a pointer to a 
 * boolean which represents whether the loop should terminate
 * returns: Nothing
 * effects: It sets the run boolean to false if the quit command is 
 * entered.
 */
void RPNCalc::quit_or_operation (string command, bool *run) {
    if (command == "quit") {
        *run = false;
    } else if (command == "+" or command == "-" or command == "*" or 
                                    command == "/" or command == "mod") {
            //check if command is an operation. If yes, do it
            operation(command);
    } else if (command == "<" or command == ">" or command == "<=" or
                    command == ">=" or command == "==") {
            //check if it is a bool operation. If yes do it.
            bool_operation(command);
    }
}

/*
 * name: simple_commands
 * purpose: To call the appropriate function respnonsible for 
 * executing one of the 'simple' commands. This is done based
 * on the command.
 * arguments: Takes in a string representing a command
 * returns: Nothing
 * effects: Performs the necessary operations, error messaging, and 
 * changes to the stack based on the command by calling the simple 
 * functions.
 */
void RPNCalc::simple_commands(string command) {
        not_datum(command); 
        print(command); 
        clear(command);
        drop(command); 
        dup(command); 
        swap(command);
}

/*
 * name: easy_commands
 * purpose: This is responsible for pushing the appropriate datum element
 * into the stack based on the command. These commands are thought of as
 * easy as they all only require adding to the stack.
 * arguments: Takes in a string representing a command and an 
 * input stream to pass to the parseString function. (this way
 * the parseString function can keep reading from the input until it sees a 
 * closing bracket).
 * returns: Nothing
 * effects: Pushes a datum object onto the top of the stack.
 */
void RPNCalc::easy_commands (string command, istream &input) {
    int resultp = 0;  //not used here
    bool is_int = got_int(command, &resultp); 
    if (is_int) {
        Datum num(resultp);
        push_datum(num);
    } else if (command == "#t") {
        Datum truth(true);
        push_datum(truth);
    } else if (command == "#f") {
        Datum fake(false);
        push_datum(fake);
    } else if(command == "{") { //check if rstring
            string rstring = parseRString(input); //input not cin only
            //because when reading from a file, you dont have cin
            Datum string_d(rstring);
            push_datum(string_d);
    }
}

 /*
 * name: check_valid_command
 * purpose: To check if a given command is one of the valid commands or 
 * an integer. 
 * arguments: Takes in a string representing a command
 * returns: Nothing
 * effects: If the command is not a valid command or an integer, then
 * it prints an error message to std::cerr. A special message is 
 * displayed when the command is an invalid boolean
 */
void RPNCalc::check_valid_command (string command) {
    int resultp = 0;  //not used here
    bool is_int = got_int(command, &resultp); // check to see if it is integer
    //check to see if it is one of the commands
    bool is_command = false;
    string arr[23] = {"#t", "#f", "not", "print", "clear", "drop", "dup", 
    "swap", "quit", "+", "-", "*", "/", "mod", "<", ">", "<=", ">=", "==", 
    "exec", "file", "if", "{"};
    string current;
    for (int i = 0; i < 23; i++) {
        current = arr[i];
        if (current == command) {
            is_command = true;
        }
    }
    istringstream ss;  //Check if invalid boolean is inputted.
    ss.str(command);
    char character;
    ss >> character;
    if (character == '#') {
        ss >> character;
        if (character != 'f' and character != 't') {
            cerr << "Error: invalid boolean " + command + "\n";
            is_command = true; //to prevent printing other errors
        }
    } 
    if (not (is_command or is_int)) {
        cerr << command + ": unimplemented\n";   
    }
}

/*
 * name: got_int
 * purpose: To determine if a string can be interpreted as an integer 
 * number and obtain that integer if possible.
 * arguments: A string with the possible integer, and a pointer to an 
 * integer in which the integer will be stored.
 * returns: A boolean value indicating whether string s can be interpreted 
 * as an integer. If not, it will return false.
 * effects: It stores the integer value in the memory pointed to by
 * resultp if the string is interpreted as an integer.
 */
bool RPNCalc::got_int(string s, int *resultp) {
        /* Holds the first non-whitespace character after the integer */
        char extra;

        return sscanf(s.c_str(), " %d %c", resultp, &extra) == 1;
}

/*
 * name: open_check
 * purpose: To check if a file can be opened. This function is used 
 * for when the file command is executed and a file needs to be 
 * opened.
 * arguments: An input filestream and the name of the file to 
 * be opened.
 * returns: Nothing
 * effects: Prints an error message to cerr if the file cannot 
 * be opened.
 */
void RPNCalc::open_check(ifstream &input, string file_name) {
    input.open(file_name);
        if (not input.is_open()) {
                cerr << "Unable to read " << file_name + "\n";
        }
}

