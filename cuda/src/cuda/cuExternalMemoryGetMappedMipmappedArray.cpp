#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuExternalMemoryGetMappedMipmappedArray)(CUmipmappedArray *, CUexternalMemory, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuExternalMemoryGetMappedMipmappedArray(CUmipmappedArray *mipmap, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC *mipmapDesc) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuExternalMemoryGetMappedMipmappedArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuExternalMemoryGetMappedMipmappedArray)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuExternalMemoryGetMappedMipmappedArray = (CUresult (*)(CUmipmappedArray *, CUexternalMemory, const CUDA_EXTERNAL_MEMORY_MIPMAPPED_ARRAY_DESC *)) __libc_dlsym(libcuda_handle, "cuExternalMemoryGetMappedMipmappedArray");
			fprintf(stderr, "cuExternalMemoryGetMappedMipmappedArray:%p\n", original_cuExternalMemoryGetMappedMipmappedArray);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuExternalMemoryGetMappedMipmappedArray():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuExternalMemoryGetMappedMipmappedArray(mipmap, extMem, mipmapDesc);
		return retval;
	}
}

