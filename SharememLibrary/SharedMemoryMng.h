//------------------------------------------------------------------------
// Name:    SharedMemoryMng.h
// Author:  jjuiddong
// Date:    1/12/2013
// 
// �����޸𸮸� �����ϴ� Ŭ������.
//------------------------------------------------------------------------
#ifndef __SHAREDMEMORYMNG_H__
#define __SHAREDMEMORYMNG_H__

namespace sharedmemory
{
	enum SHARED_TYPE
	{ 
		SHARED_SERVER,	// ���� �޸𸮸� �����ؼ� ����ϴ� ���μ���
		SHARED_CLIENT	// ���� �޸𸮸� �˻��ϴ� ���μ���
	};

	bool	Init( const std::string &name, SHARED_TYPE type, const size_t size=65536 );
	void	Release();

	void*	Allocate(const std::string &name, size_t size);
	void	DeAllocate(void *ptr);

	
	typedef struct _SMemoryInfo
	{
		std::string name;
		void *ptr;
		size_t size;
		_SMemoryInfo() {}
		_SMemoryInfo(const char *n, void *p, size_t s):name(n), ptr(p), size(s) {}
	} SMemoryInfo;
	typedef std::list<SMemoryInfo> MemoryList;

	void	EnumerateMemoryInfo(OUT MemoryList &memList);

}

#endif // __SHAREDMEMORYMNG_H__