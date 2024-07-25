#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateCTCLossDescriptor)(cudnnCTCLossDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateCTCLossDescriptor(cudnnCTCLossDescriptor_t *ctcLossDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateCTCLossDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateCTCLossDescriptor = (cudnnStatus_t (*)(cudnnCTCLossDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateCTCLossDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateCTCLossDescriptor:%p\n", wrapper_cudnnCreateCTCLossDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateCTCLossDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateCTCLossDescriptor(ctcLossDesc);
		return retval;
	}
}

