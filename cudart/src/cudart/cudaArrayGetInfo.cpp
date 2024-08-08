
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaArrayGetInfo)(struct cudaChannelFormatDesc *, struct cudaExtent *, unsigned int *, cudaArray_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaArrayGetInfo(struct cudaChannelFormatDesc *desc, struct cudaExtent *extent, unsigned int *flags, cudaArray_t array) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaArrayGetInfo)
		{
			//fetch the original function addr using dlsym
			wrapper_cudaArrayGetInfo = (cudaError_t (*)(struct cudaChannelFormatDesc *, struct cudaExtent *, unsigned int *, cudaArray_t)) dlsym(libcudart_handle, "cudaArrayGetInfo");
			fprintf(stderr, "cudaArrayGetInfo:%p\n", wrapper_cudaArrayGetInfo);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cudaArrayGetInfo():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaArrayGetInfo(desc, extent, flags, array);
		return retval;
	}
}

