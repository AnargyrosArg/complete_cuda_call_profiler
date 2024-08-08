
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaUserObjectRetain)(cudaUserObject_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaUserObjectRetain(cudaUserObject_t object, unsigned int count) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaUserObjectRetain)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaUserObjectRetain = (cudaError_t (*)(cudaUserObject_t, unsigned int)) dlsym(libcudart_handle, "cudaUserObjectRetain");
			fprintf(stderr, "cudaUserObjectRetain:%p\n", wrapper_cudaUserObjectRetain);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaUserObjectRetain():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaUserObjectRetain(object, count);
		return retval;
	}
}

