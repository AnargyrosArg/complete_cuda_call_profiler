
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaStreamGetAttribute)(cudaStream_t, cudaStreamAttrID, cudaStreamAttrValue *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaStreamGetAttribute(cudaStream_t hStream, cudaStreamAttrID attr, cudaStreamAttrValue *value_out) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaStreamGetAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaStreamGetAttribute = (cudaError_t (*)(cudaStream_t, cudaStreamAttrID, cudaStreamAttrValue *)) dlsym(libcudart_handle, "cudaStreamGetAttribute");
			fprintf(stderr, "cudaStreamGetAttribute:%p\n", wrapper_cudaStreamGetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaStreamGetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaStreamGetAttribute(hStream, attr, value_out);
		return retval;
	}
}

