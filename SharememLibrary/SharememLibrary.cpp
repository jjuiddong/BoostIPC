// SharememLibrary.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "SharedMemoryMng.h"
#include "SharedMemory.h"
#include <iostream>

DECLARE_TYPE_NAME(CCustomClass);
class CCustomClass : public sharedmemory::CSharedMem<CCustomClass, TYPE_NAME(CCustomClass)>
{
public:
	CCustomClass()
	{
		m_a = 0;
	}
	CCustomClass(int _a, int _b)
	{
		m_a = _a;
		m_b = _b;
	}
	virtual ~CCustomClass()
	{
		int ee =0;

	}
	int m_a, m_b, m_c;
};


DECLARE_TYPE_NAME(SCustomStruct);
struct SCustomStruct : public sharedmemory::CSharedMem<SCustomStruct, TYPE_NAME(SCustomStruct)>
{
	int a;
	float b;
	short c;
	char d;
	double e;
};


int _tmain(int argc, _TCHAR* argv[])
{
	sharedmemory::Init( "MySharedMemory", sharedmemory::SHARED_SERVER );


	CCustomClass *p0 = new CCustomClass(11,12);
	CCustomClass *p1 = new CCustomClass[ 10];
	CCustomClass *p2 = new CCustomClass(1,12);
	CCustomClass *p3 = new CCustomClass(2,12);
	CCustomClass *p4 = new CCustomClass(3,12);
	p1[ 0].m_a = 0;
	p1[ 0].m_b = 1;
	p1[ 0].m_c = 10;
	std::cout << p0->m_a << " " << p0->m_b << " " << p0->m_c << std::endl;


	SCustomStruct *p11 = new SCustomStruct();
	SCustomStruct *p12 = new SCustomStruct();
	SCustomStruct *p13 = new SCustomStruct();
	p11->a = 1;
	p12->a = 2;
	p13->a = 3;


//	delete p0;
// 	sharedmemory::DeAllocate(p1);	
//	sharedmemory::Release();
	return 0;
}

