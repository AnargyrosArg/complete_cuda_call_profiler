#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetRNNForwardTrainingAlgorithmMaxCount)(cudnnHandle_t, const cudnnRNNDescriptor_t, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetRNNForwardTrainingAlgorithmMaxCount(cudnnHandle_t handle, const cudnnRNNDescriptor_t rnnDesc, int *count) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetRNNForwardTrainingAlgorithmMaxCount)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetRNNForwardTrainingAlgorithmMaxCount = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnRNNDescriptor_t, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetRNNForwardTrainingAlgorithmMaxCount");
			fprintf(stderr, "wrapper_cudnnGetRNNForwardTrainingAlgorithmMaxCount:%p\n", wrapper_cudnnGetRNNForwardTrainingAlgorithmMaxCount);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetRNNForwardTrainingAlgorithmMaxCount():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetRNNForwardTrainingAlgorithmMaxCount(handle, rnnDesc, count);
		return retval;
	}
}

