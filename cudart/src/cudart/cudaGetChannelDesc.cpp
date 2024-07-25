
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGetChannelDesc)(struct cudaChannelFormatDesc *, cudaArray_const_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGetChannelDesc(struct cudaChannelFormatDesc *desc, cudaArray_const_t array) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGetChannelDesc)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGetChannelDesc = (cudaError_t (*)(struct cudaChannelFormatDesc *, cudaArray_const_t)) dlsym(libcudart_handle, "cudaGetChannelDesc");
			fprintf(stderr, "cudaGetChannelDesc:%p\n", wrapper_cudaGetChannelDesc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGetChannelDesc():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGetChannelDesc(desc, array);
		return retval;
	}
}

