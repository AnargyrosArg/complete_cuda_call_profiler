
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaFreeMipmappedArray)(cudaMipmappedArray_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaFreeMipmappedArray(cudaMipmappedArray_t mipmappedArray) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaFreeMipmappedArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaFreeMipmappedArray = (cudaError_t (*)(cudaMipmappedArray_t)) dlsym(libcudart_handle, "cudaFreeMipmappedArray");
			fprintf(stderr, "cudaFreeMipmappedArray:%p\n", wrapper_cudaFreeMipmappedArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaFreeMipmappedArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaFreeMipmappedArray(mipmappedArray);
		return retval;
	}
}

