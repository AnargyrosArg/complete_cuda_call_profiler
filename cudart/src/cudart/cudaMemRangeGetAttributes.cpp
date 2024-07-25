
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemRangeGetAttributes)(void **, size_t *, enum cudaMemRangeAttribute *, size_t, const void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemRangeGetAttributes(void **data, size_t *dataSizes, enum cudaMemRangeAttribute *attributes, size_t numAttributes, const void *devPtr, size_t count) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemRangeGetAttributes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemRangeGetAttributes = (cudaError_t (*)(void **, size_t *, enum cudaMemRangeAttribute *, size_t, const void *, size_t)) dlsym(libcudart_handle, "cudaMemRangeGetAttributes");
			fprintf(stderr, "cudaMemRangeGetAttributes:%p\n", wrapper_cudaMemRangeGetAttributes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemRangeGetAttributes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemRangeGetAttributes(data, dataSizes, attributes, numAttributes, devPtr, count);
		return retval;
	}
}

