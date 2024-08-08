
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaBindTexture2D)(size_t *, const struct textureReference *, const void *, const struct cudaChannelFormatDesc *, size_t, size_t, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaBindTexture2D(size_t *offset, const struct textureReference *texref, const void *devPtr, const struct cudaChannelFormatDesc *desc, size_t width, size_t height, size_t pitch) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaBindTexture2D)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaBindTexture2D = (cudaError_t (*)(size_t *, const struct textureReference *, const void *, const struct cudaChannelFormatDesc *, size_t, size_t, size_t)) dlsym(libcudart_handle, "cudaBindTexture2D");
			fprintf(stderr, "cudaBindTexture2D:%p\n", wrapper_cudaBindTexture2D);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaBindTexture2D():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaBindTexture2D(offset, texref, devPtr, desc, width, height, pitch);
		return retval;
	}
}

