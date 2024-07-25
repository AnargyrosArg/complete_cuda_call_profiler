#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuDeviceGetTexture1DLinearMaxWidth)(size_t *, CUarray_format, unsigned, CUdevice);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuDeviceGetTexture1DLinearMaxWidth(size_t *maxWidthInElements, CUarray_format format, unsigned numChannels, CUdevice dev) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetTexture1DLinearMaxWidth():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuDeviceGetTexture1DLinearMaxWidth)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuDeviceGetTexture1DLinearMaxWidth = (CUresult (*)(size_t *, CUarray_format, unsigned, CUdevice)) __libc_dlsym(libcuda_handle, "cuDeviceGetTexture1DLinearMaxWidth");
			fprintf(stderr, "cuDeviceGetTexture1DLinearMaxWidth:%p\n", original_cuDeviceGetTexture1DLinearMaxWidth);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuDeviceGetTexture1DLinearMaxWidth():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuDeviceGetTexture1DLinearMaxWidth(maxWidthInElements, format, numChannels, dev);
		return retval;
	}
}

