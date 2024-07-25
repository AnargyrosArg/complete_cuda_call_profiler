#include <cudnn_cnn_train.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnMakeFusedOpsPlan)(cudnnHandle_t, cudnnFusedOpsPlan_t, const cudnnFusedOpsConstParamPack_t, size_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnMakeFusedOpsPlan(cudnnHandle_t handle, cudnnFusedOpsPlan_t plan, const cudnnFusedOpsConstParamPack_t constPack, size_t *workspaceSizeInBytes) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnMakeFusedOpsPlan)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnMakeFusedOpsPlan = (cudnnStatus_t (*)(cudnnHandle_t, cudnnFusedOpsPlan_t, const cudnnFusedOpsConstParamPack_t, size_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnMakeFusedOpsPlan");
			fprintf(stderr, "wrapper_cudnnMakeFusedOpsPlan:%p\n", wrapper_cudnnMakeFusedOpsPlan);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnMakeFusedOpsPlan():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnMakeFusedOpsPlan(handle, plan, constPack, workspaceSizeInBytes);
		return retval;
	}
}

