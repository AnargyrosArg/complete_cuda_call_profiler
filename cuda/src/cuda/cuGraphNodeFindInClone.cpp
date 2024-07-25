#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphNodeFindInClone)(CUgraphNode *, CUgraphNode, CUgraph);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphNodeFindInClone(CUgraphNode *phNode, CUgraphNode hOriginalNode, CUgraph hClonedGraph) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphNodeFindInClone():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphNodeFindInClone)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphNodeFindInClone = (CUresult (*)(CUgraphNode *, CUgraphNode, CUgraph)) __libc_dlsym(libcuda_handle, "cuGraphNodeFindInClone");
			fprintf(stderr, "cuGraphNodeFindInClone:%p\n", original_cuGraphNodeFindInClone);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphNodeFindInClone():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphNodeFindInClone(phNode, hOriginalNode, hClonedGraph);
		return retval;
	}
}

