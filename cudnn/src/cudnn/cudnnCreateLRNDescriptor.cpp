#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateLRNDescriptor)(cudnnLRNDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateLRNDescriptor(cudnnLRNDescriptor_t *normDesc){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateLRNDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateLRNDescriptor = (cudnnStatus_t (*)(cudnnLRNDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateLRNDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateLRNDescriptor:%p\n", wrapper_cudnnCreateLRNDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateLRNDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateLRNDescriptor(normDesc);
		return retval;
	}
}

