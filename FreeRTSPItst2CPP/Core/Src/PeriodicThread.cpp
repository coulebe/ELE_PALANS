/*
 * PeriodicThread.cpp
 *
 *  Created on: Mar. 6, 2023
 *      Author: Alfred
 */



#ifndef  INC_PERIODICTHREAD_HPP_  // PeriodicThread_t
#include "PeriodicThread.hpp"  //
#endif

//===| Definitions for PeriodicThread_t |=======================================
//-----------------------------------------------------------------------------
osTimerId_t timerId = NULL;
int ThreadCount = 0;
osThreadId_t Threads[10] = {0};

//-----------------------------------------------------------------------------
void PeriodicThread_t::entryFunc()
{
    while(1)
    {
    	osDelayUntil(portMAX_DELAY);
        handlingData();
    };
};

//-----------------------------------------------------------------------------

void PeriodicThread_t::time_init(unsigned long periodS, unsigned long periodNS)
{

    // Only once
    if(timerId == NULL){

        // Sampling period timer
        osTimerAttr_t timerAttr = {
            .name = "samplingTimer"
        };
        timerId = osTimerNew(dispatcher, osTimerPeriodic, &timerAttr);
        if (timerId == NULL) {
            printf("Sampling Timer creation failed!\n");
        } else {
            osTimerStart(timerId, periodS * 1000UL + periodNS / 1000000UL);
        }
    }
}
 //-----------------------------------------------------------------------------\

bool PeriodicThread_t::start(unsigned long periodS, unsigned long periodNS)
{
    time_init(periodS, periodNS);

    osThreadAttr_t threadAttr = {
        .name = "PeriodicThread"
    };
    Threads[ThreadCount] = osThreadNew(entryFunc, NULL, &threadAttr);
    ThreadCount++;

    return (Threads[ThreadCount - 1] != NULL);
}




