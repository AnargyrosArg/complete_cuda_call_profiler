#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNBackwardWeightsAlgorithmMaxCount)(cudnnHandle_t, const cudnnRNNDescriptor_t, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNBackwardWeightsAlgorithmMaxCount(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, int *count{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNBackwardWeightsAlgorithmMaxCount)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNBackwardWeightsAlgorithmMaxCount = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNBackwardWeightsAlgorithmMaxCount");
			fprintf(stderr, "wrapper_cudnnGetRNNBackwardWeightsAlgorithmMaxCount:%p\n", wrapper_cudnnGetRNNBackwardWeightsAlgorithmMaxCount);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNBackwardWeightsAlgorithmMaxCount():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNBackwardWeightsAlgorithmMaxCount(handle, rnnDesc, count);
		return retval;
	}
}

