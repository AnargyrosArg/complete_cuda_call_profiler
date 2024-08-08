
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaWaitExternalSemaphoresAsync_v2)(const cudaExternalSemaphore_t *, const struct cudaExternalSemaphoreWaitParams *, unsigned int, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaWaitExternalSemaphoresAsync_v2(const cudaExternalSemaphore_t *extSemArray, const struct cudaExternalSemaphoreWaitParams *paramsArray, unsigned int numExtSems, cudaStream_t stream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaWaitExternalSemaphoresAsync_v2)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaWaitExternalSemaphoresAsync_v2 = (cudaError_t (*)(const cudaExternalSemaphore_t *, const struct cudaExternalSemaphoreWaitParams *, unsigned int, cudaStream_t)) dlsym(libcudart_handle, "cudaWaitExternalSemaphoresAsync_v2");
			fprintf(stderr, "cudaWaitExternalSemaphoresAsync_v2:%p\n", wrapper_cudaWaitExternalSemaphoresAsync_v2);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaWaitExternalSemaphoresAsync_v2():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaWaitExternalSemaphoresAsync_v2(extSemArray, paramsArray, numExtSems, stream);
		return retval;
	}
}

