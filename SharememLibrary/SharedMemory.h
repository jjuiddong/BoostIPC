//------------------------------------------------------------------------
// Name:    SharedMemory.h
// Author:  jjuiddong
// Date:    1/12/2013
// 
// CShareMem Ŭ������ ��ӹ޾Ƽ� �����޸� �Ҵ�(new)�� ������,
// �����޸𸮿� ��ü�� �����ȴ�. (CRTP ����)
// Boost shared memory ���̺귯���� �̿���
//
// CSharedMem Ŭ���� ��ӹ޴� ��
//
// DECLARE_TYPE_NAME(CCustomClass);
// class CCustomClass : public sharedmemory::CSharedMem<CCustomClass, TYPE_NAME(CCustomClass)>
// {
// ...
// }
//
//------------------------------------------------------------------------
#ifndef __SHAREDMEMORY_H__
#define __SHAREDMEMORY_H__

#include "SharedMemoryMng.h"


#define DECLARE_TYPE_NAME(className)					\
struct className##typeNameWrap							\
{														\
	static char* typeName() { return #className; }		\
};
#define TYPE_NAME(className)	className##typeNameWrap


namespace sharedmemory
{
	template<class T, class typeName> // typeName = DECLARE_TYPE_NAME() ��ũ�θ� ���� �������
	class CSharedMem
	{
	protected:
		static int m_Count;

	public:
		static void* operator new (size_t size)
		{
			return Allocate(size);
		}
		void* operator new[] (size_t size)
		{
			return Allocate(size);
		}

		// Debug new
		void* operator new (size_t size, char* lpszFileName, int nLine)
		{
			return Allocate(size);
		}
		// Debug new
		void* operator new[] (size_t size, char* lpszFileName, int nLine)
		{
			return Allocate(size);
		}

		static void operator delete (void *ptr)
		{
			sharedmemory::DeAllocate(ptr);
		}
		static void operator delete[] (void *ptr)
		{
			sharedmemory::DeAllocate(ptr);
		}

	private:
		static void* Allocate(const size_t size)
		{
			std::stringstream ss;
			ss << typeName::typeName() << "#" << ++m_Count;
			return sharedmemory::Allocate(ss.str(), size);
		}
	};

	template<class T, class typeName>
	int CSharedMem<T,typeName>::m_Count=0;
}


#endif // __SHAREDMEMORY_H__