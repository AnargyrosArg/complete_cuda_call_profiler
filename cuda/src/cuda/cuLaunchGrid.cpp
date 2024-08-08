#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuLaunchGrid)(CUfunction, int, int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuLaunchGrid(CUfunction f, int grid_width, int grid_height) {
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
				fprintf(stderr, "dlsym error for fntion cuLaunchGrid():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuLaunchGrid)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuLaunchGrid = (CUresult (*)(CUfunction, int, int)) __libc_dlsym(libcuda_handle, "cuLaunchGrid");
			fprintf(stderr, "cuLaunchGrid:%p\n", original_cuLaunchGrid);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuLaunchGrid():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuLaunchGrid(f, grid_width, grid_height);
		return retval;
	}
}

