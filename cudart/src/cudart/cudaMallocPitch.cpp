
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMallocPitch)(void **, size_t *, size_t, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMallocPitch(void **devPtr, size_t *pitch, size_t width, size_t height) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMallocPitch)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMallocPitch = (cudaError_t (*)(void **, size_t *, size_t, size_t)) dlsym(libcudart_handle, "cudaMallocPitch");
			fprintf(stderr, "cudaMallocPitch:%p\n", wrapper_cudaMallocPitch);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMallocPitch():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMallocPitch(devPtr, pitch, width, height);
		return retval;
	}
}

