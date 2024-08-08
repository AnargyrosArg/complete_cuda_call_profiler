
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaEventCreateWithFlags)(cudaEvent_t *, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaEventCreateWithFlags(cudaEvent_t *event, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaEventCreateWithFlags)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaEventCreateWithFlags = (cudaError_t (*)(cudaEvent_t *, unsigned int)) dlsym(libcudart_handle, "cudaEventCreateWithFlags");
			fprintf(stderr, "cudaEventCreateWithFlags:%p\n", wrapper_cudaEventCreateWithFlags);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaEventCreateWithFlags():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaEventCreateWithFlags(event, flags);
		return retval;
	}
}

