/**
 * @file mainpage.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage Csci 3081_2019 Transit Simulator
 *
 * \section Introduction
 * This program is a transit system simulation with a visualization capability.
 * It models transit around the University of Minnesota campus via bus. 
 *
 * \section  User Guide
 * \subsection  Running the Simulator
 * \subsection Method 1 Run on VOLE or CSE labs machines
 * 1. Navigate to base project directory
 * 2. Make and start server:
 * 
 * ```
 * $ cd src
 * $ make 
 * $ cd ..
 * $./build/bin/vis_sim <port_number>
 * ```
 * 
 * Notes:
 * i. <port_number> should be a number above 8000 that includes the last 3 digits of your student id.
 * So, if your student id number is: 1459345, use 8345, or 9345**
 * 
 * 
 * 3. Run your broswer and enter following address in the address bar of your browser (Firefox/Chrome):
 * ```
 * http://127.0.0.1:<port_number>/web_graphics/project.html
 * ```
 * 
 * 4. Once you get to the simulation page, adjust the time steps and
 * time steps between busses to your desire number and then click
 * the `Start` button. 
 * 
 * \subsection Method 2 Using SSH
 * 1. SSH to cse labs machines using a Windows machine with Git Bash.
 * ```
 * ssh -L <port number>:127.0.0.1:<port_number> <x500>@<cse_labs_computer>.cselabs.umn.edu
 * ```
 * 
 * Notes:
 * i. <port_number> should be a number above 8000 that includes the last 3 digits of your student id.
 * So, if your student id number is: 1459345, use 8345, or 9345**
 * 
 * ii. <x500> is your Internet ID
 * 
 *
 * After successfully connected to the CSE labs machine:
 * 1. Navigate to base project directory 
 * 2. make and start server:
 * ```
 * $ cd src
 * $ make 
 * $ cd ..
 * $./build/bin/vis_sim <port_number>
 * ```
 * 
 * Notes:
 * i. <port_number> should be a number above 8000 that includes the last 3 digits of your student id.
 * So, if your student id number is: 1459345, use 8345, or 9345**
 * 
 * 
 * 3. Run your broswer and enter following address in the address bar of your browser (Firefox/Chrome):
 * ```
 * http://127.0.0.1:<port_number>/web_graphics/project.html
 * ```
 *
 * 4. Once you get to the simulation page, adjust the time steps and
 * time steps between busses to your desire number and then click
 * the `Start` button.
 * 
 * If you run `./build/bin/configuration_sim  <config_filename>`, you need to specify 
 * the configuration file that is store in config directory. Otherwise, the default `config.txt`
 * will be used. 
 * 
 * Running configuration_sim give you options to redirect you output in a text file, specify 
 * the length of simulation, or both. In order to do that run the following command:
 * ```
 * ./build/bin/configuration_sim <config_filename> [length of simulation] [outputfile]
 * ```
 * 
 * 
 * \section Classes
 * Class Bus, Route, Stop, and Passenger has a relationship. Every time Bus class calls its Update(), it will
 * call Move function to trigger Update function of each Passenger. It will update all the status of passengers, route,
 * and time
 *   
 * \subsection PassengerFactory
 * PassengerFactory class is the main class that generates passengers. It generates a
 * passenger with a randomized name and random destination with bounds when
 * Generate(curr_stop, last_stop) is called each time. In order to set the bound
 * , pass in currect stop id and last stop id into the function. The function
 * will return Passenger object with name and destination
 *
 * \subsection PassengerGenerator
 * PassengerGenerator is a constructor that constructs a passenger generator with a list of
 * propabilities and a list of stops called generation_probabilities_ and stops_
 * respectively.
 *
 * GeneratePassengers() is a pure virtual function in Passenger Generator. It is
 * is implemented in RamdomPassengerGenerator class. It will return number of
 * passenger has been generated.
 *
 * \subsection RandomPassengerGenerator
 * RandomPassengerGenerator class is inheritance of PassengerGenerator class.
 *
 * RandomPassengerGenerator constructor constructs a random passenger generator
 * with a list of probabilities and a list of stops called probs and stops respectively.
 *
 * GeneratePassengers() will randomly generates passengers for each stops
 * according to propabilities and return number of passenger generated. After calling the Generate function from
 * PassengerFactory to generate a passenger.

 * \subsection Passenger
 * Passenger class is a class that represent each passenger 
 * each passenger has its name and detination_id.
 * It includes several method to get passengers status and information
 *
 * \subsection Stop
 * Stop class is a class that form a route. It will also update the passengers
 * status at stop when its Update function is called. Each stops has an unique id and longitude and latitude based on real world location. To load passengers on bus,
 * a bus is passed into the LoadPassengers(bus) when it is called. Stop LoadPassengers will call Bus LoadPassenger to add passengers at the stop
 * onto the bus when bus arrived and there is spaces. It will number of passengers add to Bus and delete passengers loaded onto the bus from Stop passenger list.
 * Report function will print the stops status and the output can be redirect to a file.
 *
 * \subsection Route
 * Route class is a class has a name, a list of stops, a list of distances between each stops, number of stops.
 * It also generate passengers by using PassengerGenerator* generator_. 
 * Report method will print the stops status.
 * Clone methods will deep copy constructor.
 * Update method will update each stops in the route and stops will update passengers status in each stops.
 *
 *\subsection Bus
 * Bus class has passengers, outgoing and incoming routes, speed, and name.
 * It will move based on its speed and stop at every stops. When Update function is called the bus will move closer to the next stop.
 * It will load and unload passengers at stops by calling stops' Update function. 
 * 
 * 
 * UML diagrams of the class structure can be viewed by directing
 * to project folder and run the following command
 * \code{.sh}
 * cd <path>/project/docs
 * doxygen Doxyfile
 * \endcode
 * Open the docs/html folder and open index.html, a html webpage will shown.
 * Select "Classes" from dropdown menu and click "Class Hierarchy".
 * 
 * \subsubsection classes Primary Classes
 * Below is a list of primary classes in this program
 * <ul>
 * <li> Bus
 * <li> Passenger
 * <li> Route
 * <li> Stop
 * </ul>
 * 
 * \section Designing  Designing and Implementing the Observer Pattern
 * First, I create an interface called IObserver which includes a pure function UpdateObserver.
 * Then, BusWebObserver inherits from this interface. 
 * The BusWebObserver class is registered to a bus after the bus is clicked on the website.
 * After it is registered, it will than receive an updated BusData everytime the monitored bus changes.
 * Bus Object is modified to implement the IObservable interface, so that it can register, notify, and clear observers.
 *
 * 
 *  \section Designing and Implementing the Decorator Pattern 
 * We need to implement two functionalities with the decorator pattern: changing the bus color depending on the route and changing the color intensity based on the number of passengers.
 * Here, I would focus my discussion on the second functionality: changing intensity of the bus color.
 * <br><br>
 * In my implementation, I set the color intensity based on the number of passengers, and I directly include this in the constructor of Maroon Bus and Gold Bus decorator classes.
 * The pro is that this code is easy to implement. However, the con is that this method is against the spirit of the decorator pattern.
 * The spirit of the decorator pattern is to incrementally change the properties of an object, but here I set the color to the desired intensity directly in the constructor.
 * If we ever add another decorator that incrementally changes the color property, its effect will be overwritten by our current decorator.
 * <br><br>
 * What I should have done is create two other decorator classes: One for making the color brighter and the other one for making the color dimmer. The pro of this design is that the whole pattern will be lower coupling.
 * In other words, the dependency between modules is lower. The design will also follow the principle of closed to change but open to extension more.
 * However, the con is that I have to create two extra classes which takes more time. Overall, both designs are high cohesion and each of them has their own pros and cons.
 */
#endif  // SRC_MAINPAGE_H_
