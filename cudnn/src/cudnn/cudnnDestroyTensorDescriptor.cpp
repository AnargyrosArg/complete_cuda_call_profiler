#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyTensorDescriptor)(cudnnTensorDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyTensorDescriptor(cudnnTensorDescriptor_t tensorDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyTensorDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyTensorDescriptor = (cudnnStatus_t (*)(cudnnTensorDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyTensorDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyTensorDescriptor:%p\n", wrapper_cudnnDestroyTensorDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyTensorDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyTensorDescriptor(tensorDesc);
		return retval;
	}
}

