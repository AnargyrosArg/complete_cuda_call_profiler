#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNForwardInferenceAlgorithmMaxCount)(cudnnHandle_t, const cudnnRNNDescriptor_t, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNForwardInferenceAlgorithmMaxCount(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, int *count{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNForwardInferenceAlgorithmMaxCount)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNForwardInferenceAlgorithmMaxCount = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNForwardInferenceAlgorithmMaxCount");
			fprintf(stderr, "wrapper_cudnnGetRNNForwardInferenceAlgorithmMaxCount:%p\n", wrapper_cudnnGetRNNForwardInferenceAlgorithmMaxCount);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNForwardInferenceAlgorithmMaxCount():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNForwardInferenceAlgorithmMaxCount(handle, rnnDesc, count);
		return retval;
	}
}

