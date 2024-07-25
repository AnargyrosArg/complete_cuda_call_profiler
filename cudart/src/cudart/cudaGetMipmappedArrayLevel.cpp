
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetMipmappedArrayLevel)(cudaArray_t *, cudaMipmappedArray_const_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetMipmappedArrayLevel(cudaArray_t *levelArray, cudaMipmappedArray_const_t mipmappedArray, unsigned int level) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetMipmappedArrayLevel)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetMipmappedArrayLevel = (cudaError_t (*)(cudaArray_t *, cudaMipmappedArray_const_t, unsigned int)) dlsym(libcudart_handle, "cudaGetMipmappedArrayLevel");
			fprintf(stderr, "cudaGetMipmappedArrayLevel:%p\n", wrapper_cudaGetMipmappedArrayLevel);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetMipmappedArrayLevel():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetMipmappedArrayLevel(levelArray, mipmappedArray, level);
		return retval;
	}
}

