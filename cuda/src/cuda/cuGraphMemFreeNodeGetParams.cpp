#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphMemFreeNodeGetParams)(CUgraphNode, CUdeviceptr *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphMemFreeNodeGetParams(CUgraphNode hNode, CUdeviceptr *dptr_out) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphMemFreeNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphMemFreeNodeGetParams)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphMemFreeNodeGetParams = (CUresult (*)(CUgraphNode, CUdeviceptr *)) __libc_dlsym(libcuda_handle, "cuGraphMemFreeNodeGetParams");
			fprintf(stderr, "cuGraphMemFreeNodeGetParams:%p\n", original_cuGraphMemFreeNodeGetParams);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphMemFreeNodeGetParams():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphMemFreeNodeGetParams(hNode, dptr_out);
		return retval;
	}
}

