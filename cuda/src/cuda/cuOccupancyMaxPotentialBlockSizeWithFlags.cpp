#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuOccupancyMaxPotentialBlockSizeWithFlags)(int *, int *, CUfunction, CUoccupancyB2DSize, size_t, int, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuOccupancyMaxPotentialBlockSizeWithFlags(int *minGridSize, int *blockSize, CUfunction func, CUoccupancyB2DSize blockSizeToDynamicSMemSize, size_t dynamicSMemSize, int blockSizeLimit, unsigned int flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuOccupancyMaxPotentialBlockSizeWithFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuOccupancyMaxPotentialBlockSizeWithFlags)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuOccupancyMaxPotentialBlockSizeWithFlags = (CUresult (*)(int *, int *, CUfunction, CUoccupancyB2DSize, size_t, int, unsigned int)) __libc_dlsym(libcuda_handle, "cuOccupancyMaxPotentialBlockSizeWithFlags");
			fprintf(stderr, "cuOccupancyMaxPotentialBlockSizeWithFlags:%p\n", original_cuOccupancyMaxPotentialBlockSizeWithFlags);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuOccupancyMaxPotentialBlockSizeWithFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuOccupancyMaxPotentialBlockSizeWithFlags(minGridSize, blockSize, func, blockSizeToDynamicSMemSize, dynamicSMemSize, blockSizeLimit, flags);
		return retval;
	}
}

