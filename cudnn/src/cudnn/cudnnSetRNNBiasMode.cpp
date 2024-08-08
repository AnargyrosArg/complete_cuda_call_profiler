#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetRNNBiasMode)(cudnnRNNDescriptor_t, cudnnRNNBiasMode_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetRNNBiasMode(cudnnRNNDescriptor_t rnnDesc, cudnnRNNBiasMode_t biasMode{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetRNNBiasMode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetRNNBiasMode = (cudnnStatus_t (*)(cudnnRNNDescriptor_t, cudnnRNNBiasMode_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetRNNBiasMode");
			fprintf(stderr, "wrapper_cudnnSetRNNBiasMode:%p\n", wrapper_cudnnSetRNNBiasMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetRNNBiasMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetRNNBiasMode(rnnDesc, biasMode);
		return retval;
	}
}

