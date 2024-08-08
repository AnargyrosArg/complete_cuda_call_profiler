
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaEventQuery)(cudaEvent_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaEventQuery(cudaEvent_t event) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaEventQuery)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaEventQuery = (cudaError_t (*)(cudaEvent_t)) dlsym(libcudart_handle, "cudaEventQuery");
			fprintf(stderr, "cudaEventQuery:%p\n", wrapper_cudaEventQuery);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaEventQuery():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaEventQuery(event);
		return retval;
	}
}

