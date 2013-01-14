// Sharemem1.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <iostream> 

//using namespace boost;
using namespace boost::interprocess;
//using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	try 
	{
		shared_memory_object::remove("Hello");

 		shared_memory_object sharedmem1 (create_only, "Hello", read_write);

		// setting the size of the shared memory
		sharedmem1.truncate (65536);

		// map the shared memory to current process 
		mapped_region mmap (sharedmem1, read_write, 0, 256); 

		// access the mapped region using get_address
		std::strcpy(static_cast<char* >(mmap.get_address()), "Hello World!\n");

		//… more code follows
	}
	catch (interprocess_exception&e) 
	{
		// .. .  clean up 
		std::cout << e.what() << std::endl;
		std::cout << "client1 error\n";
	}

	return 0;
}

