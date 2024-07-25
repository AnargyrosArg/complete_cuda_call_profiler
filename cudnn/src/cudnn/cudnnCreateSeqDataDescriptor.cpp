#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreateSeqDataDescriptor)(cudnnSeqDataDescriptor_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreateSeqDataDescriptor(cudnnSeqDataDescriptor_t *seqDataDesc) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreateSeqDataDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreateSeqDataDescriptor = (cudnnStatus_t (*)(cudnnSeqDataDescriptor_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreateSeqDataDescriptor");
			fprintf(stderr, "wrapper_cudnnCreateSeqDataDescriptor:%p\n", wrapper_cudnnCreateSeqDataDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreateSeqDataDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreateSeqDataDescriptor(seqDataDesc);
		return retval;
	}
}

