#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetReduceTensorDescriptor)(const cudnnReduceTensorDescriptor_t, cudnnReduceTensorOp_t *, cudnnDataType_t *, cudnnNanPropagation_t *, cudnnReduceTensorIndices_t *, cudnnIndicesType_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetReduceTensorDescriptor(const cudnnReduceTensorDescriptor_t reduceTensorDesc, cudnnReduceTensorOp_t *reduceTensorOp, cudnnDataType_t *reduceTensorCompType, cudnnNanPropagation_t *reduceTensorNanOpt, cudnnReduceTensorIndices_t *reduceTensorIndices, cudnnIndicesType_t *reduceTensorIndicesType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetReduceTensorDescriptor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetReduceTensorDescriptor = (cudnnStatus_t (*)(const cudnnReduceTensorDescriptor_t, cudnnReduceTensorOp_t *, cudnnDataType_t *, cudnnNanPropagation_t *, cudnnReduceTensorIndices_t *, cudnnIndicesType_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetReduceTensorDescriptor");
			fprintf(stderr, "wrapper_cudnnGetReduceTensorDescriptor:%p\n", wrapper_cudnnGetReduceTensorDescriptor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetReduceTensorDescriptor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetReduceTensorDescriptor(reduceTensorDesc, reduceTensorOp, reduceTensorCompType, reduceTensorNanOpt, reduceTensorIndices, reduceTensorIndicesType);
		return retval;
	}
}

