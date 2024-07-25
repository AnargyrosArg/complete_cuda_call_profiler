#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphMemcpyNodeGetParams)(CUgraphNode, CUDA_MEMCPY3D *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphMemcpyNodeGetParams(CUgraphNode hNode, CUDA_MEMCPY3D *nodeParams) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphMemcpyNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphMemcpyNodeGetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphMemcpyNodeGetParams = (CUresult (*)(CUgraphNode, CUDA_MEMCPY3D *)) __libc_dlsym(libcuda_handle, "cuGraphMemcpyNodeGetParams");
			fprintf(stderr, "cuGraphMemcpyNodeGetParams:%p\n", original_cuGraphMemcpyNodeGetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphMemcpyNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphMemcpyNodeGetParams(hNode, nodeParams);
		return retval;
	}
}

