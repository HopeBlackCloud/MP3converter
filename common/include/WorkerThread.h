/****************************************************************
 This class is the base class of encoder thread. If a class tends
 to derive from this class, should implement Run method.

 Author: Murat Karabulut
 Date:   06.06.2018
*****************************************************************/
#ifndef WORKER_THREAD_H
#define WORKER_THREAD_H

#include "pthread.h"

namespace MediaFramework
{
	class WorkerThread
	{
		public:
		   WorkerThread()          {  }
		   virtual ~WorkerThread() {  }

		   bool StartThread()
		   {
			  return (pthread_create(&thread, NULL, RunFunc, this) == 0);
		   }

		   int WaitForThreadToExit()
		   {
			  return pthread_join(thread, NULL);
		   }

		protected:
		   virtual void Run() = 0;

		private:
		   static void * RunFunc(void * This) 
		   { 
			   ((WorkerThread *)This)->Run(); 
	   
			   return NULL;
		   }

		   pthread_t thread;
	};
}

#endif







