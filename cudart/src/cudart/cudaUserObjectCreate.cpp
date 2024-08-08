
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaUserObjectCreate)(cudaUserObject_t *, void *, cudaHostFn_t, unsigned int, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaUserObjectCreate(cudaUserObject_t *object_out, void *ptr, cudaHostFn_t destroy, unsigned int initialRefcount, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaUserObjectCreate)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaUserObjectCreate = (cudaError_t (*)(cudaUserObject_t *, void *, cudaHostFn_t, unsigned int, unsigned int)) dlsym(libcudart_handle, "cudaUserObjectCreate");
			fprintf(stderr, "cudaUserObjectCreate:%p\n", wrapper_cudaUserObjectCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaUserObjectCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaUserObjectCreate(object_out, ptr, destroy, initialRefcount, flags);
		return retval;
	}
}

