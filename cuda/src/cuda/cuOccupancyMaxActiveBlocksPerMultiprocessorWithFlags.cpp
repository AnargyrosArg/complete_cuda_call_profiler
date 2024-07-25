#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)(int *, CUfunction, int, size_t, unsigned int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize, unsigned int flags) {
		fprintf(stderr, "%s()\n", __func__);
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcuda_handle == NULL){
			libcuda_handle =__libc_dlopen_mode("libcuda.so.1", RTLD_LAZY);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags = (CUresult (*)(int *, CUfunction, int, size_t, unsigned int)) __libc_dlsym(libcuda_handle, "cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags");
			fprintf(stderr, "cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags:%p\n", original_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(numBlocks, func, blockSize, dynamicSMemSize, flags);
		return retval;
	}
}

