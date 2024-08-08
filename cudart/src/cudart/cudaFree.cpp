
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaFree)(void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaFree(void *devPtr) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaFree)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaFree = (cudaError_t (*)(void *)) dlsym(libcudart_handle, "cudaFree");
			fprintf(stderr, "cudaFree:%p\n", wrapper_cudaFree);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaFree():%s\n", __dlerror);
			fflush(stderr);
		}
		fprintf(stderr,"calling wrapper_cudaFree() !\n");
		cudaError_t retval = wrapper_cudaFree(devPtr);
		return retval;
	}
}

