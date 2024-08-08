#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyActivationDescriptor)(cudnnActivationDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyActivationDescriptor(cudnnActivationDescriptor_t activationDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyActivationDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyActivationDescriptor = (cudnnStatus_t (*)(cudnnActivationDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyActivationDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyActivationDescriptor:%p\n", wrapper_cudnnDestroyActivationDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyActivationDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyActivationDescriptor(activationDesc);
		return retval;
	}
}

