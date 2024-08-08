#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetCTCLossDescriptor)(cudnnCTCLossDescriptor_t, cudnnDataType_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetCTCLossDescriptor(cudnnCTCLossDescriptor_t ctcLossDesc, cudnnDataType_t *compType){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetCTCLossDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetCTCLossDescriptor = (cudnnStatus_t (*)(cudnnCTCLossDescriptor_t, cudnnDataType_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetCTCLossDescriptor");
			fprintf(stderr, "wrapper_cudnnGetCTCLossDescriptor:%p\n", wrapper_cudnnGetCTCLossDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetCTCLossDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetCTCLossDescriptor(ctcLossDesc, compType);
		return retval;
	}
}

