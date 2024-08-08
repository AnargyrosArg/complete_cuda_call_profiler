#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnBatchNormalizationBackward)(cudnnHandle_t, cudnnBatchNormMode_t, const void *, const void *, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, const void *, void *, void *, double, const void *, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnBatchNormalizationBackward(cudnnHandle_t handle, cudnnBatchNormMode_t mode, const void *alphaDataDiff, const void *betaDataDiff, const void *alphaParamDiff, const void *betaParamDiff, const cudnnTensorDescriptor_t xDesc, const void *x, const cudnnTensorDescriptor_t dyDesc, const void *dy, const cudnnTensorDescriptor_t dxDesc, void *dx, const cudnnTensorDescriptor_t dBnScaleBiasDesc, const void *bnScale, void *dBnScaleResult, void *dBnBiasResult, double epsilon, const void *savedMean, const void *savedInvVariance{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnBatchNormalizationBackward)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnBatchNormalizationBackward = (cudnnStatus_t (*)(cudnnHandle_t, cudnnBatchNormMode_t, const void *, const void *, const void *, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, const void *, const cudnnTensorDescriptor_t, void *, const cudnnTensorDescriptor_t, const void *, void *, void *, double, const void *, const void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnBatchNormalizationBackward");
			fprintf(stderr, "wrapper_cudnnBatchNormalizationBackward:%p\n", wrapper_cudnnBatchNormalizationBackward);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnBatchNormalizationBackward():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnBatchNormalizationBackward(handle, mode, alphaDataDiff, betaDataDiff, alphaParamDiff, betaParamDiff, xDesc, x, dyDesc, dy, dxDesc, dx, dBnScaleBiasDesc, bnScale, dBnScaleResult, dBnBiasResult, epsilon, savedMean, savedInvVariance);
		return retval;
	}
}

