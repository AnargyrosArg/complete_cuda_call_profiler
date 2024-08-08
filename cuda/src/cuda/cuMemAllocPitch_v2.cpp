#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemAllocPitch_v2)(CUdeviceptr *, size_t *, size_t, size_t, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemAllocPitch_v2(CUdeviceptr *dptr, size_t *pPitch, size_t WidthInBytes, size_t Height, unsigned int ElementSizeBytes) {
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
				fprintf(stderr, "dlsym error for fntion cuMemAllocPitch_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemAllocPitch_v2)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemAllocPitch_v2 = (CUresult (*)(CUdeviceptr *, size_t *, size_t, size_t, unsigned int)) __libc_dlsym(libcuda_handle, "cuMemAllocPitch_v2");
			fprintf(stderr, "cuMemAllocPitch_v2:%p\n", original_cuMemAllocPitch_v2);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemAllocPitch_v2():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemAllocPitch_v2(dptr, pPitch, WidthInBytes, Height, ElementSizeBytes);
		return retval;
	}
}

