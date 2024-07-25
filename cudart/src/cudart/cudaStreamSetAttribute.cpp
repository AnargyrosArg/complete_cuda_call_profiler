
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamSetAttribute)(cudaStream_t, cudaStreamAttrID, const cudaStreamAttrValue *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamSetAttribute(cudaStream_t hStream, cudaStreamAttrID attr, const cudaStreamAttrValue *value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamSetAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamSetAttribute = (cudaError_t (*)(cudaStream_t, cudaStreamAttrID, const cudaStreamAttrValue *)) dlsym(libcudart_handle, "cudaStreamSetAttribute");
			fprintf(stderr, "cudaStreamSetAttribute:%p\n", wrapper_cudaStreamSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamSetAttribute(hStream, attr, value);
		return retval;
	}
}

