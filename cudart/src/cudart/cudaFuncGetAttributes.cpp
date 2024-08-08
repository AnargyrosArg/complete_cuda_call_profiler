
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaFuncGetAttributes)(struct cudaFuncAttributes *, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaFuncGetAttributes(struct cudaFuncAttributes *attr, const void *func) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaFuncGetAttributes)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaFuncGetAttributes = (cudaError_t (*)(struct cudaFuncAttributes *, const void *)) dlsym(libcudart_handle, "cudaFuncGetAttributes");
			fprintf(stderr, "cudaFuncGetAttributes:%p\n", wrapper_cudaFuncGetAttributes);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaFuncGetAttributes():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaFuncGetAttributes(attr, func);
		return retval;
	}
}

