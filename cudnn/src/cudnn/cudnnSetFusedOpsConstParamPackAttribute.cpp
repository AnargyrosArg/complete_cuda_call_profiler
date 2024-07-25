#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetFusedOpsConstParamPackAttribute)(cudnnFusedOpsConstParamPack_t, cudnnFusedOpsConstParamLabel_t, const void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetFusedOpsConstParamPackAttribute(cudnnFusedOpsConstParamPack_t constPack, cudnnFusedOpsConstParamLabel_t paramLabel, const void *param) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetFusedOpsConstParamPackAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetFusedOpsConstParamPackAttribute = (cudnnStatus_t (*)(cudnnFusedOpsConstParamPack_t, cudnnFusedOpsConstParamLabel_t, const void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetFusedOpsConstParamPackAttribute");
			fprintf(stderr, "wrapper_cudnnSetFusedOpsConstParamPackAttribute:%p\n", wrapper_cudnnSetFusedOpsConstParamPackAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetFusedOpsConstParamPackAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetFusedOpsConstParamPackAttribute(constPack, paramLabel, param);
		return retval;
	}
}

