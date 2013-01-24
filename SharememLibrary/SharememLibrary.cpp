// SharememLibrary.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "SharedMemoryMng.h"
#include "SharedMemory.h"
#include "SharedMemoryString.h"
#include "SharedMemoryList.h"
#include <iostream>
#include <Windows.h>

//using namespace std;

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


struct SCustomSubStruct
{
	int a0;
	unsigned int a1;
	float b0;
	char c0;
	unsigned char c1;
	bool d0;
	short e0;
	unsigned short e1;
	BYTE f0;
	DWORD g0;

};

DECLARE_TYPE_NAME(_SData);
typedef struct _SData : public sharedmemory::CSharedMem<_SData, TYPE_NAME(_SData)>
{
	int a;
	char b;
	float c;

} SData;

enum VAR_TYPE
{
	TYPE1,
	TYPE2,
	TYPE3,
	TYPE4,
};

DECLARE_TYPE_NAME(SCustomStruct);
struct SCustomStruct : public sharedmemory::CSharedMem<SCustomStruct, TYPE_NAME(SCustomStruct)>
{
	int a;
	float b;
// 	short c;
// 	char d;
// 	double e;
// 	bool f;
	int arr[10];
	SCustomSubStruct sub[5];
	char strings[ 32];
	SData data1;
	SData *pdata2;
	VAR_TYPE varType;

};


namespace testName
{
	class CA
	{
	public:
		CA() {
			m_pStr = new char[32];
			strcpy_s(m_pStr, 32, "goodbye");
		}
		virtual ~CA() {}
		int m_id;
		char *m_pStr;
		virtual void func() 
		{
			std::cout << "CA::func()\n";
		}
	};

	class CC
	{
	public:
		CC() {}
		virtual ~CC() {}
		float m_ccVal;
		std::string m_str;
		sharedmemory::shm_list< sharedmemory::shm_string > lst;
	};

	class CD
	{
	public:
		CD() : m_shmString("shm_string test hello")
		{
			strcpy_s(m_name, sizeof(m_name), "hello");
		}
		char m_name[32];
		sharedmemory::shm_string m_shmString;
	};

	DECLARE_TYPE_NAME_SCOPE(testName, CB);
	class CB : public CA, public CC, public CD, public sharedmemory::CSharedMem<CB, TYPE_NAME(CB)>
	{
	public:
		CB() {}
		virtual ~CB() {}
		double m_val;
		virtual void func()
		{
			std::cout << "CB::func()\n";
		}
	};

}

int _tmain(int argc, _TCHAR* argv[])
{
	sharedmemory::Init( "MySharedMemory", sharedmemory::SHARED_SERVER );

  	sharedmemory::shm_string str2;
  	str2 = "aaa";
	std::cout << str2 << std::endl;

	testName::CB *pcb = new ("LookatMe") testName::CB();
	pcb->m_id = 101;
	pcb->m_val = 12.34f;
	pcb->func();

	pcb->lst.push_back( "test1" );
	pcb->lst.push_back( "test2" );
	pcb->lst.push_back( "test3" );
	pcb->lst.push_back( "test4" );


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

// 	p11->a = 1;
// 	p11->f = false;
	p11->pdata2 = new SData;
	p11->pdata2->a = 1234;
	p11->varType = TYPE3;


	p11->arr[ 0] = 1;
	p11->arr[ 1] = 2;
	p11->arr[ 2] = 3;
	p11->sub[0].c0 = 'a';
	p11->sub[0].d0 = true;
	p11->sub[0].e0 = 101;


// 	p12->a = 2;
// 	p12->f = true;

// 	p13->a = 3;
// 	p13->f = false;
	p13->arr[ 0] = 1;
	p13->arr[ 1] = 2;
	p13->arr[ 2] = 3;
	p13->sub[0].c0 = 'z';
	p13->sub[0].d0 = false;
	p13->sub[0].e0 = 123;


//	delete p0;
// 	sharedmemory::DeAllocate(p1);	
//	sharedmemory::Release();
	return 0;
}

