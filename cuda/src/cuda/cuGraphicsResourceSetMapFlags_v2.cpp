#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGraphicsResourceSetMapFlags_v2)(CUgraphicsResource, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGraphicsResourceSetMapFlags_v2(CUgraphicsResource resource, unsigned int flags) {
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
				fprintf(stderr, "dlsym error for fntion cuGraphicsResourceSetMapFlags_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuGraphicsResourceSetMapFlags_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuGraphicsResourceSetMapFlags_v2 = (CUresult (*)(CUgraphicsResource, unsigned int)) __libc_dlsym(libcuda_handle, "cuGraphicsResourceSetMapFlags_v2");
			fprintf(stderr, "cuGraphicsResourceSetMapFlags_v2:%p\n", original_cuGraphicsResourceSetMapFlags_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuGraphicsResourceSetMapFlags_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuGraphicsResourceSetMapFlags_v2(resource, flags);
		return retval;
	}
}

