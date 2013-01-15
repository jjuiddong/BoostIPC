// SharememLibrary.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "SharedMemoryMng.h"
#include "SharedMemory.h"
#include <iostream>


int _tmain(int argc, _TCHAR* argv[])
{
	DECLARE_TYPE_NAME(CCustomClass);
	class CCustomClass : public sharedmemory::CSharedMem<CCustomClass, TYPE_NAME(CCustomClass)>
	{
	public:
		CCustomClass()
		{
			a = 0;
		}
		CCustomClass(int _a, int _b)
		{
			a = _a;
			b = _b;
		}
		virtual ~CCustomClass()
		{
			int ee =0;

		}
		int a, b, c;
	};

	sharedmemory::Init( "TestSharedMem", sharedmemory::SHARED_SERVER );
	CCustomClass *p0 = new CCustomClass(11,12);
	CCustomClass *p1 = new CCustomClass[ 10];
	CCustomClass *p2 = new CCustomClass(1,12);
	CCustomClass *p3 = new CCustomClass(2,12);
	CCustomClass *p4 = new CCustomClass(3,12);

	p1[ 0].a = 0;
	p1[ 0].b = 1;
	p1[ 0].c = 10;

	std::cout << p0->a << " " << p0->b << " " << p0->c << std::endl;

//	delete p0;
// 	sharedmemory::DeAllocate(p1);	
	sharedmemory::Release();
	return 0;
}

