/*
 * ThreadWrapper.hpp
 *
 *  Created on: Mar 1, 2023
 *      Author: alfre
 */

#ifndef INC_THREADWRAPPER_HPP_
#define INC_THREADWRAPPER_HPP_


//Constants
#define LOWEST_PRIORITY  0
#define HIGHEST_PRIORITY configMAX_PRIORITIES - 1

//Classic dependencies
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <FreeRTOSConfig.h>
#include "cmsis_os.h"




class ThreadWrapper_t
{
  protected:
    ThreadWrapper_t
      ( int _taskPriority = configMAX_PRIORITIES - 1
       ,int _taskStackSize = 0
      )
      :running( false)
      ,taskPriority( _taskPriority )
      ,taskStackSize( _taskStackSize )
    {
    };

  public:
    virtual ~ThreadWrapper_t()
    {
      if( threadId != NULL )
      {
        // Release thread handle.
    	  osStatus_t status = osThreadTerminate(threadId);// stop the thread
    	  if (status == osOK) {
    	     printf("Thread successfully stopped");                                           // Thread was terminated successfully
    	  }
    	  else{
    		  printf("Thread failed to stop");
    	  }
      };
    };

    bool isRunning()const { return running; };
    unsigned long getThreadId() const { return (unsigned long)threadId; };
    int getTaskPriority(){return taskPriority; };

    // Return true if thread is started, false otherwise.
    //
    int start();

    //--| Virtual Interfaces |-------------------------------------------------
      //--| ThreadWrapper_t |--->
        protected:
          // OO thread handler.
          //
          virtual void entryFunc() = 0;
    //--end--------------------------------------------------------------------

  private:
    // Indicates if server construction was successful.
    //
    bool running;
    int taskPriority;
    int taskStackSize;
    osThreadId_t  threadId;

//    struct sched_param mySchedParam;
//    int hThread;
    osThreadAttr_t thread_attr;

    // Thread function dispatch.
    static void * dispatch( void * lpParam );
};




#endif /* INC_THREADWRAPPER_HPP_ */
