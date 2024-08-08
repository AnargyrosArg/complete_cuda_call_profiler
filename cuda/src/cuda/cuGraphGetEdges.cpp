#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphGetEdges)(CUgraph, CUgraphNode *, CUgraphNode *, size_t *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphGetEdges(CUgraph hGraph, CUgraphNode *from, CUgraphNode *to, size_t *numEdges) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphGetEdges():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphGetEdges)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphGetEdges = (CUresult (*)(CUgraph, CUgraphNode *, CUgraphNode *, size_t *)) __libc_dlsym(libcuda_handle, "cuGraphGetEdges");
			fprintf(stderr, "cuGraphGetEdges:%p\n", original_cuGraphGetEdges);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphGetEdges():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphGetEdges(hGraph, from, to, numEdges);
		return retval;
	}
}

