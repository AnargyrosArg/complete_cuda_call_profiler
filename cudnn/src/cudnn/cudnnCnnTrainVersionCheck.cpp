#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCnnTrainVersionCheck)();
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCnnTrainVersionCheck({
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCnnTrainVersionCheck)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCnnTrainVersionCheck = (cudnnStatus_t (*)()) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCnnTrainVersionCheck");
			fprintf(stderr, "wrapper_cudnnCnnTrainVersionCheck:%p\n", wrapper_cudnnCnnTrainVersionCheck);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCnnTrainVersionCheck():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCnnTrainVersionCheck();
		return retval;
	}
}

