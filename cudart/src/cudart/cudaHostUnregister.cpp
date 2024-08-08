
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaHostUnregister)(void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaHostUnregister(void *ptr) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaHostUnregister)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaHostUnregister = (cudaError_t (*)(void *)) dlsym(libcudart_handle, "cudaHostUnregister");
			fprintf(stderr, "cudaHostUnregister:%p\n", wrapper_cudaHostUnregister);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaHostUnregister():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaHostUnregister(ptr);
		return retval;
	}
}

