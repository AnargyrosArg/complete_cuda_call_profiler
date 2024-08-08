#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetNormalizationBackwardWorkspaceSize)(cudnnHandle_t, cudnnNormMode_t, cudnnNormOps_t, cudnnNormAlgo_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, size_t *, int);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetNormalizationBackwardWorkspaceSize(cudnnHandle_t handle, cudnnNormMode_t mode, cudnnNormOps_t normOps, cudnnNormAlgo_t algo, const cudnnTensorDescriptor_t xDesc, const cudnnTensorDescriptor_t yDesc, const cudnnTensorDescriptor_t dyDesc, const cudnnTensorDescriptor_t dzDesc, const cudnnTensorDescriptor_t dxDesc, const cudnnTensorDescriptor_t dNormScaleBiasDesc, const cudnnActivationDescriptor_t activationDesc, const cudnnTensorDescriptor_t normMeanVarDesc, size_t *sizeInBytes, int groupCnt){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetNormalizationBackwardWorkspaceSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetNormalizationBackwardWorkspaceSize = (cudnnStatus_t (*)(cudnnHandle_t, cudnnNormMode_t, cudnnNormOps_t, cudnnNormAlgo_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, size_t *, int)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetNormalizationBackwardWorkspaceSize");
			fprintf(stderr, "wrapper_cudnnGetNormalizationBackwardWorkspaceSize:%p\n", wrapper_cudnnGetNormalizationBackwardWorkspaceSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetNormalizationBackwardWorkspaceSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetNormalizationBackwardWorkspaceSize(handle, mode, normOps, algo, xDesc, yDesc, dyDesc, dzDesc, dxDesc, dNormScaleBiasDesc, activationDesc, normMeanVarDesc, sizeInBytes, groupCnt);
		return retval;
	}
}

