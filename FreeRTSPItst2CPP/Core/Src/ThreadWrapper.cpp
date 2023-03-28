/*
 * ThreadWrapper.cpp
 *
 *  Created on: Mar 2, 2023
 *      Author: Alfred
 */

#ifndef INC_THREADWRAPPER_HPP_
#include "ThreadWrapper.hpp"
#endif


void * ThreadWrapper_t::dispatch( void * lpParam )
{
  // Call the actual OO thread handler.
  ((ThreadWrapper_t*)lpParam)->entryFunc();

  return NULL;
}

//-----------------------------------------------------------------------------
int ThreadWrapper_t::start()
{
  // Don't start two threads on the same object.
  if( !isRunning() )
  {


	thread_attr.name = "ThreadWrapper_t";
	thread_attr.priority = (osPriority_t) (taskPriority + osPriorityRealtime);
	thread_attr.stack_size = configMINIMAL_STACK_SIZE;

	// Create the thread.
	    threadId = osThreadNew((osThreadFunc_t) dispatch, NULL, &thread_attr);
	    if (threadId == NULL)
	    {
	      running = false;
	    }
	    else
	    {
	      running = true;
	      printf("Thread %i is running",((int)threadId));
	    }
	  }
	  return (int) threadId;
}

//===| EOF |===================================================================

