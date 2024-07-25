#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyFusedOpsVariantParamPack)(cudnnFusedOpsVariantParamPack_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyFusedOpsVariantParamPack(cudnnFusedOpsVariantParamPack_t varPack) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyFusedOpsVariantParamPack)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyFusedOpsVariantParamPack = (cudnnStatus_t (*)(cudnnFusedOpsVariantParamPack_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyFusedOpsVariantParamPack");
			fprintf(stderr, "wrapper_cudnnDestroyFusedOpsVariantParamPack:%p\n", wrapper_cudnnDestroyFusedOpsVariantParamPack);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyFusedOpsVariantParamPack():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyFusedOpsVariantParamPack(varPack);
		return retval;
	}
}

