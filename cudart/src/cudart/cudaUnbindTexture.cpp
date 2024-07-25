
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaUnbindTexture)(const struct textureReference *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaUnbindTexture(const struct textureReference *texref) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaUnbindTexture)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaUnbindTexture = (cudaError_t (*)(const struct textureReference *)) dlsym(libcudart_handle, "cudaUnbindTexture");
			fprintf(stderr, "cudaUnbindTexture:%p\n", wrapper_cudaUnbindTexture);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaUnbindTexture():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaUnbindTexture(texref);
		return retval;
	}
}

