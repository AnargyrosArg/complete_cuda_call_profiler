#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetRNNPaddingMode)(cudnnRNNDescriptor_t, unsigned);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetRNNPaddingMode(cudnnRNNDescriptor_t rnnDesc, unsigned paddingMode){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetRNNPaddingMode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetRNNPaddingMode = (cudnnStatus_t (*)(cudnnRNNDescriptor_t, unsigned)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetRNNPaddingMode");
			fprintf(stderr, "wrapper_cudnnSetRNNPaddingMode:%p\n", wrapper_cudnnSetRNNPaddingMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetRNNPaddingMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetRNNPaddingMode(rnnDesc, paddingMode);
		return retval;
	}
}

