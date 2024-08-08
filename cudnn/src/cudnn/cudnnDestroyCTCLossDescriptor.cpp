#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyCTCLossDescriptor)(cudnnCTCLossDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyCTCLossDescriptor(cudnnCTCLossDescriptor_t ctcLossDesc{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyCTCLossDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyCTCLossDescriptor = (cudnnStatus_t (*)(cudnnCTCLossDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyCTCLossDescriptor");
			fprintf(stderr, "wrapper_cudnnDestroyCTCLossDescriptor:%p\n", wrapper_cudnnDestroyCTCLossDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyCTCLossDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyCTCLossDescriptor(ctcLossDesc);
		return retval;
	}
}

