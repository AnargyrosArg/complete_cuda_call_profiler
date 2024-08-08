
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaBindTexture)(size_t *, const struct textureReference *, const void *, const struct cudaChannelFormatDesc *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaBindTexture(size_t *offset, const struct textureReference *texref, const void *devPtr, const struct cudaChannelFormatDesc *desc, size_t size) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaBindTexture)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaBindTexture = (cudaError_t (*)(size_t *, const struct textureReference *, const void *, const struct cudaChannelFormatDesc *, size_t)) dlsym(libcudart_handle, "cudaBindTexture");
			fprintf(stderr, "cudaBindTexture:%p\n", wrapper_cudaBindTexture);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaBindTexture():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaBindTexture(offset, texref, devPtr, desc, size);
		return retval;
	}
}

