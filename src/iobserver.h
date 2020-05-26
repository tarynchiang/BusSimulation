/**
 * @file iobserver.h
 *
 * @copyright 2020 3081 Staff, All rights reserved
 */

#ifndef SRC_IOBSERVER_H_
#define SRC_IOBSERVER_H_

#include "src/data_structs.h"

/**
 * @brief template for IObserver 
*/
template <typename T>
class IObserver{
 public:
  virtual void Notify(T* info) = 0;
};

#endif  // SRC_IOBSERVER_H_
