
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaDestroyTextureObject)(cudaTextureObject_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaDestroyTextureObject(cudaTextureObject_t texObject) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaDestroyTextureObject)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaDestroyTextureObject = (cudaError_t (*)(cudaTextureObject_t)) dlsym(libcudart_handle, "cudaDestroyTextureObject");
			fprintf(stderr, "cudaDestroyTextureObject:%p\n", wrapper_cudaDestroyTextureObject);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaDestroyTextureObject():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaDestroyTextureObject(texObject);
		return retval;
	}
}

