
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaIpcOpenEventHandle)(cudaEvent_t *, cudaIpcEventHandle_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaIpcOpenEventHandle(cudaEvent_t *event, cudaIpcEventHandle_t handle) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaIpcOpenEventHandle)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaIpcOpenEventHandle = (cudaError_t (*)(cudaEvent_t *, cudaIpcEventHandle_t)) dlsym(libcudart_handle, "cudaIpcOpenEventHandle");
			fprintf(stderr, "cudaIpcOpenEventHandle:%p\n", wrapper_cudaIpcOpenEventHandle);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaIpcOpenEventHandle():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaIpcOpenEventHandle(event, handle);
		return retval;
	}
}

