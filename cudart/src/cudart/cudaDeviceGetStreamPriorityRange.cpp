
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDeviceGetStreamPriorityRange)(int *, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDeviceGetStreamPriorityRange(int *leastPriority, int *greatestPriority) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDeviceGetStreamPriorityRange)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDeviceGetStreamPriorityRange = (cudaError_t (*)(int *, int *)) dlsym(libcudart_handle, "cudaDeviceGetStreamPriorityRange");
			fprintf(stderr, "cudaDeviceGetStreamPriorityRange:%p\n", wrapper_cudaDeviceGetStreamPriorityRange);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDeviceGetStreamPriorityRange():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDeviceGetStreamPriorityRange(leastPriority, greatestPriority);
		return retval;
	}
}

