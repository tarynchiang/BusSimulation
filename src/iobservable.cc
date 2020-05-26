/**
 * @file iobservable.cc
 *
 * @copyright 2020 3081 Staff, All rights reserved.
 */

#include "src/iobservable.h"

template <typename T>
void IObservable<T>::RegisterObserver(IObserver<T>* observer) {
  observers_.push_back(observer);
}

template <typename T>
void IObservable<T>::ClearObservers() {
  std::cout << "Clearing observers vector of size " << observers_.size()
                                                                << std::endl;
  for (int i = 0; i < static_cast<int>(observers_.size()); i++) {
    delete observers_[i];
  }
  observers_.clear();
}

template <typename T>
void IObservable<T>::NotifyObservers(T* notification) {
  for (int i = 0; i < static_cast<int>(observers_.size()); i++) {
    observers_[i]->Notify(notification);
  }
}

template class IObservable<BusData>;
template class IObservable<StopData>;