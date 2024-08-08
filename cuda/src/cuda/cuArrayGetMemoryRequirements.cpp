#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuArrayGetMemoryRequirements)(CUDA_ARRAY_MEMORY_REQUIREMENTS *, CUarray, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuArrayGetMemoryRequirements(CUDA_ARRAY_MEMORY_REQUIREMENTS *memoryRequirements, CUarray array, CUdevice device) {
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
				fprintf(stderr, "dlsym error for fntion cuArrayGetMemoryRequirements():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuArrayGetMemoryRequirements)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuArrayGetMemoryRequirements = (CUresult (*)(CUDA_ARRAY_MEMORY_REQUIREMENTS *, CUarray, CUdevice)) __libc_dlsym(libcuda_handle, "cuArrayGetMemoryRequirements");
			fprintf(stderr, "cuArrayGetMemoryRequirements:%p\n", original_cuArrayGetMemoryRequirements);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuArrayGetMemoryRequirements():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuArrayGetMemoryRequirements(memoryRequirements, array, device);
		return retval;
	}
}

