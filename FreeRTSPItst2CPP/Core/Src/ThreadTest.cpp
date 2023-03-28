/*
 * ThreadTest.cpp
 *
 *  Created on: Mar. 10, 2023
 *      Author: Alfred
 */

#ifndef INC_THREADTEST_HPP_
# include "ThreadTest.hpp" //
#endif


void ThreadWrapperTest_t::entryFunc()
{
	for(;;)
	{
		printf("Hello world!\n");
		osDelay(1500);
	}
}

//void PeriodicThreadTest_t::handlingData()
//{
//	printf("Hello world!\tExt_ID : %i \t Priority : %i\n ", threadNumber, getTaskPriority());
//	osDelay(100);
//};


//-----------------------------------------------------------------------------

//===| EOF |===================================================================


