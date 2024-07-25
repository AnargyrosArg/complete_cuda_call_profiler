#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCTCLoss)(cudnnHandle_t, const cudnnTensorDescriptor_t, const void *, const int *, const int *, const int *, void *, const cudnnTensorDescriptor_t, void *, cudnnCTCLossAlgo_t, cudnnCTCLossDescriptor_t, void *, size_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCTCLoss(cudnnHandle_t handle, const cudnnTensorDescriptor_t probsDesc, const void *probs, const int hostLabels[], const int hostLabelLengths[], const int hostInputLengths[], void *costs, const cudnnTensorDescriptor_t gradientsDesc, void *gradients, cudnnCTCLossAlgo_t algo, cudnnCTCLossDescriptor_t ctcLossDesc, void *workspace, size_t workSpaceSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCTCLoss)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCTCLoss = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnTensorDescriptor_t, const void *, const int *, const int *, const int *, void *, const cudnnTensorDescriptor_t, void *, cudnnCTCLossAlgo_t, cudnnCTCLossDescriptor_t, void *, size_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCTCLoss");
			fprintf(stderr, "wrapper_cudnnCTCLoss:%p\n", wrapper_cudnnCTCLoss);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCTCLoss():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCTCLoss(handle, probsDesc, probs, hostLabels, hostLabelLengths, hostInputLengths, costs, gradientsDesc, gradients, algo, ctcLossDesc, workspace, workSpaceSizeInBytes);
		return retval;
	}
}

