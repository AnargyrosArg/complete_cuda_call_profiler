#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphInstantiateWithFlags)(CUgraphExec *, CUgraph, unsigned long long);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphInstantiateWithFlags(CUgraphExec *phGraphExec, CUgraph hGraph, unsigned long long flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphInstantiateWithFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphInstantiateWithFlags)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphInstantiateWithFlags = (CUresult (*)(CUgraphExec *, CUgraph, unsigned long long)) __libc_dlsym(libcuda_handle, "cuGraphInstantiateWithFlags");
			fprintf(stderr, "cuGraphInstantiateWithFlags:%p\n", original_cuGraphInstantiateWithFlags);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphInstantiateWithFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphInstantiateWithFlags(phGraphExec, hGraph, flags);
		return retval;
	}
}

