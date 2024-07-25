#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyFusedOpsConstParamPack)(cudnnFusedOpsConstParamPack_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyFusedOpsConstParamPack(cudnnFusedOpsConstParamPack_t constPack) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyFusedOpsConstParamPack)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyFusedOpsConstParamPack = (cudnnStatus_t (*)(cudnnFusedOpsConstParamPack_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyFusedOpsConstParamPack");
			fprintf(stderr, "wrapper_cudnnDestroyFusedOpsConstParamPack:%p\n", wrapper_cudnnDestroyFusedOpsConstParamPack);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyFusedOpsConstParamPack():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyFusedOpsConstParamPack(constPack);
		return retval;
	}
}

