/*
 * alt_main.cpp
 *
 *  Created on: Feb. 16, 2023
 *      Author: alfred
 */


#include "stdio.h"
#include "alt_main.h"
#include "ThreadTest.hpp"


int alt_main()
{
	/* Initialization */

	while (1)
	{
		/* Super loop */
//		printf( "Hello World CPP\n\r") ;
		ThreadWrapperTest_t* t1 = new ThreadWrapperTest_t();

		t1->start();





	}
	return 0;
}



