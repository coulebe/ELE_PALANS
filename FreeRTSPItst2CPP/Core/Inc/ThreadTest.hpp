/*
 * ThreadTest.hpp
 *
 *  Created on: Mar. 10, 2023
 *      Author: alfre
 */

#ifndef INC_THREADTEST_HPP_
#define INC_THREADTEST_HPP_


#ifndef  INC_THREADWRAPPER_HPP_  // ThreadWrapper_t
# include "ThreadWrapper.hpp" //
#endif


//#ifndef  INC_PERIODICTHREAD_HPP_  // PeriodicThread_t
//# include "PeriodicThread.hpp" //
//#endif


//
class ThreadWrapperTest_t : public ThreadWrapper_t
{
    public:
      ThreadWrapperTest_t
        (int _threadNumber = 0
        ,int _taskPriority = HIGHEST_PRIORITY
        ,int _taskStackSize = 0
       )
        :ThreadWrapper_t(_taskPriority,_taskPriority)
        ,threadNumber(_threadNumber)
        {};
       ~ThreadWrapperTest_t()
       {};
       void handlingData();
     protected:
       void entryFunc();
       int threadNumber;
};

//===========================================================================
//class PeriodicThreadTest_t : public PeriodicThread_t
//{
//    public:
//      PeriodicThreadTest_t
//       ( int _threadNumber = 0
//        ,int _taskPriority = HIGHEST_PRIORITY
//        ,int _taskStackSize = 0
//       )
//       :PeriodicThread_t(_taskPriority,_taskPriority)
//       ,threadNumber(_threadNumber)
//       {};
//      ~PeriodicThreadTest_t()
//      {};
//
//    protected:
//      void handlingData();
//      int threadNumber;
//
//};

//===========================================================================



#endif /* INC_THREADTEST_HPP_ */
