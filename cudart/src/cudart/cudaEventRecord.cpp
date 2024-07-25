
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaEventRecord)(cudaEvent_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaEventRecord(cudaEvent_t event, cudaStream_t stream) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaEventRecord)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaEventRecord = (cudaError_t (*)(cudaEvent_t, cudaStream_t)) dlsym(libcudart_handle, "cudaEventRecord");
			fprintf(stderr, "cudaEventRecord:%p\n", wrapper_cudaEventRecord);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaEventRecord():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaEventRecord(event, stream);
		return retval;
	}
}
