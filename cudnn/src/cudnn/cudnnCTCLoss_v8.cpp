#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCTCLoss_v8)(cudnnHandle_t, cudnnCTCLossAlgo_t, cudnnCTCLossDescriptor_t, const cudnnTensorDescriptor_t, const void *, const int *, const int *, const int *, void *, const cudnnTensorDescriptor_t, void *, size_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCTCLoss_v8(cudnnHandle_t handle, cudnnCTCLossAlgo_t algo, cudnnCTCLossDescriptor_t ctcLossDesc, const cudnnTensorDescriptor_t probsDesc, const void *probs, const int labels[], const int labelLengths[], const int inputLengths[], void *costs, const cudnnTensorDescriptor_t gradientsDesc, void *gradients, size_t workSpaceSizeInBytes, void *workspace){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCTCLoss_v8)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCTCLoss_v8 = (cudnnStatus_t (*)(cudnnHandle_t, cudnnCTCLossAlgo_t, cudnnCTCLossDescriptor_t, const cudnnTensorDescriptor_t, const void *, const int *, const int *, const int *, void *, const cudnnTensorDescriptor_t, void *, size_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCTCLoss_v8");
			fprintf(stderr, "wrapper_cudnnCTCLoss_v8:%p\n", wrapper_cudnnCTCLoss_v8);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCTCLoss_v8():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCTCLoss_v8(handle, algo, ctcLossDesc, probsDesc, probs, labels, labelLengths, inputLengths, costs, gradientsDesc, gradients, workSpaceSizeInBytes, workspace);
		return retval;
	}
}

