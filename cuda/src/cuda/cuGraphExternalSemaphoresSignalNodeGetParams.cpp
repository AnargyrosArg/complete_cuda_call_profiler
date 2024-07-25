#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExternalSemaphoresSignalNodeGetParams)(CUgraphNode, CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExternalSemaphoresSignalNodeGetParams(CUgraphNode hNode, CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *params_out) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExternalSemaphoresSignalNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExternalSemaphoresSignalNodeGetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExternalSemaphoresSignalNodeGetParams = (CUresult (*)(CUgraphNode, CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphExternalSemaphoresSignalNodeGetParams");
			fprintf(stderr, "cuGraphExternalSemaphoresSignalNodeGetParams:%p\n", original_cuGraphExternalSemaphoresSignalNodeGetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExternalSemaphoresSignalNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExternalSemaphoresSignalNodeGetParams(hNode, params_out);
		return retval;
	}
}

