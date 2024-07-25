
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMalloc3DArray)(cudaArray_t *, const struct cudaChannelFormatDesc *, struct cudaExtent, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMalloc3DArray(cudaArray_t *array, const struct cudaChannelFormatDesc *desc, struct cudaExtent extent, unsigned int flags) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMalloc3DArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMalloc3DArray = (cudaError_t (*)(cudaArray_t *, const struct cudaChannelFormatDesc *, struct cudaExtent, unsigned int)) dlsym(libcudart_handle, "cudaMalloc3DArray");
			fprintf(stderr, "cudaMalloc3DArray:%p\n", wrapper_cudaMalloc3DArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMalloc3DArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMalloc3DArray(array, desc, extent, flags);
		return retval;
	}
}

