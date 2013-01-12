// Client2.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>
#include <boost/interprocess/sync/file_lock.hpp> 
#include <iostream> 
#include <fstream> 
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

		// .. as in Listing 11
		file_lock f_lock(fileName.c_str());
		f_lock.lock();
		std::cout << "Locked in Process 2" << std::endl;
		system("sleep 4"); 
		file.write("Process 2", 9);
		file.flush(); 
		f_lock.unlock();
		std::cout << "Unlocked from Process 2" << std::endl;
		file.close(); 


		// opening the message queue whose name is mq
// 		message_queue mq (open_only,     // only open
// 			"mq"               // name
// 			);
// 		size_t recvd_size; 
// 		unsigned int priority; 
// 
// 		// now send the messages to the queue
// 		for (int i=0; i<20; ++i) 
// 		{ 
// 			int buffer[20]; 
// 			mq.receive ((void*) buffer, sizeof(buffer), recvd_size, priority); 
// 			if (recvd_size != sizeof(buffer)) 
// 			{
// 				; // do the error handling
// 			}
// 			cout << buffer << " " << recvd_size << " " << priority << endl;
// 		}



// 		// creating our first shared memory object.
// 		shared_memory_object sharedmem1 (open_only, "Hello", read_only);
// 
// 		// map the shared memory to current process 
// 		mapped_region mmap (sharedmem1, read_only, 0, 256); 
// 
// 		// access the mapped region using get_address
// 		//std::strcpy(static_cast<char* >(mmap.get_address()), "Hello World!\n");
// 		printf( "sharedmem : %s\n", static_cast<char* >(mmap.get_address()) );
// 
// 		shared_memory_object::remove("Hello");

	} 
	catch (interprocess_exception&e) 
	{
		// .. .  clean up 
		cout << e.what() << endl;
		printf( "client2 error\n" );
	} 

	return 0;
}

