
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaSetDoubleForHost)(double *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaSetDoubleForHost(double *d) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaSetDoubleForHost)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaSetDoubleForHost = (cudaError_t (*)(double *)) dlsym(libcudart_handle, "cudaSetDoubleForHost");
			fprintf(stderr, "cudaSetDoubleForHost:%p\n", wrapper_cudaSetDoubleForHost);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaSetDoubleForHost():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaSetDoubleForHost(d);
		return retval;
	}
}

