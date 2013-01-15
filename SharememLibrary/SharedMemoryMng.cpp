
#include "stdafx.h"
#include "SharedMemoryMng.h"
#include <boost/interprocess/shared_memory_object.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/unordered_map.hpp>     //boost::unordered_map
//#include <boost/interprocess/containers/map.hpp>
#include <functional>                  //std::equal_to
#include <boost/functional/hash.hpp>   //boost::hash

using namespace boost::interprocess;

namespace sharedmemory
{
	typedef managed_shared_memory::segment_manager						segment_manager_t;
	typedef allocator<char, segment_manager_t>							char_allocator;
	typedef basic_string<char, std::char_traits<char>, char_allocator>	shm_string;

	typedef struct _complex_data
	{
		//void *ptr;
		size_t size;
		// 공유메모리 주소는 프로세스에 따라 달라지므로 handle을 공유해야 한다.
		managed_shared_memory::handle_t handle;
		_complex_data() {}
		_complex_data(size_t s, managed_shared_memory::handle_t h) : size(s),handle(h) {}
	} complex_data;

	typedef std::pair<const shm_string, complex_data>					shm_map_value_type;
	typedef allocator<shm_map_value_type, segment_manager_t>			shm_map_type_allocator;
	typedef boost::unordered_map< shm_string, complex_data,
		boost::hash<shm_string>, std::equal_to<shm_string>,
		shm_map_type_allocator>											shm_complex_map;

	// variables
	managed_shared_memory *n_pSegment = NULL;
	shm_complex_map *n_pMap = NULL;
	std::string n_Name;
	SHARED_TYPE n_Type;

	// functions
	bool InitSharedMemory_Server(const std::string &name, const size_t size);
	bool InitSharedMemory_Client(const std::string &name);
}


using namespace sharedmemory;

//------------------------------------------------------------------------
// 공유메모리 초기화
//------------------------------------------------------------------------
bool sharedmemory::Init( const std::string &name, SHARED_TYPE type, const size_t size ) // size=65536
{
	n_Name = name;
	n_Type = type;
	bool result = false;

	try 
	{
		switch (type)
		{
		case SHARED_SERVER: result = InitSharedMemory_Server(name, size); break;
		case SHARED_CLIENT: result = InitSharedMemory_Client(name); break;
		}
	}
	catch (interprocess_exception &e)
	{
		std::string errorStr = e.what(); // debug용
		return false;
	}

	return result;
}


//------------------------------------------------------------------------
// 공유 메모리 제거
//------------------------------------------------------------------------
void sharedmemory::Release()
{
	if (SHARED_SERVER == n_Type) // ServerType일때만 지울수있다.
	{
		shared_memory_object::remove(n_Name.c_str());
	}
	SAFE_DELETE(n_pSegment);
}


//------------------------------------------------------------------------
// 공유메모리 클라이언트용 초기화
//------------------------------------------------------------------------
bool sharedmemory::InitSharedMemory_Client(const std::string &name)
{
	n_pSegment = new managed_shared_memory(open_only, name.c_str());
	n_pMap = n_pSegment->find<shm_complex_map>("StringKeyPointerValueMap").first;
	return n_pMap? true : false;
}


//------------------------------------------------------------------------
// 공유메모리 서버용 초기화
//------------------------------------------------------------------------
bool sharedmemory::InitSharedMemory_Server(const std::string &name, const size_t size)
{
	shared_memory_object::remove(name.c_str());
	n_pSegment = new managed_shared_memory(create_only, name.c_str(),  size);
	n_pMap = n_pSegment->construct<shm_complex_map>("StringKeyPointerValueMap")
		(10, boost::hash<shm_string>(), std::equal_to<shm_string>(), 
		n_pSegment->get_allocator<shm_map_value_type>() );

	return true;
}


//------------------------------------------------------------------------
// 메모리를 할당해서 리턴한다.
// map에 할당받은 객체의 이름과 주소를 저장한다.
//------------------------------------------------------------------------
void* sharedmemory::Allocate(const std::string &name, size_t size)
{
	RETV(!n_pSegment, NULL);
	RETV(!n_pMap, NULL);

	// 현재 Map에 데이타를 찾으려면 공유메모리를 이용하는 방법 밖에 없다.
	shm_string str( n_pSegment->get_allocator<shm_string>() );
	str = name.c_str();
	shm_complex_map::iterator it = n_pMap->find( str );
	if (n_pMap->end() != it)
		return NULL; // 이미 존재한다면 실패

	void *ptr = n_pSegment->allocate(size, std::nothrow_t());
	RETV(!ptr, NULL);

	// 공유메모리 주소는 프로세스에 따라 달라지므로 handle을 공유해야 한다.
	managed_shared_memory::handle_t handle = n_pSegment->get_handle_from_address(ptr);

	n_pMap->insert( shm_map_value_type(str,complex_data(size,handle)) );
	return ptr;
}


//------------------------------------------------------------------------
// 메모리를 반납한다.
//------------------------------------------------------------------------
void sharedmemory::DeAllocate(void *ptr)
{
	RET(!n_pSegment);
	RET(!n_pMap);

	const managed_shared_memory::handle_t handle = n_pSegment->get_handle_from_address(ptr);

	shm_complex_map::iterator it = n_pMap->begin();
	while (n_pMap->end() != it)
	{
		if (it->second.handle == handle)
		{
			n_pSegment->deallocate(ptr);
			n_pMap->erase(it);
			break;
		}
		++it;
	}
}


//------------------------------------------------------------------------
// n_pMap에 저장된 정보를 리턴한다.
//------------------------------------------------------------------------
void sharedmemory::EnumerateMemoryInfo(OUT MemoryList &memList)
{
	RET(!n_pSegment);
	RET(!n_pMap);

	shm_complex_map::iterator it = n_pMap->begin();
	while (n_pMap->end() != it)
	{
		void *ptr = n_pSegment->get_address_from_handle(it->second.handle);
		memList.push_back( SMemoryInfo(it->first.c_str(), ptr, it->second.size) );
		++it;
	}
}

