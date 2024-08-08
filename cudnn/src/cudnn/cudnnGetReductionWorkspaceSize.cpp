#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnGetReductionWorkspaceSize)(cudnnHandle_t, const cudnnReduceTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnGetReductionWorkspaceSize(cudnnHandle_t handle, const cudnnReduceTensorDescriptor_t reduceTensorDesc, const cudnnTensorDescriptor_t aDesc, const cudnnTensorDescriptor_t cDesc, size_t *sizeInBytes){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnGetReductionWorkspaceSize)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnGetReductionWorkspaceSize = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnReduceTensorDescriptor_t, const cudnnTensorDescriptor_t, const cudnnTensorDescriptor_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnGetReductionWorkspaceSize");
			fprintf(stderr, "wrapper_cudnnGetReductionWorkspaceSize:%p\n", wrapper_cudnnGetReductionWorkspaceSize);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnGetReductionWorkspaceSize():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnGetReductionWorkspaceSize(handle, reduceTensorDesc, aDesc, cDesc, sizeInBytes);
		return retval;
	}
}

