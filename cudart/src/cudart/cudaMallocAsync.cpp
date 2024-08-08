
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMallocAsync)(void **, size_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMallocAsync(void **devPtr, size_t size, cudaStream_t hStream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMallocAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMallocAsync = (cudaError_t (*)(void **, size_t, cudaStream_t)) dlsym(libcudart_handle, "cudaMallocAsync");
			fprintf(stderr, "cudaMallocAsync:%p\n", wrapper_cudaMallocAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMallocAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMallocAsync(devPtr, size, hStream);
		return retval;
	}
}

