#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateFusedOpsPlan)(cudnnFusedOpsPlan_t *, cudnnFusedOps_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateFusedOpsPlan(cudnnFusedOpsPlan_t *plan, cudnnFusedOps_t ops) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateFusedOpsPlan)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateFusedOpsPlan = (cudnnStatus_t (*)(cudnnFusedOpsPlan_t *, cudnnFusedOps_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateFusedOpsPlan");
			fprintf(stderr, "wrapper_cudnnCreateFusedOpsPlan:%p\n", wrapper_cudnnCreateFusedOpsPlan);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateFusedOpsPlan():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateFusedOpsPlan(plan, ops);
		return retval;
	}
}

