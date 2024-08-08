
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaMemRangeGetAttribute)(void *, size_t, enum cudaMemRangeAttribute, const void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaMemRangeGetAttribute(void *data, size_t dataSize, enum cudaMemRangeAttribute attribute, const void *devPtr, size_t count) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaMemRangeGetAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaMemRangeGetAttribute = (cudaError_t (*)(void *, size_t, enum cudaMemRangeAttribute, const void *, size_t)) dlsym(libcudart_handle, "cudaMemRangeGetAttribute");
			fprintf(stderr, "cudaMemRangeGetAttribute:%p\n", wrapper_cudaMemRangeGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaMemRangeGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaMemRangeGetAttribute(data, dataSize, attribute, devPtr, count);
		return retval;
	}
}

