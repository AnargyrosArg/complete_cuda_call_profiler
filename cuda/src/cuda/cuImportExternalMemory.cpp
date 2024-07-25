#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuImportExternalMemory)(CUexternalMemory *, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuImportExternalMemory(CUexternalMemory *extMem_out, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC *memHandleDesc) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuImportExternalMemory():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuImportExternalMemory)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuImportExternalMemory = (CUresult (*)(CUexternalMemory *, const CUDA_EXTERNAL_MEMORY_HANDLE_DESC *)) __libc_dlsym(libcuda_handle, "cuImportExternalMemory");
			fprintf(stderr, "cuImportExternalMemory:%p\n", original_cuImportExternalMemory);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuImportExternalMemory():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuImportExternalMemory(extMem_out, memHandleDesc);
		return retval;
	}
}

