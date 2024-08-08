#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreate)(cudnnHandle_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreate(cudnnHandle_t *handle{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreate)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreate = (cudnnStatus_t (*)(cudnnHandle_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreate");
			fprintf(stderr, "wrapper_cudnnCreate:%p\n", wrapper_cudnnCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreate(handle);
		return retval;
	}
}

