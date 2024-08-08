#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuOccupancyMaxPotentialBlockSize)(int *, int *, CUfunction, CUoccupancyB2DSize, size_t, int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuOccupancyMaxPotentialBlockSize(int *minGridSize, int *blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit) {
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
				fprintf(stderr, "dlsym error for fntion cuOccupancyMaxPotentialBlockSize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuOccupancyMaxPotentialBlockSize)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuOccupancyMaxPotentialBlockSize = (CUresult (*)(int *, int *, CUfunction, CUoccupancyB2DSize, size_t, int)) __libc_dlsym(libcuda_handle, "cuOccupancyMaxPotentialBlockSize");
			fprintf(stderr, "cuOccupancyMaxPotentialBlockSize:%p\n", original_cuOccupancyMaxPotentialBlockSize);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuOccupancyMaxPotentialBlockSize():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuOccupancyMaxPotentialBlockSize(minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit);
		return retval;
	}
}

