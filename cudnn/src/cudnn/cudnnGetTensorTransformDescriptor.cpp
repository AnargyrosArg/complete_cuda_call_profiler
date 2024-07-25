#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetTensorTransformDescriptor)(cudnnTensorTransformDescriptor_t, uint32_t, cudnnTensorFormat_t *, int32_t *, int32_t *, uint32_t *, cudnnFoldingDirection_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetTensorTransformDescriptor(cudnnTensorTransformDescriptor_t transformDesc, uint32_t nbDimsRequested, cudnnTensorFormat_t *destFormat, int32_t padBeforeA[], int32_t padAfterA[], uint32_t foldA[], cudnnFoldingDirection_t *direction) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetTensorTransformDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetTensorTransformDescriptor = (cudnnStatus_t (*)(cudnnTensorTransformDescriptor_t, uint32_t, cudnnTensorFormat_t *, int32_t *, int32_t *, uint32_t *, cudnnFoldingDirection_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetTensorTransformDescriptor");
			fprintf(stderr, "wrapper_cudnnGetTensorTransformDescriptor:%p\n", wrapper_cudnnGetTensorTransformDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetTensorTransformDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetTensorTransformDescriptor(transformDesc, nbDimsRequested, destFormat, padBeforeA, padAfterA, foldA, direction);
		return retval;
	}
}

