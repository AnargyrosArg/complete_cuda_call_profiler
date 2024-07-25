
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaFuncSetAttribute)(const void *, enum cudaFuncAttribute, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaFuncSetAttribute(const void *func, enum cudaFuncAttribute attr, int value) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaFuncSetAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaFuncSetAttribute = (cudaError_t (*)(const void *, enum cudaFuncAttribute, int)) dlsym(libcudart_handle, "cudaFuncSetAttribute");
			fprintf(stderr, "cudaFuncSetAttribute:%p\n", wrapper_cudaFuncSetAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaFuncSetAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaFuncSetAttribute(func, attr, value);
		return retval;
	}
}

