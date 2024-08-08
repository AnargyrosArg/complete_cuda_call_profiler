#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphRemoveDependencies)(CUgraph, const CUgraphNode *, const CUgraphNode *, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphRemoveDependencies(CUgraph hGraph, const CUgraphNode *from, const CUgraphNode *to, size_t numDependencies) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphRemoveDependencies():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphRemoveDependencies)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphRemoveDependencies = (CUresult (*)(CUgraph, const CUgraphNode *, const CUgraphNode *, size_t)) __libc_dlsym(libcuda_handle, "cuGraphRemoveDependencies");
			fprintf(stderr, "cuGraphRemoveDependencies:%p\n", original_cuGraphRemoveDependencies);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphRemoveDependencies():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphRemoveDependencies(hGraph, from, to, numDependencies);
		return retval;
	}
}

