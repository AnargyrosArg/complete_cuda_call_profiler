#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetCTCLossDescriptor)(cudnnCTCLossDescriptor_t, cudnnDataType_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetCTCLossDescriptor(cudnnCTCLossDescriptor_t ctcLossDesc, cudnnDataType_t compType){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetCTCLossDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetCTCLossDescriptor = (cudnnStatus_t (*)(cudnnCTCLossDescriptor_t, cudnnDataType_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetCTCLossDescriptor");
			fprintf(stderr, "wrapper_cudnnSetCTCLossDescriptor:%p\n", wrapper_cudnnSetCTCLossDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetCTCLossDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetCTCLossDescriptor(ctcLossDesc, compType);
		return retval;
	}
}

