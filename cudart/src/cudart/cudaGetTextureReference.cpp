
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetTextureReference)(const struct textureReference **, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetTextureReference(const struct textureReference **texref, const void *symbol) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetTextureReference)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetTextureReference = (cudaError_t (*)(const struct textureReference **, const void *)) dlsym(libcudart_handle, "cudaGetTextureReference");
			fprintf(stderr, "cudaGetTextureReference:%p\n", wrapper_cudaGetTextureReference);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetTextureReference():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetTextureReference(texref, symbol);
		return retval;
	}
}

