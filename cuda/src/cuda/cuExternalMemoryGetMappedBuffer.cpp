#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuExternalMemoryGetMappedBuffer)(CUdeviceptr *, CUexternalMemory, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC *);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuExternalMemoryGetMappedBuffer(CUdeviceptr *devPtr, CUexternalMemory extMem, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC *bufferDesc) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuExternalMemoryGetMappedBuffer():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuExternalMemoryGetMappedBuffer)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuExternalMemoryGetMappedBuffer = (CUresult (*)(CUdeviceptr *, CUexternalMemory, const CUDA_EXTERNAL_MEMORY_BUFFER_DESC *)) __libc_dlsym(libcuda_handle, "cuExternalMemoryGetMappedBuffer");
			fprintf(stderr, "cuExternalMemoryGetMappedBuffer:%p\n", original_cuExternalMemoryGetMappedBuffer);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuExternalMemoryGetMappedBuffer():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuExternalMemoryGetMappedBuffer(devPtr, extMem, bufferDesc);
		return retval;
	}
}

