#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphNodeGetDependentNodes)(CUgraphNode, CUgraphNode *, size_t *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphNodeGetDependentNodes(CUgraphNode hNode, CUgraphNode *dependentNodes, size_t *numDependentNodes) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphNodeGetDependentNodes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphNodeGetDependentNodes)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphNodeGetDependentNodes = (CUresult (*)(CUgraphNode, CUgraphNode *, size_t *)) __libc_dlsym(libcuda_handle, "cuGraphNodeGetDependentNodes");
			fprintf(stderr, "cuGraphNodeGetDependentNodes:%p\n", original_cuGraphNodeGetDependentNodes);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphNodeGetDependentNodes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphNodeGetDependentNodes(hNode, dependentNodes, numDependentNodes);
		return retval;
	}
}

