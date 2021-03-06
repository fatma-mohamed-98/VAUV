// Copyright 2021 VorteX-co
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
#ifndef VDVL__EXECUTOR_HPP__
#define VDVL__EXECUTOR_HPP__
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/function.hpp>
/* ********************************
 * The Executor class manages the hardware resources required
 * for the Asynchronous I/O operations.
 * 1- Own io_service object
 * 2- Launches a threads pool to run the service functions
 * 3- Providing callback functions that will be ...
 *  will be invoked at interesting points of the execution.
 * ******************************** */
namespace VDVL
{
class Executor : private boost::noncopyable,
  public boost::enable_shared_from_this<Executor>
{
  // I/O service manages the interface to OS API.
  boost::asio::io_service _io;
  // Worker function invoked by each new worker thread
  // Internaly each thread  calls the run() method of
  // the boost::asio::io_service object.
  void Worker(boost::asio::io_service & io_);

public:
  // Callbacks for each interesting points of the execution.
  // OnError callback for Error handling
  boost::function<void(boost::asio::io_service &, boost::system::error_code)>
  OnError;
  // OnException callback for Exception handling
  boost::function<void(boost::asio::io_service &, const std::exception &)>
  OnException;
  // OnRun callback is a userdefined function to be executed on starting
  boost::function<void(boost::asio::io_service &)> OnRun;
  // A method for just returing the I/O service object by ref
  boost::asio::io_service & GetIO();
  // Run method for starting the execution process
  void Run(unsigned int numThreads = -1);
};
}  // namespace VDVL
#endif  // VDVL__EXECUTOR_HPP__
