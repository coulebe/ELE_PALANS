/*
 * PeriodicThread.hpp
 *
 *  Created on: Mar. 6, 2023
 *      Author: alfre
 */

#ifndef INC_PERIODICTHREAD_HPP_
#define INC_PERIODICTHREAD_HPP_

#ifndef  INC_THREADWRAPPER_HPP_  // ThreadWrapper_t
# include "ThreadWrapper.hpp" //
#endif

#include <time.h>
//#include <cmsis_os.h>

//=============================================================================
//
class PeriodicThread_t : public ThreadWrapper_t
{
  public:
    PeriodicThread_t
     ( int _taskPriority = configMAX_PRIORITIES - 1
      ,int _taskStackSize = 0
     )
     :ThreadWrapper_t(_taskPriority, _taskStackSize)
     {};
    ~PeriodicThread_t(){};

    bool start(unsigned long periodS, unsigned long periodNS);

    //--| Virtual Interfaces |-------------------------------------------------
      //--| ThreadWrapper_t |--->
      protected:
         void entryFunc();
      //--| Newly defined |--->
         virtual void handlingData() = 0;
	  //--| End |--->

	  //void catcher(){printf("Test handler\n");};

  private:
         static osTimerId_t timerId;
		 static int ThreadCount;
		 static osThreadId_t Threads[10];

		 void time_init(unsigned long periodS, unsigned long periodNS);
		 static void dispatcher(int signo);
//		 static void handler(int signo) {}

};




#endif /* INC_PERIODICTHREAD_HPP_ */
