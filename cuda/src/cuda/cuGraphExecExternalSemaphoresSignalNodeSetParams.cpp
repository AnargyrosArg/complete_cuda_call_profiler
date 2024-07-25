#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExecExternalSemaphoresSignalNodeSetParams)(CUgraphExec, CUgraphNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExecExternalSemaphoresSignalNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *nodeParams) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExecExternalSemaphoresSignalNodeSetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExecExternalSemaphoresSignalNodeSetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExecExternalSemaphoresSignalNodeSetParams = (CUresult (*)(CUgraphExec, CUgraphNode, const CUDA_EXT_SEM_SIGNAL_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphExecExternalSemaphoresSignalNodeSetParams");
			fprintf(stderr, "cuGraphExecExternalSemaphoresSignalNodeSetParams:%p\n", original_cuGraphExecExternalSemaphoresSignalNodeSetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExecExternalSemaphoresSignalNodeSetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExecExternalSemaphoresSignalNodeSetParams(hGraphExec, hNode, nodeParams);
		return retval;
	}
}

