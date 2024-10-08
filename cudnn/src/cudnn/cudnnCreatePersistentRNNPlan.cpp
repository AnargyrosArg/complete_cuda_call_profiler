#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnCreatePersistentRNNPlan)(cudnnRNNDescriptor_t, const int, const cudnnDataType_t, cudnnPersistentRNNPlan_t *);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnCreatePersistentRNNPlan(cudnnRNNDescriptor_t rnnDesc, const int minibatch, const cudnnDataType_t dataType, cudnnPersistentRNNPlan_t *plan){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnCreatePersistentRNNPlan)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnCreatePersistentRNNPlan = (cudnnStatus_t (*)(cudnnRNNDescriptor_t, const int, const cudnnDataType_t, cudnnPersistentRNNPlan_t *)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnCreatePersistentRNNPlan");
			fprintf(stderr, "wrapper_cudnnCreatePersistentRNNPlan:%p\n", wrapper_cudnnCreatePersistentRNNPlan);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnCreatePersistentRNNPlan():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnCreatePersistentRNNPlan(rnnDesc, minibatch, dataType, plan);
		return retval;
	}
}

