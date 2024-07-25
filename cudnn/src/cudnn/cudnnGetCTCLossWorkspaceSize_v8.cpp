#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetCTCLossWorkspaceSize_v8)(cudnnHandle_t, cudnnCTCLossAlgo_t, cudnnCTCLossDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetCTCLossWorkspaceSize_v8(cudnnHandle_t handle, cudnnCTCLossAlgo_t algo, cudnnCTCLossDescriptor_t ctcLossDesc, const cudnnTensorDescriptor_t probsDesc, const cudnnTensorDescriptor_t gradientsDesc, size_t *sizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetCTCLossWorkspaceSize_v8)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetCTCLossWorkspaceSize_v8 = (cudnnStatus_t (*)(cudnnHandle_t, cudnnCTCLossAlgo_t, cudnnCTCLossDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetCTCLossWorkspaceSize_v8");
			fprintf(stderr, "wrapper_cudnnGetCTCLossWorkspaceSize_v8:%p\n", wrapper_cudnnGetCTCLossWorkspaceSize_v8);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetCTCLossWorkspaceSize_v8():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetCTCLossWorkspaceSize_v8(handle, algo, ctcLossDesc, probsDesc, gradientsDesc, sizeInBytes);
		return retval;
	}
}

