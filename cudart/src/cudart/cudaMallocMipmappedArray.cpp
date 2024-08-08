
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMallocMipmappedArray)(cudaMipmappedArray_t *, const struct cudaChannelFormatDesc *, struct cudaExtent, unsigned int, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMallocMipmappedArray(cudaMipmappedArray_t *mipmappedArray, const struct cudaChannelFormatDesc *desc, struct cudaExtent extent, unsigned int numLevels, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMallocMipmappedArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMallocMipmappedArray = (cudaError_t (*)(cudaMipmappedArray_t *, const struct cudaChannelFormatDesc *, struct cudaExtent, unsigned int, unsigned int)) dlsym(libcudart_handle, "cudaMallocMipmappedArray");
			fprintf(stderr, "cudaMallocMipmappedArray:%p\n", wrapper_cudaMallocMipmappedArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMallocMipmappedArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMallocMipmappedArray(mipmappedArray, desc, extent, numLevels, flags);
		return retval;
	}
}

