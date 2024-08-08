#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexObjectGetResourceViewDesc)(CUDA_RESOURCE_VIEW_DESC *, CUtexObject);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexObjectGetResourceViewDesc(CUDA_RESOURCE_VIEW_DESC *pResViewDesc, CUtexObject texObject) {
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
				fprintf(stderr, "dlsym error for fntion cuTexObjectGetResourceViewDesc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexObjectGetResourceViewDesc)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexObjectGetResourceViewDesc = (CUresult (*)(CUDA_RESOURCE_VIEW_DESC *, CUtexObject)) __libc_dlsym(libcuda_handle, "cuTexObjectGetResourceViewDesc");
			fprintf(stderr, "cuTexObjectGetResourceViewDesc:%p\n", original_cuTexObjectGetResourceViewDesc);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexObjectGetResourceViewDesc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexObjectGetResourceViewDesc(pResViewDesc, texObject);
		return retval;
	}
}

