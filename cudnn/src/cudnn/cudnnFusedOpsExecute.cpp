#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnFusedOpsExecute)(cudnnHandle_t, const cudnnFusedOpsPlan_t, cudnnFusedOpsVariantParamPack_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnFusedOpsExecute(cudnnHandle_t handle, const cudnnFusedOpsPlan_t plan, cudnnFusedOpsVariantParamPack_t varPack{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnFusedOpsExecute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnFusedOpsExecute = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnFusedOpsPlan_t, cudnnFusedOpsVariantParamPack_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnFusedOpsExecute");
			fprintf(stderr, "wrapper_cudnnFusedOpsExecute:%p\n", wrapper_cudnnFusedOpsExecute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnFusedOpsExecute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnFusedOpsExecute(handle, plan, varPack);
		return retval;
	}
}

