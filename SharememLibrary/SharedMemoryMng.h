//------------------------------------------------------------------------
// Name:    SharedMemoryMng.h
// Author:  jjuiddong
// Date:    1/12/2013
// 
// 공유메모리를 관리하는 클래스다.
//------------------------------------------------------------------------
#ifndef __SHAREDMEMORYMNG_H__
#define __SHAREDMEMORYMNG_H__

namespace sharedmemory
{
	enum SHARED_TYPE
	{ 
		SHARED_SERVER,	// 공유 메모리를 생성해서 사용하는 프로세스
		SHARED_CLIENT	// 공유 메모리를 검색하는 프로세스
	};

	bool	Init( const std::string &name, SHARED_TYPE type, const size_t size=65536 );
	void	Release();

	void*	Allocate(const std::string &name, size_t size);
	void	DeAllocate(void *ptr);
	void*	AllocateAnonymous(const std::string &typeName, size_t size);
	
	typedef struct _SMemoryInfo
	{
		std::string name;
		void *ptr;
		size_t size;
		_SMemoryInfo() {}
		_SMemoryInfo(const char *n, void *p, size_t s):name(n), ptr(p), size(s) {}
	} SMemoryInfo;
	typedef std::list<SMemoryInfo> MemoryList;

	void		EnumerateMemoryInfo(OUT MemoryList &memList);
	std::string ParseObjectName(const std::string &objectName);
	bool		FindMemoryInfo(const std::string &name, OUT SMemoryInfo &info);
	void*	MemoryMapping(const void *srcPtr );

}

#endif // __SHAREDMEMORYMNG_H__