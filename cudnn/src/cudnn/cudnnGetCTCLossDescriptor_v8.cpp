#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetCTCLossDescriptor_v8)(cudnnCTCLossDescriptor_t, cudnnDataType_t *, cudnnLossNormalizationMode_t *, cudnnNanPropagation_t *, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetCTCLossDescriptor_v8(cudnnCTCLossDescriptor_t ctcLossDesc, cudnnDataType_t *compType, cudnnLossNormalizationMode_t *normMode, cudnnNanPropagation_t *gradMode, int *maxLabelLength) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetCTCLossDescriptor_v8)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetCTCLossDescriptor_v8 = (cudnnStatus_t (*)(cudnnCTCLossDescriptor_t, cudnnDataType_t *, cudnnLossNormalizationMode_t *, cudnnNanPropagation_t *, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetCTCLossDescriptor_v8");
			fprintf(stderr, "wrapper_cudnnGetCTCLossDescriptor_v8:%p\n", wrapper_cudnnGetCTCLossDescriptor_v8);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetCTCLossDescriptor_v8():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetCTCLossDescriptor_v8(ctcLossDesc, compType, normMode, gradMode, maxLabelLength);
		return retval;
	}
}

