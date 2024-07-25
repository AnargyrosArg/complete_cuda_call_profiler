#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetTensorTransformDescriptor)(cudnnTensorTransformDescriptor_t, const uint32_t, const cudnnTensorFormat_t, const int32_t *, const int32_t *, const uint32_t *, const cudnnFoldingDirection_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetTensorTransformDescriptor(cudnnTensorTransformDescriptor_t transformDesc, const uint32_t nbDims, const cudnnTensorFormat_t destFormat, const int32_t padBeforeA[], const int32_t padAfterA[], const uint32_t foldA[], const cudnnFoldingDirection_t direction) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetTensorTransformDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetTensorTransformDescriptor = (cudnnStatus_t (*)(cudnnTensorTransformDescriptor_t, const uint32_t, const cudnnTensorFormat_t, const int32_t *, const int32_t *, const uint32_t *, const cudnnFoldingDirection_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetTensorTransformDescriptor");
			fprintf(stderr, "wrapper_cudnnSetTensorTransformDescriptor:%p\n", wrapper_cudnnSetTensorTransformDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetTensorTransformDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetTensorTransformDescriptor(transformDesc, nbDims, destFormat, padBeforeA, padAfterA, foldA, direction);
		return retval;
	}
}

