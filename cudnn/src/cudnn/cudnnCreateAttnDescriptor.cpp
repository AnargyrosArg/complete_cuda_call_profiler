#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateAttnDescriptor)(cudnnAttnDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateAttnDescriptor(cudnnAttnDescriptor_t *attnDesc{
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateAttnDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateAttnDescriptor = (cudnnStatus_t (*)(cudnnAttnDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateAttnDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateAttnDescriptor:%p\n", wrapper_cudnnCreateAttnDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateAttnDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateAttnDescriptor(attnDesc);
		return retval;
	}
}

