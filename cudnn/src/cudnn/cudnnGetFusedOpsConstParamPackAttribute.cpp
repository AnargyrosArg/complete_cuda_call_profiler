#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetFusedOpsConstParamPackAttribute)(const cudnnFusedOpsConstParamPack_t, cudnnFusedOpsConstParamLabel_t, void *, int *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetFusedOpsConstParamPackAttribute(const cudnnFusedOpsConstParamPack_t constPack, cudnnFusedOpsConstParamLabel_t paramLabel, void *param, int *isNULL){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetFusedOpsConstParamPackAttribute)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetFusedOpsConstParamPackAttribute = (cudnnStatus_t (*)(const cudnnFusedOpsConstParamPack_t, cudnnFusedOpsConstParamLabel_t, void *, int *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetFusedOpsConstParamPackAttribute");
			fprintf(stderr, "wrapper_cudnnGetFusedOpsConstParamPackAttribute:%p\n", wrapper_cudnnGetFusedOpsConstParamPackAttribute);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetFusedOpsConstParamPackAttribute():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetFusedOpsConstParamPackAttribute(constPack, paramLabel, param, isNULL);
		return retval;
	}
}

