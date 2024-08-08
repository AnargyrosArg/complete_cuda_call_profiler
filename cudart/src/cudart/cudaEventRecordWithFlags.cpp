
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaEventRecordWithFlags)(cudaEvent_t, cudaStream_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaEventRecordWithFlags(cudaEvent_t event, cudaStream_t stream, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaEventRecordWithFlags)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaEventRecordWithFlags = (cudaError_t (*)(cudaEvent_t, cudaStream_t, unsigned int)) dlsym(libcudart_handle, "cudaEventRecordWithFlags");
			fprintf(stderr, "cudaEventRecordWithFlags:%p\n", wrapper_cudaEventRecordWithFlags);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaEventRecordWithFlags():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaEventRecordWithFlags(event, stream, flags);
		return retval;
	}
}

