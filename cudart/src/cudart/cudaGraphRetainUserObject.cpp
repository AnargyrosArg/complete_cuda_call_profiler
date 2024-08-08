
#include <cuda_runtime_api.h>
#include <dlfcn.h>
#include <iostream>
cudaError_t (*wrapper_cudaGraphRetainUserObject)(cudaGraph_t, cudaUserObject_t, unsigned int, unsigned int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libcudart_handle;
extern "C"
{
	cudaError_t cudaGraphRetainUserObject(cudaGraph_t graph, cudaUserObject_t object, unsigned int count, unsigned int flags) {
		char* __dlerror;
        #ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif
		//this call clears any previous errors
		dlerror();
		if(libcudart_handle == NULL){
			libcudart_handle = dlopen("/usr/local/cuda-11.7/lib64/libcudart.so.11.0", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudaGraphRetainUserObject)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudaGraphRetainUserObject = (cudaError_t (*)(cudaGraph_t, cudaUserObject_t, unsigned int, unsigned int)) dlsym(libcudart_handle, "cudaGraphRetainUserObject");
			fprintf(stderr, "cudaGraphRetainUserObject:%p\n", wrapper_cudaGraphRetainUserObject);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudaGraphRetainUserObject():%s\n", __dlerror);
			fflush(stderr);
		}
		cudaError_t retval = wrapper_cudaGraphRetainUserObject(graph, object, count, flags);
		return retval;
	}
}

