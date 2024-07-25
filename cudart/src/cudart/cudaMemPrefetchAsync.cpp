
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemPrefetchAsync)(const void *, size_t, int, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemPrefetchAsync(const void *devPtr, size_t count, int dstDevice, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemPrefetchAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemPrefetchAsync = (cudaError_t (*)(const void *, size_t, int, cudaStream_t)) dlsym(libcudart_handle, "cudaMemPrefetchAsync");
			fprintf(stderr, "cudaMemPrefetchAsync:%p\n", wrapper_cudaMemPrefetchAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemPrefetchAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemPrefetchAsync(devPtr, count, dstDevice, stream);
		return retval;
	}
}

