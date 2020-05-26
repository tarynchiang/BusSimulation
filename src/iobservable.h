/**
 * @file iobservable.h
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */

#ifndef SRC_IOBSERVABLE_H_
#define SRC_IOBSERVABLE_H_

#include <vector>
#include <iostream>

#include "src/iobserver.h"
#include "src/data_structs.h"

/**
 * @brief Interface for obects that accept observer by implementing template
*/
template <typename T>
class IObservable{
 public:
  IObservable() : observers_() {}
  virtual void RegisterObserver(IObserver<T>* observer);
  virtual void ClearObservers();
  virtual void NotifyObservers(T* notification);
 private:
  std::vector<IObserver<T>*> observers_;
};

#endif  // SRC_IOBSERVABLE_H_
