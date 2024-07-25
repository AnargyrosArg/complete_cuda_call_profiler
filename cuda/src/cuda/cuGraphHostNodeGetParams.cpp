#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphHostNodeGetParams)(CUgraphNode, CUDA_HOST_NODE_PARAMS *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphHostNodeGetParams(CUgraphNode hNode, CUDA_HOST_NODE_PARAMS *nodeParams) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphHostNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphHostNodeGetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphHostNodeGetParams = (CUresult (*)(CUgraphNode, CUDA_HOST_NODE_PARAMS *)) __libc_dlsym(libcuda_handle, "cuGraphHostNodeGetParams");
			fprintf(stderr, "cuGraphHostNodeGetParams:%p\n", original_cuGraphHostNodeGetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphHostNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphHostNodeGetParams(hNode, nodeParams);
		return retval;
	}
}

