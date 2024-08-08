#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuLaunchGridAsync)(CUfunction, int, int, CUstream);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuLaunchGridAsync(CUfunction f, int grid_width, int grid_height, CUstream hStream) {
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
				fprintf(stderr, "dlsym error for fntion cuLaunchGridAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuLaunchGridAsync)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuLaunchGridAsync = (CUresult (*)(CUfunction, int, int, CUstream)) __libc_dlsym(libcuda_handle, "cuLaunchGridAsync");
			fprintf(stderr, "cuLaunchGridAsync:%p\n", original_cuLaunchGridAsync);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLaunchGridAsync():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuLaunchGridAsync(f, grid_width, grid_height, hStream);
		return retval;
	}
}

