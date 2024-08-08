
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMallocArray)(cudaArray_t *, const struct cudaChannelFormatDesc *, size_t, size_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMallocArray(cudaArray_t *array, const struct cudaChannelFormatDesc *desc, size_t width, size_t height, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMallocArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMallocArray = (cudaError_t (*)(cudaArray_t *, const struct cudaChannelFormatDesc *, size_t, size_t, unsigned int)) dlsym(libcudart_handle, "cudaMallocArray");
			fprintf(stderr, "cudaMallocArray:%p\n", wrapper_cudaMallocArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMallocArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMallocArray(array, desc, width, height, flags);
		return retval;
	}
}

