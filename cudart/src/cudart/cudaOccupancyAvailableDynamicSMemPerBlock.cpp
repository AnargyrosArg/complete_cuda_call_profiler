
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaOccupancyAvailableDynamicSMemPerBlock)(size_t *, const void *, int, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaOccupancyAvailableDynamicSMemPerBlock(size_t *dynamicSmemSize, const void *func, int numBlocks, int blockSize) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaOccupancyAvailableDynamicSMemPerBlock)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaOccupancyAvailableDynamicSMemPerBlock = (cudaError_t (*)(size_t *, const void *, int, int)) dlsym(libcudart_handle, "cudaOccupancyAvailableDynamicSMemPerBlock");
			fprintf(stderr, "cudaOccupancyAvailableDynamicSMemPerBlock:%p\n", wrapper_cudaOccupancyAvailableDynamicSMemPerBlock);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaOccupancyAvailableDynamicSMemPerBlock():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaOccupancyAvailableDynamicSMemPerBlock(dynamicSmemSize, func, numBlocks, blockSize);
		return retval;
	}
}

