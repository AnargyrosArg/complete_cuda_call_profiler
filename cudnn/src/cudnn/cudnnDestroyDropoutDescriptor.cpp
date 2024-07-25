#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyDropoutDescriptor)(cudnnDropoutDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyDropoutDescriptor(cudnnDropoutDescriptor_t dropoutDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyDropoutDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyDropoutDescriptor = (cudnnStatus_t (*)(cudnnDropoutDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyDropoutDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyDropoutDescriptor:%p\n", wrapper_cudnnDestroyDropoutDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyDropoutDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyDropoutDescriptor(dropoutDesc);
		return retval;
	}
}
