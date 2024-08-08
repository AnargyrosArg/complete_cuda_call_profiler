#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateFusedOpsVariantParamPack)(cudnnFusedOpsVariantParamPack_t *, cudnnFusedOps_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateFusedOpsVariantParamPack(cudnnFusedOpsVariantParamPack_t *varPack, cudnnFusedOps_t ops{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateFusedOpsVariantParamPack)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateFusedOpsVariantParamPack = (cudnnStatus_t (*)(cudnnFusedOpsVariantParamPack_t *, cudnnFusedOps_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateFusedOpsVariantParamPack");
			fprintf(stderr, "wrapper_cudnnCreateFusedOpsVariantParamPack:%p\n", wrapper_cudnnCreateFusedOpsVariantParamPack);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateFusedOpsVariantParamPack():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateFusedOpsVariantParamPack(varPack, ops);
		return retval;
	}
}

