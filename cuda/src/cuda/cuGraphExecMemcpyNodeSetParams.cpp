#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphExecMemcpyNodeSetParams)(CUgraphExec, CUgraphNode, const CUDA_MEMCPY3D *, CUcontext);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphExecMemcpyNodeSetParams(CUgraphExec hGraphExec, CUgraphNode hNode, const CUDA_MEMCPY3D *copyParams, CUcontext ctx) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphExecMemcpyNodeSetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphExecMemcpyNodeSetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphExecMemcpyNodeSetParams = (CUresult (*)(CUgraphExec, CUgraphNode, const CUDA_MEMCPY3D *, CUcontext)) __libc_dlsym(libcuda_handle, "cuGraphExecMemcpyNodeSetParams");
			fprintf(stderr, "cuGraphExecMemcpyNodeSetParams:%p\n", original_cuGraphExecMemcpyNodeSetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphExecMemcpyNodeSetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphExecMemcpyNodeSetParams(hGraphExec, hNode, copyParams, ctx);
		return retval;
	}
}

