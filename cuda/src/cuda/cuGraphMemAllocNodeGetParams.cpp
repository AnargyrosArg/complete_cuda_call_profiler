#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphMemAllocNodeGetParams)(CUgraphNode, CUDA_MEM_ALLOC_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphMemAllocNodeGetParams(CUgraphNode hNode, CUDA_MEM_ALLOC_NODE_PARAMS *params_out) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphMemAllocNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphMemAllocNodeGetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphMemAllocNodeGetParams = (CUresult (*)(CUgraphNode, CUDA_MEM_ALLOC_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphMemAllocNodeGetParams");
			fprintf(stderr, "cuGraphMemAllocNodeGetParams:%p\n", original_cuGraphMemAllocNodeGetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphMemAllocNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphMemAllocNodeGetParams(hNode, params_out);
		return retval;
	}
}

