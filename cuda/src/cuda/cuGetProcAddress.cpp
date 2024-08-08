#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuGetProcAddress)(const char *, void **, int, cuuint64_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuGetProcAddress(const char *symbol, void **pfn, int cudaVersion, cuuint64_t flags) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		//Returning an error here causes the calling cudart function to fallback to dlsym symbol resolution
		//allowing us to intercept.
		return CUDA_ERROR_NOT_FOUND;
	}
}

