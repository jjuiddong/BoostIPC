// SharememHeapMapTest.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/allocators/node_allocator.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream> 
#include <string>
#include <boost/unordered_map.hpp>     //boost::unordered_map
#include <functional>                  //std::equal_to
#include <boost/functional/hash.hpp>   //boost::hash


using namespace boost::interprocess;

int _tmain(int argc, _TCHAR* argv[])
{
	try 
	{
		// creating our first shared memory object.
		managed_shared_memory segment(open_only, "MySharedMemory");

		typedef managed_shared_memory::segment_manager								segment_manager_t;
		typedef allocator<char, segment_manager_t>									char_allocator;
		typedef basic_string<char, std::char_traits<char>, char_allocator>			shm_string;

		typedef int complex_data;
		typedef std::pair<const shm_string, complex_data>							shm_map_value_type;
		typedef allocator<shm_map_value_type, segment_manager_t>					shm_map_type_allocator;
		typedef boost::unordered_map< shm_string, complex_data,
			boost::hash<shm_string>, std::equal_to<shm_string>,
			shm_map_type_allocator>													shm_complex_map;

		shm_complex_map *pMap = segment.find<shm_complex_map>("MyHashMap").first;
		if (pMap)
		{
			int cnt = 0;
			shm_complex_map::iterator it = pMap->begin();
			while (pMap->end() != it)
			{
				std::cout << it->first << "=" << it->second << std::endl;
				++it;
				++cnt;
			}
			std::cout << "count = " << cnt << std::endl;
		}

	}
	catch (interprocess_exception&e) 
	{
		// .. .  clean up 
		std::cout << e.what() << std::endl;
		std::cout << "client1 error\n";
	}

	return 0;
}

