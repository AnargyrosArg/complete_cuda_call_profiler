
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaEventElapsedTime)(float *, cudaEvent_t, cudaEvent_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaEventElapsedTime(float *ms, cudaEvent_t start, cudaEvent_t end) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaEventElapsedTime)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaEventElapsedTime = (cudaError_t (*)(float *, cudaEvent_t, cudaEvent_t)) dlsym(libcudart_handle, "cudaEventElapsedTime");
			fprintf(stderr, "cudaEventElapsedTime:%p\n", wrapper_cudaEventElapsedTime);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaEventElapsedTime():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaEventElapsedTime(ms, start, end);
		return retval;
	}
}

