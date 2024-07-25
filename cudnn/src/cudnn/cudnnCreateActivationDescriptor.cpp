#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateActivationDescriptor)(cudnnActivationDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateActivationDescriptor(cudnnActivationDescriptor_t *activationDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateActivationDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateActivationDescriptor = (cudnnStatus_t (*)(cudnnActivationDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateActivationDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateActivationDescriptor:%p\n", wrapper_cudnnCreateActivationDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateActivationDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateActivationDescriptor(activationDesc);
		return retval;
	}
}

