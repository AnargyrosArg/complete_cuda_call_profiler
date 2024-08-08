
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemsetAsync)(void *, int, size_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemsetAsync(void *devPtr, int value, size_t count, cudaStream_t stream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemsetAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemsetAsync = (cudaError_t (*)(void *, int, size_t, cudaStream_t)) dlsym(libcudart_handle, "cudaMemsetAsync");
			fprintf(stderr, "cudaMemsetAsync:%p\n", wrapper_cudaMemsetAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemsetAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemsetAsync(devPtr, value, count, stream);
		return retval;
	}
}

