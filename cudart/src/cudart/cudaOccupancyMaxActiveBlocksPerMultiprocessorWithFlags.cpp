
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)(int *, const void *, int, size_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int *numBlocks, const void *func, int blockSize, size_t dynamicSMemSize, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags = (cudaError_t (*)(int *, const void *, int, size_t, unsigned int)) dlsym(libcudart_handle, "cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags");
			fprintf(stderr, "cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags:%p\n", wrapper_cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(numBlocks, func, blockSize, dynamicSMemSize, flags);
		return retval;
	}
}

