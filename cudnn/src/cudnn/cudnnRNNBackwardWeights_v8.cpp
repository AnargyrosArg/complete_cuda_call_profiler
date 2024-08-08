#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnRNNBackwardWeights_v8)(cudnnHandle_t, cudnnRNNDescriptor_t, cudnnWgradMode_t, const int32_t *, cudnnRNNDataDescriptor_t, const void *, cudnnTensorDescriptor_t, const void *, cudnnRNNDataDescriptor_t, const void *, size_t, void *, size_t, void *, size_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnRNNBackwardWeights_v8(cudnnHandle_t handle, cudnnRNNDescriptor_t rnnDesc, cudnnWgradMode_t addGrad, const int32_t devSeqLengths[], cudnnRNNDataDescriptor_t xDesc, const void *x, cudnnTensorDescriptor_t hDesc, const void *hx, cudnnRNNDataDescriptor_t yDesc, const void *y, size_t weightSpaceSize, void *dweightSpace, size_t workSpaceSize, void *workSpace, size_t reserveSpaceSize, void *reserveSpace{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnRNNBackwardWeights_v8)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnRNNBackwardWeights_v8 = (cudnnStatus_t (*)(cudnnHandle_t, cudnnRNNDescriptor_t, cudnnWgradMode_t, const int32_t *, cudnnRNNDataDescriptor_t, const void *, cudnnTensorDescriptor_t, const void *, cudnnRNNDataDescriptor_t, const void *, size_t, void *, size_t, void *, size_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnRNNBackwardWeights_v8");
			fprintf(stderr, "wrapper_cudnnRNNBackwardWeights_v8:%p\n", wrapper_cudnnRNNBackwardWeights_v8);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnRNNBackwardWeights_v8():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnRNNBackwardWeights_v8(handle, rnnDesc, addGrad, devSeqLengths, xDesc, x, hDesc, hx, yDesc, y, weightSpaceSize, dweightSpace, workSpaceSize, workSpace, reserveSpaceSize, reserveSpace);
		return retval;
	}
}

