  
/**
 * @file bus.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_

#include <iostream>
#include <list>
#include <string>

#include "src/data_structs.h"
#include "src/iobserver.h"
#include "src/iobservable.h"
#include "src/passenger.h"
#include "src/passenger_loader.h"
#include "src/passenger_unloader.h"
#include "src/route.h"
#include "src/stop.h"

class PassengerUnloader;
class PassengerLoader;
class Route;
class Stop;

/**
 * @brief Bus interface inheritent from IObservable class
*/
class Bus : public IObservable<BusData>{
  public: 
    virtual bool IsTripComplete() = 0;
    virtual bool LoadPassenger(Passenger *) = 0;  // returning revenue delta
    virtual bool Move() = 0;
    virtual void Update() = 0;
    virtual void Report(std::ostream&) = 0;
    virtual void UpdateBusData() = 0;
    virtual BusData GetBusData() const = 0;
    virtual std::string GetName() const = 0 ;
    virtual Stop * GetNextStop() const = 0;
    virtual size_t GetNumPassengers() const = 0;
    virtual int GetCapacity() const = 0;

    /**
     * a pure virtual function for setting method
     * @param r red component
     * @param g green component
     * @param b blue component
     * @param a transparency
    */
    virtual void SetColor(float r,float g, float b, float a) = 0;
    /**
     * a pure virtual function for checking route
    */
    virtual bool CheckRoute() = 0;
    /**
     * desctrutor
    */
    virtual ~Bus(){} 
} ;

/**
 * @brief concrete class for Bus
*/
class BusBase : public Bus {
 public:
  BusBase(std::string name, Route * out, Route * in, int capacity = 60,
                double speed = 1, std::string type = "Medium");
  bool IsTripComplete() ;
  bool LoadPassenger(Passenger *);  // returning revenue delta
  bool Move();
  void Update();
  void Report(std::ostream&);

  // Vis Getters
  void UpdateBusData();
  BusData GetBusData() const;
  std::string GetName() const { return name_; }
  Stop * GetNextStop() const{ return next_stop_; }
  size_t GetNumPassengers() const { return passengers_.size(); }
  int GetCapacity() const { return passenger_max_capacity_; }

  /**
   * Setter method for color
   * @param r red component
   * @param g green component
   * @param b blue component
   * @param a transparency
   * @return void
  */
  void SetColor(float r,float g, float b, float a);
  /**
    * function for checking route inbound or outbound
    * @return boolean
  */
  bool CheckRoute();

 private:
  int UnloadPassengers();  // returning revenue delta
  int HandleBusStop();
  void ToNextStop();
  double UpdateDistance();
  Route* CurrentRoute();
  // bool Refuel();
  PassengerUnloader * unloader_;
  PassengerLoader * loader_;
  std::list<Passenger *> passengers_;
  int passenger_max_capacity_;
  // double revenue_; // revenue collected from passengers, doesn't include
                      // passengers who pay on deboard
  // double fuel_;   // may not be necessary for our simulation
  // double max_fuel_;
  std::string name_;
  std::string type_;
  double speed_;  // could also be called "distance travelled in one time step"
  Route * outgoing_route_;
  Route * incoming_route_;
  double distance_remaining_;  // when negative?, unload/load procedure occurs
                              // AND next stop set
  Stop * next_stop_;
  // bool trip_complete_;  // [DERIVED data] when BOTH routes are at end, trip
  // is complete

  // Vis data for bus
  BusData bus_data_;

  // total number of passenger
  int total = 0;
};

/**
 * @brief decorator class to color bus
*/
class BusDecorator: public Bus {
 protected:
  Bus* b_bus;
 public:
  BusDecorator(Bus* busBase): b_bus(busBase) {}

  bool IsTripComplete() { return b_bus->IsTripComplete();}
  bool LoadPassenger(Passenger * new_passenger) {return b_bus->LoadPassenger(new_passenger);}  // returning revenue delta
  bool Move() {return b_bus->Move();}
  void Update(){b_bus->Update();}
  void Report(std::ostream& os) {b_bus->Report(os);}

  // Vis Getters
  void UpdateBusData() {b_bus->UpdateBusData();}
  BusData GetBusData() const {return b_bus->GetBusData();}
  
  std::string GetName() const { return b_bus->GetName();}
  Stop * GetNextStop() const{ return b_bus->GetNextStop();}
  size_t GetNumPassengers() const { return b_bus->GetNumPassengers();}
  int GetCapacity() const { return b_bus->GetCapacity();}

  void SetColor(float r,float g, float b, float a) { b_bus->SetColor(r,g,b,a);}
  //check current color
  bool CheckRoute() {return b_bus->CheckRoute();}

  void RegisterObserver(IObserver<BusData>* observer) override {b_bus->RegisterObserver(observer);}
  void ClearObservers() override { b_bus->ClearObservers();}
  void NotifyObservers(BusData* notification) override {b_bus->NotifyObservers(notification);}
};

/**
 * @brief concrete decorator class for coloring bus to maroon
*/
class MaroonBus: public BusDecorator {
 public:
  MaroonBus(Bus* busBase): BusDecorator(busBase) {
    int pg_count = b_bus->GetNumPassengers();
    int totalcapacity = b_bus->GetCapacity();
    int color = 150+pg_count*30;
    b_bus->SetColor(color,0,0,255);}
};

/**
 * @brief concrete decorator class for coloring bus to gold
*/
class GoldBus: public BusDecorator {
 public:
  GoldBus(Bus* busBase): BusDecorator(busBase) {
    int pg_count = b_bus->GetNumPassengers();
    int totalcapacity = b_bus->GetCapacity();
    int color = 181+pg_count*30;
    b_bus->SetColor(207, color,59,255);
    }
};
#endif  // SRC_BUS_H_
