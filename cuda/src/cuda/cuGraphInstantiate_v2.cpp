#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphInstantiate_v2)(CUgraphExec *, CUgraph, CUgraphNode *, char *, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphInstantiate_v2(CUgraphExec *phGraphExec, CUgraph hGraph, CUgraphNode *phErrorNode, char *logBuffer, size_t bufferSize) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphInstantiate_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphInstantiate_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphInstantiate_v2 = (CUresult (*)(CUgraphExec *, CUgraph, CUgraphNode *, char *, size_t)) __libc_dlsym(libcuda_handle, "cuGraphInstantiate_v2");
			fprintf(stderr, "cuGraphInstantiate_v2:%p\n", original_cuGraphInstantiate_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphInstantiate_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphInstantiate_v2(phGraphExec, hGraph, phErrorNode, logBuffer, bufferSize);
		return retval;
	}
}

