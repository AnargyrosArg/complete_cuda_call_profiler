#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExternalSemaphoresWaitNodeSetParams)(CUgraphNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExternalSemaphoresWaitNodeSetParams(CUgraphNode hNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS *nodeParams) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphExternalSemaphoresWaitNodeSetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExternalSemaphoresWaitNodeSetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExternalSemaphoresWaitNodeSetParams = (CUresult (*)(CUgraphNode, const CUDA_EXT_SEM_WAIT_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphExternalSemaphoresWaitNodeSetParams");
			fprintf(stderr, "cuGraphExternalSemaphoresWaitNodeSetParams:%p\n", original_cuGraphExternalSemaphoresWaitNodeSetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExternalSemaphoresWaitNodeSetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExternalSemaphoresWaitNodeSetParams(hNode, nodeParams);
		return retval;
	}
}

