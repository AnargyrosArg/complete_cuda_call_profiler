
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemset2DAsync)(void *, size_t, int, size_t, size_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemset2DAsync(void *devPtr, size_t pitch, int value, size_t width, size_t height, cudaStream_t stream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemset2DAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemset2DAsync = (cudaError_t (*)(void *, size_t, int, size_t, size_t, cudaStream_t)) dlsym(libcudart_handle, "cudaMemset2DAsync");
			fprintf(stderr, "cudaMemset2DAsync:%p\n", wrapper_cudaMemset2DAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemset2DAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemset2DAsync(devPtr, pitch, value, width, height, stream);
		return retval;
	}
}

