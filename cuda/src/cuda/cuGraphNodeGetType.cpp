#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphNodeGetType)(CUgraphNode, CUgraphNodeType *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphNodeGetType(CUgraphNode hNode, CUgraphNodeType *type) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphNodeGetType():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphNodeGetType)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphNodeGetType = (CUresult (*)(CUgraphNode, CUgraphNodeType *)) __libc_dlsym(libcuda_handle, "cuGraphNodeGetType");
			fprintf(stderr, "cuGraphNodeGetType:%p\n", original_cuGraphNodeGetType);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphNodeGetType():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphNodeGetType(hNode, type);
		return retval;
	}
}

