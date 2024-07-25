#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetActivationDescriptor)(const cudnnActivationDescriptor_t, cudnnActivationMode_t *, cudnnNanPropagation_t *, double *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetActivationDescriptor(const cudnnActivationDescriptor_t activationDesc, cudnnActivationMode_t *mode, cudnnNanPropagation_t *reluNanOpt, double *coef) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetActivationDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetActivationDescriptor = (cudnnStatus_t (*)(const cudnnActivationDescriptor_t, cudnnActivationMode_t *, cudnnNanPropagation_t *, double *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetActivationDescriptor");
			fprintf(stderr, "wrapper_cudnnGetActivationDescriptor:%p\n", wrapper_cudnnGetActivationDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetActivationDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetActivationDescriptor(activationDesc, mode, reluNanOpt, coef);
		return retval;
	}
}

