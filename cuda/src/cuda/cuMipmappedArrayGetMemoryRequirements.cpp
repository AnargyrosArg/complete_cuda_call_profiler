#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMipmappedArrayGetMemoryRequirements)(CUDA_ARRAY_MEMORY_REQUIREMENTS *, CUmipmappedArray, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMipmappedArrayGetMemoryRequirements(CUDA_ARRAY_MEMORY_REQUIREMENTS *memoryRequirements, CUmipmappedArray mipmap, CUdevice device) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMipmappedArrayGetMemoryRequirements():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMipmappedArrayGetMemoryRequirements)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMipmappedArrayGetMemoryRequirements = (CUresult (*)(CUDA_ARRAY_MEMORY_REQUIREMENTS *, CUmipmappedArray, CUdevice)) __libc_dlsym(libcuda_handle, "cuMipmappedArrayGetMemoryRequirements");
			fprintf(stderr, "cuMipmappedArrayGetMemoryRequirements:%p\n", original_cuMipmappedArrayGetMemoryRequirements);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMipmappedArrayGetMemoryRequirements():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMipmappedArrayGetMemoryRequirements(memoryRequirements, mipmap, device);
		return retval;
	}
}

