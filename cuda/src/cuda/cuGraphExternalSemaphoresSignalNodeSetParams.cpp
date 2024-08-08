#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExternalSemaphoresSignalNodeSetParams)(CUgraphNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExternalSemaphoresSignalNodeSetParams(CUgraphNode hNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *nodeParams) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphExternalSemaphoresSignalNodeSetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExternalSemaphoresSignalNodeSetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExternalSemaphoresSignalNodeSetParams = (CUresult (*)(CUgraphNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphExternalSemaphoresSignalNodeSetParams");
			fprintf(stderr, "cuGraphExternalSemaphoresSignalNodeSetParams:%p\n", original_cuGraphExternalSemaphoresSignalNodeSetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExternalSemaphoresSignalNodeSetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExternalSemaphoresSignalNodeSetParams(hNode, nodeParams);
		return retval;
	}
}

