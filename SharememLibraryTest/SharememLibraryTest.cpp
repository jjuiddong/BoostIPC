// SharememLibraryTest.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "../SharememLibrary/SharedMemory.h"
#include "../SharememLibrary/SharedMemoryMng.h"
#include <boost/foreach.hpp>
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	sharedmemory::Init( "TestSharedMem", sharedmemory::SHARED_CLIENT );

	sharedmemory::MemoryList memList;
	sharedmemory::EnumerateMemoryInfo( memList );

	BOOST_FOREACH(sharedmemory::SMemoryInfo &info, memList)
	{
		std::cout << "name: " << info.name << ", ptr: " << info.ptr << ", size: " << info.size << std::endl;
	}

	sharedmemory::Release();
	return 0;
}
