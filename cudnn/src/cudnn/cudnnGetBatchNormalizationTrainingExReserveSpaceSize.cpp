#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetBatchNormalizationTrainingExReserveSpaceSize)(cudnnHandle_t, cudnnBatchNormMode_t, cudnnBatchNormOps_t, const cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetBatchNormalizationTrainingExReserveSpaceSize(cudnnHandle_t handle, cudnnBatchNormMode_t mode, cudnnBatchNormOps_t bnOps, const cudnnActivationDescriptor_t activationDesc, const cudnnTensorDescriptor_t xDesc, size_t *sizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetBatchNormalizationTrainingExReserveSpaceSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetBatchNormalizationTrainingExReserveSpaceSize = (cudnnStatus_t (*)(cudnnHandle_t, cudnnBatchNormMode_t, cudnnBatchNormOps_t, const cudnnActivationDescriptor_t, const cudnnTensorDescriptor_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetBatchNormalizationTrainingExReserveSpaceSize");
			fprintf(stderr, "wrapper_cudnnGetBatchNormalizationTrainingExReserveSpaceSize:%p\n", wrapper_cudnnGetBatchNormalizationTrainingExReserveSpaceSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetBatchNormalizationTrainingExReserveSpaceSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetBatchNormalizationTrainingExReserveSpaceSize(handle, mode, bnOps, activationDesc, xDesc, sizeInBytes);
		return retval;
	}
}

