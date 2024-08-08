#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNBiasMode)(cudnnRNNDescriptor_t, cudnnRNNBiasMode_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNBiasMode(cudnnRNNDescriptor_t rnnDesc, cudnnRNNBiasMode_t *biasMode{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNBiasMode)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNBiasMode = (cudnnStatus_t (*)(cudnnRNNDescriptor_t, cudnnRNNBiasMode_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNBiasMode");
			fprintf(stderr, "wrapper_cudnnGetRNNBiasMode:%p\n", wrapper_cudnnGetRNNBiasMode);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNBiasMode():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNBiasMode(rnnDesc, biasMode);
		return retval;
	}
}

