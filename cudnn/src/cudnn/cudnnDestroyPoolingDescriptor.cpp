#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyPoolingDescriptor)(cudnnPoolingDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyPoolingDescriptor(cudnnPoolingDescriptor_t poolingDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyPoolingDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyPoolingDescriptor = (cudnnStatus_t (*)(cudnnPoolingDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyPoolingDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyPoolingDescriptor:%p\n", wrapper_cudnnDestroyPoolingDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyPoolingDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyPoolingDescriptor(poolingDesc);
		return retval;
	}
}

