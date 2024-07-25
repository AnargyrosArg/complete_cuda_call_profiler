#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuTexObjectGetTextureDesc)(CUDA_TEXTURE_DESC *, CUtexObject);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuTexObjectGetTextureDesc(CUDA_TEXTURE_DESC *pTexDesc, CUtexObject texObject) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexObjectGetTextureDesc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuTexObjectGetTextureDesc)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuTexObjectGetTextureDesc = (CUresult (*)(CUDA_TEXTURE_DESC *, CUtexObject)) __libc_dlsym(libcuda_handle, "cuTexObjectGetTextureDesc");
			fprintf(stderr, "cuTexObjectGetTextureDesc:%p\n", original_cuTexObjectGetTextureDesc);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuTexObjectGetTextureDesc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuTexObjectGetTextureDesc(pTexDesc, texObject);
		return retval;
	}
}

