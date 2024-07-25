#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphNodeGetDependencies)(CUgraphNode, CUgraphNode *, size_t *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphNodeGetDependencies(CUgraphNode hNode, CUgraphNode *dependencies, size_t *numDependencies) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphNodeGetDependencies():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphNodeGetDependencies)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphNodeGetDependencies = (CUresult (*)(CUgraphNode, CUgraphNode *, size_t *)) __libc_dlsym(libcuda_handle, "cuGraphNodeGetDependencies");
			fprintf(stderr, "cuGraphNodeGetDependencies:%p\n", original_cuGraphNodeGetDependencies);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphNodeGetDependencies():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphNodeGetDependencies(hNode, dependencies, numDependencies);
		return retval;
	}
}

