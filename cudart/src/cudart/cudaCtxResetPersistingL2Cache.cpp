
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaCtxResetPersistingL2Cache)();
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaCtxResetPersistingL2Cache() {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaCtxResetPersistingL2Cache)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaCtxResetPersistingL2Cache = (cudaError_t (*)()) dlsym(libcudart_handle, "cudaCtxResetPersistingL2Cache");
			fprintf(stderr, "cudaCtxResetPersistingL2Cache:%p\n", wrapper_cudaCtxResetPersistingL2Cache);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaCtxResetPersistingL2Cache():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaCtxResetPersistingL2Cache();
		return retval;
	}
}

