#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphKernelNodeCopyAttributes)(CUgraphNode, CUgraphNode);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphKernelNodeCopyAttributes(CUgraphNode dst, CUgraphNode src) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphKernelNodeCopyAttributes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphKernelNodeCopyAttributes)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphKernelNodeCopyAttributes = (CUresult (*)(CUgraphNode, CUgraphNode)) __libc_dlsym(libcuda_handle, "cuGraphKernelNodeCopyAttributes");
			fprintf(stderr, "cuGraphKernelNodeCopyAttributes:%p\n", original_cuGraphKernelNodeCopyAttributes);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphKernelNodeCopyAttributes():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphKernelNodeCopyAttributes(dst, src);
		return retval;
	}
}

