
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaFreeArray)(cudaArray_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaFreeArray(cudaArray_t array) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaFreeArray)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaFreeArray = (cudaError_t (*)(cudaArray_t)) dlsym(libcudart_handle, "cudaFreeArray");
			fprintf(stderr, "cudaFreeArray:%p\n", wrapper_cudaFreeArray);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaFreeArray():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaFreeArray(array);
		return retval;
	}
}

