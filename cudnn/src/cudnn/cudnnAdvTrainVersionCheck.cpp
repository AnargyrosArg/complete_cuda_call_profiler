#include <cudnn_adv_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnAdvTrainVersionCheck)();
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnAdvTrainVersionCheck(){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnAdvTrainVersionCheck)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnAdvTrainVersionCheck = (cudnnStatus_t (*)()) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnAdvTrainVersionCheck");
			fprintf(stderr, "wrapper_cudnnAdvTrainVersionCheck:%p\n", wrapper_cudnnAdvTrainVersionCheck);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnAdvTrainVersionCheck():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnAdvTrainVersionCheck();
		return retval;
	}
}

