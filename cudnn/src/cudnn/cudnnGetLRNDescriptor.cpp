#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetLRNDescriptor)(cudnnLRNDescriptor_t, unsigned *, double *, double *, double *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetLRNDescriptor(cudnnLRNDescriptor_t normDesc, unsigned *lrnN, double *lrnAlpha, double *lrnBeta, double *lrnK){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetLRNDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetLRNDescriptor = (cudnnStatus_t (*)(cudnnLRNDescriptor_t, unsigned *, double *, double *, double *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetLRNDescriptor");
			fprintf(stderr, "wrapper_cudnnGetLRNDescriptor:%p\n", wrapper_cudnnGetLRNDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetLRNDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetLRNDescriptor(normDesc, lrnN, lrnAlpha, lrnBeta, lrnK);
		return retval;
	}
}

