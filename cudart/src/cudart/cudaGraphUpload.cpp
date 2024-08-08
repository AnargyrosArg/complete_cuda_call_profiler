
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphUpload)(cudaGraphExec_t, cudaStream_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphUpload(cudaGraphExec_t graphExec, cudaStream_t stream) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphUpload)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphUpload = (cudaError_t (*)(cudaGraphExec_t, cudaStream_t)) dlsym(libcudart_handle, "cudaGraphUpload");
			fprintf(stderr, "cudaGraphUpload:%p\n", wrapper_cudaGraphUpload);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphUpload():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphUpload(graphExec, stream);
		return retval;
	}
}

