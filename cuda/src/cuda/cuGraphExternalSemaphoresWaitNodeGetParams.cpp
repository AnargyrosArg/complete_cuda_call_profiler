#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExternalSemaphoresWaitNodeGetParams)(CUgraphNode, CUDA_EXT_SEM_WAIT_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExternalSemaphoresWaitNodeGetParams(CUgraphNode hNode, CUDA_EXT_SEM_WAIT_NODE_PARAMS *params_out) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExternalSemaphoresWaitNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExternalSemaphoresWaitNodeGetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExternalSemaphoresWaitNodeGetParams = (CUresult (*)(CUgraphNode, CUDA_EXT_SEM_WAIT_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphExternalSemaphoresWaitNodeGetParams");
			fprintf(stderr, "cuGraphExternalSemaphoresWaitNodeGetParams:%p\n", original_cuGraphExternalSemaphoresWaitNodeGetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExternalSemaphoresWaitNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExternalSemaphoresWaitNodeGetParams(hNode, params_out);
		return retval;
	}
}

