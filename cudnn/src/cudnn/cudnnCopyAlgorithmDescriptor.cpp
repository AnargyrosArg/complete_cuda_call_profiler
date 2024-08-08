#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCopyAlgorithmDescriptor)(const cudnnAlgorithmDescriptor_t, cudnnAlgorithmDescriptor_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCopyAlgorithmDescriptor(const cudnnAlgorithmDescriptor_t src, cudnnAlgorithmDescriptor_t dest){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCopyAlgorithmDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCopyAlgorithmDescriptor = (cudnnStatus_t (*)(const cudnnAlgorithmDescriptor_t, cudnnAlgorithmDescriptor_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCopyAlgorithmDescriptor");
			fprintf(stderr, "wrapper_cudnnCopyAlgorithmDescriptor:%p\n", wrapper_cudnnCopyAlgorithmDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCopyAlgorithmDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCopyAlgorithmDescriptor(src, dest);
		return retval;
	}
}

