#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetFusedOpsVariantParamPackAttribute)(const cudnnFusedOpsVariantParamPack_t, cudnnFusedOpsVariantParamLabel_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetFusedOpsVariantParamPackAttribute(const cudnnFusedOpsVariantParamPack_t varPack, cudnnFusedOpsVariantParamLabel_t paramLabel, void *ptr){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetFusedOpsVariantParamPackAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetFusedOpsVariantParamPackAttribute = (cudnnStatus_t (*)(const cudnnFusedOpsVariantParamPack_t, cudnnFusedOpsVariantParamLabel_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetFusedOpsVariantParamPackAttribute");
			fprintf(stderr, "wrapper_cudnnGetFusedOpsVariantParamPackAttribute:%p\n", wrapper_cudnnGetFusedOpsVariantParamPackAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetFusedOpsVariantParamPackAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetFusedOpsVariantParamPackAttribute(varPack, paramLabel, ptr);
		return retval;
	}
}

