
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaFreeAsync)(void *, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaFreeAsync(void *devPtr, cudaStream_t hStream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaFreeAsync)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaFreeAsync = (cudaError_t (*)(void *, cudaStream_t)) dlsym(libcudart_handle, "cudaFreeAsync");
			fprintf(stderr, "cudaFreeAsync:%p\n", wrapper_cudaFreeAsync);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaFreeAsync():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaFreeAsync(devPtr, hStream);
		return retval;
	}
}

