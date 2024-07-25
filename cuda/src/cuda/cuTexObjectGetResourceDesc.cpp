#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexObjectGetResourceDesc)(CUDA_RESOURCE_DESC *, CUtexObject);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexObjectGetResourceDesc(CUDA_RESOURCE_DESC *pResDesc, CUtexObject texObject) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexObjectGetResourceDesc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexObjectGetResourceDesc)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexObjectGetResourceDesc = (CUresult (*)(CUDA_RESOURCE_DESC *, CUtexObject)) __libc_dlsym(libcuda_handle, "cuTexObjectGetResourceDesc");
			fprintf(stderr, "cuTexObjectGetResourceDesc:%p\n", original_cuTexObjectGetResourceDesc);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexObjectGetResourceDesc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexObjectGetResourceDesc(pResDesc, texObject);
		return retval;
	}
}

