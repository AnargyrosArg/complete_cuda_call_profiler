
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaUserObjectRelease)(cudaUserObject_t, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaUserObjectRelease(cudaUserObject_t object, unsigned int count) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaUserObjectRelease)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaUserObjectRelease = (cudaError_t (*)(cudaUserObject_t, unsigned int)) dlsym(libcudart_handle, "cudaUserObjectRelease");
			fprintf(stderr, "cudaUserObjectRelease:%p\n", wrapper_cudaUserObjectRelease);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaUserObjectRelease():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaUserObjectRelease(object, count);
		return retval;
	}
}

