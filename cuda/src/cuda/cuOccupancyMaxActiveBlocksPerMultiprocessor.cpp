#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuOccupancyMaxActiveBlocksPerMultiprocessor)(int *, CUfunction, int, size_t);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuOccupancyMaxActiveBlocksPerMultiprocessor(int *numBlocks, CUfunction func, int blockSize, size_t dynamicSMemSize) {
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
				fprintf(stderr, "dlsym error for fntion cuOccupancyMaxActiveBlocksPerMultiprocessor():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuOccupancyMaxActiveBlocksPerMultiprocessor)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuOccupancyMaxActiveBlocksPerMultiprocessor = (CUresult (*)(int *, CUfunction, int, size_t)) __libc_dlsym(libcuda_handle, "cuOccupancyMaxActiveBlocksPerMultiprocessor");
			fprintf(stderr, "cuOccupancyMaxActiveBlocksPerMultiprocessor:%p\n", original_cuOccupancyMaxActiveBlocksPerMultiprocessor);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuOccupancyMaxActiveBlocksPerMultiprocessor():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuOccupancyMaxActiveBlocksPerMultiprocessor(numBlocks, func, blockSize, dynamicSMemSize);
		return retval;
	}
}

