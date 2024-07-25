#include <cudnn_ops_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnOpsTrainVersionCheck)();
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnOpsTrainVersionCheck() {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnOpsTrainVersionCheck)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnOpsTrainVersionCheck = (cudnnStatus_t (*)()) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnOpsTrainVersionCheck");
			fprintf(stderr, "wrapper_cudnnOpsTrainVersionCheck:%p\n", wrapper_cudnnOpsTrainVersionCheck);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnOpsTrainVersionCheck():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnOpsTrainVersionCheck();
		return retval;
	}
}

