#include <cudnn_ops_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnReduceTensor)(cudnnHandle_t, const cudnnReduceTensorDescriptor_t, void *, size_t, void *, size_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, void *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnReduceTensor(cudnnHandle_t handle, const cudnnReduceTensorDescriptor_t reduceTensorDesc, void *indices, size_t indicesSizeInBytes, void *workspace, size_t workspaceSizeInBytes, const void *alpha, const cudnnTensorDescriptor_t aDesc, const void *A, const void *beta, const cudnnTensorDescriptor_t cDesc, void *C){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnReduceTensor)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnReduceTensor = (cudnnStatus_t (*)(cudnnHandle_t, const cudnnReduceTensorDescriptor_t, void *, size_t, void *, size_t, const void *, const cudnnTensorDescriptor_t, const void *, const void *, const cudnnTensorDescriptor_t, void *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnReduceTensor");
			fprintf(stderr, "wrapper_cudnnReduceTensor:%p\n", wrapper_cudnnReduceTensor);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnReduceTensor():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnReduceTensor(handle, reduceTensorDesc, indices, indicesSizeInBytes, workspace, workspaceSizeInBytes, alpha, aDesc, A, beta, cDesc, C);
		return retval;
	}
}

