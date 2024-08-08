#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphKernelNodeGetParams)(CUgraphNode, CUDA_KERNEL_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphKernelNodeGetParams(CUgraphNode hNode, CUDA_KERNEL_NODE_PARAMS *nodeParams) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphKernelNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphKernelNodeGetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphKernelNodeGetParams = (CUresult (*)(CUgraphNode, CUDA_KERNEL_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphKernelNodeGetParams");
			fprintf(stderr, "cuGraphKernelNodeGetParams:%p\n", original_cuGraphKernelNodeGetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphKernelNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphKernelNodeGetParams(hNode, nodeParams);
		return retval;
	}
}

