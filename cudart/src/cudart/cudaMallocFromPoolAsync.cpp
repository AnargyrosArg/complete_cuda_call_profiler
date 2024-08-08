
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMallocFromPoolAsync)(void **, size_t, cudaMemPool_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMallocFromPoolAsync(void **ptr, size_t size, cudaMemPool_t memPool, cudaStream_t stream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMallocFromPoolAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMallocFromPoolAsync = (cudaError_t (*)(void **, size_t, cudaMemPool_t, cudaStream_t)) dlsym(libcudart_handle, "cudaMallocFromPoolAsync");
			fprintf(stderr, "cudaMallocFromPoolAsync:%p\n", wrapper_cudaMallocFromPoolAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMallocFromPoolAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMallocFromPoolAsync(ptr, size, memPool, stream);
		return retval;
	}
}

