#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuMemHostAlloc)(void **, size_t, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuMemHostAlloc(void **pp, size_t bytesize, unsigned int Flags) {
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
				fprintf(stderr, "dlsym error for fntion cuMemHostAlloc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuMemHostAlloc)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuMemHostAlloc = (CUresult (*)(void **, size_t, unsigned int)) __libc_dlsym(libcuda_handle, "cuMemHostAlloc");
			fprintf(stderr, "cuMemHostAlloc:%p\n", original_cuMemHostAlloc);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuMemHostAlloc():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuMemHostAlloc(pp, bytesize, Flags);
		return retval;
	}
}

