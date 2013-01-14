// SharememHeap.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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
	char name[100];
	basic_bufferstream<char> formatter(name,100);

	formatter << 10 << std::ends;
	formatter.seekp(0);
	formatter << 11 << std::ends;
	formatter.seekp(0);
	formatter << 12 << std::ends;
	formatter.seekp(0);

	std::stringstream ss;
	ss << "aa";


	try 
	{
		class CCustomClass
		{
		public:
			CCustomClass() {}
			CCustomClass(int _a, int _b) : a(_a), b(_b) {}
			virtual ~CCustomClass() {}
		protected:
			int a;
			int b;
		};

		struct shm_remove
		{
			shm_remove() 
			{ shared_memory_object::remove("MySharedMemory"); }
			~shm_remove()
			{ shared_memory_object::remove("MySharedMemory"); }
		} remover;

		// creating our first shared memory object.
		managed_shared_memory segment(create_only, "MySharedMemory",  
									  65536);

		typedef allocator<CCustomClass, 
			managed_shared_memory::segment_manager> Allocator;
		typedef Allocator::pointer Ptr;
		Allocator allocator_instance(segment.get_segment_manager());

		CCustomClass *pc1 = 
			segment.construct<CCustomClass>("v1", std::nothrow_t())();
		CCustomClass *pc2 = 
			segment.construct<CCustomClass>("v2", std::nothrow_t())();

		managed_shared_memory::const_named_iterator i = 
			segment.named_begin();
		while (segment.named_end() != i)
		{
			const char *name = i->name();
			std::cout << name << " : " << i->name_length() 
				<< " " << i->value() << std::endl;
			++i;
		}

		segment.destroy_ptr(pc1);
		segment.destroy_ptr(pc2);

		// 
		// 		// map the shared memory to current process 
		// 		mapped_region mmap (sharedmem1, read_write, 0, 256); 
		// 
		// 		// access the mapped region using get_address
		// 		std::strcpy(static_cast<char* >(mmap.get_address()), "Hello World!\n");

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

