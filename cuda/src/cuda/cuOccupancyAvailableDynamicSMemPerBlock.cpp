#include <cuda.h>
#include <dlfcn.h>
#include <iostream>
CUresult (*original_cuOccupancyAvailableDynamicSMemPerBlock)(size_t *, CUfunction, int, int);
extern void* libcuda_handle;
extern "C" {
	void* __libc_dlsym (void *, const char *);
	void* __libc_dlopen_mode (const char*, int);
}
extern "C"
{
	CUresult cuOccupancyAvailableDynamicSMemPerBlock(size_t *dynamicSmemSize, CUfunction func, int numBlocks, int blockSize) {
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
				fprintf(stderr, "dlsym error for fntion cuOccupancyAvailableDynamicSMemPerBlock():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		if (!original_cuOccupancyAvailableDynamicSMemPerBlock)
		{
			//fetch the original fntion addr using __libc_dlsym
			original_cuOccupancyAvailableDynamicSMemPerBlock = (CUresult (*)(size_t *, CUfunction, int, int)) __libc_dlsym(libcuda_handle, "cuOccupancyAvailableDynamicSMemPerBlock");
			fprintf(stderr, "cuOccupancyAvailableDynamicSMemPerBlock:%p\n", original_cuOccupancyAvailableDynamicSMemPerBlock);
			__dlerror = dlerror();
			if(__dlerror){
				fprintf(stderr, "dlsym error for fntion cuOccupancyAvailableDynamicSMemPerBlock():%s\n", __dlerror);
				fflush(stderr);
			}
		}
		CUresult retval = original_cuOccupancyAvailableDynamicSMemPerBlock(dynamicSmemSize, func, numBlocks, blockSize);
		return retval;
	}
}

