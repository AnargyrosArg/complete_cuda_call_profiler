#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnDestroyFusedOpsPlan)(cudnnFusedOpsPlan_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnDestroyFusedOpsPlan(cudnnFusedOpsPlan_t plan) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnDestroyFusedOpsPlan)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnDestroyFusedOpsPlan = (cudnnStatus_t (*)(cudnnFusedOpsPlan_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnDestroyFusedOpsPlan");
			fprintf(stderr, "wrapper_cudnnDestroyFusedOpsPlan:%p\n", wrapper_cudnnDestroyFusedOpsPlan);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnDestroyFusedOpsPlan():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnDestroyFusedOpsPlan(plan);
		return retval;
	}
}

