
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaBindTextureToArray)(const struct textureReference *, cudaArray_const_t, const struct cudaChannelFormatDesc *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaBindTextureToArray(const struct textureReference *texref, cudaArray_const_t array, const struct cudaChannelFormatDesc *desc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaBindTextureToArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaBindTextureToArray = (cudaError_t (*)(const struct textureReference *, cudaArray_const_t, const struct cudaChannelFormatDesc *)) dlsym(libcudart_handle, "cudaBindTextureToArray");
			fprintf(stderr, "cudaBindTextureToArray:%p\n", wrapper_cudaBindTextureToArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaBindTextureToArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaBindTextureToArray(texref, array, desc);
		return retval;
	}
}

