#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphKernelNodeSetAttribute)(CUgraphNode, CUkernelNodeAttrID, const CUkernelNodeAttrValue *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphKernelNodeSetAttribute(CUgraphNode hNode, CUkernelNodeAttrID attr, const CUkernelNodeAttrValue *value) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphKernelNodeSetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphKernelNodeSetAttribute)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphKernelNodeSetAttribute = (CUresult (*)(CUgraphNode, CUkernelNodeAttrID, const CUkernelNodeAttrValue *)) __libc_dlsym(libcuda_handle, "cuGraphKernelNodeSetAttribute");
			fprintf(stderr, "cuGraphKernelNodeSetAttribute:%p\n", original_cuGraphKernelNodeSetAttribute);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphKernelNodeSetAttribute():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphKernelNodeSetAttribute(hNode, attr, value);
		return retval;
	}
}

