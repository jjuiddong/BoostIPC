// Client.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <fstream> 
#include <iostream> 
#include <boost/interprocess/sync/file_lock.hpp> 
#include <cstdlib>
#include <iostream> 

using namespace boost::interprocess;
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	try 
	{
		std::string fileName("test"); 
		std::fstream file;

		file.open(fileName.c_str(), std::ios::out | std::ios::binary | 
			std::ios::trunc); 
		if (!file.is_open() || file.bad()) 
		{ 
			std::cout << "Open failed" << std::endl; 
			exit(-1); 
		}

		try 
		{ 
			file_lock f_lock(fileName.c_str());
			f_lock.lock();
			std::cout << "Locked in Process 1" << std::endl;
			file.write("Process 1", 9);
			file.flush(); 
			f_lock.unlock();
			std::cout << "Unlocked from Process 1" << std::endl;
		} 
		catch (interprocess_exception& e) 
		{ 
			std::cout << e.what( ) << std::endl;
		}

		file.close();

// 		message_queue::remove( "mq" );
// 		message_queue mq (create_only,   // only create
// 			"mq",              // name
// 			20,                 //max message count
// 			sizeof(int)      //max message size
// 			);
// 
// 		// now send the messages to the queue
// 		for (int i=0; i<20; ++i) 
// 			mq.send(&i, sizeof(int), 0); // the 3rd argument is the priority 



// 		// creating our first shared memory object.
//  		shared_memory_object sharedmem1 (open_only, "Hello", read_write);
// 
// 		// setting the size of the shared memory
// 		sharedmem1.truncate (256);
// 
// 		// map the shared memory to current process 
// 		mapped_region mmap (sharedmem1, read_write, 0, 256); 
// 
// 		// access the mapped region using get_address
// 		std::strcpy(static_cast<char* >(mmap.get_address()), "Hello World!\n");

		// … more code follows
	}
	catch (interprocess_exception&e) 
	{
		// .. .  clean up 
		cout << e.what() << endl;
		printf( "client1 error" );
	}

	return 0;
}
