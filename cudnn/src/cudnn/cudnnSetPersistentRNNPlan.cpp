#include <cudnn_adv_infer.h>
#include <dlfcn.h>
#include <iostream>
cudnnStatus_t (*wrapper_cudnnSetPersistentRNNPlan)(cudnnRNNDescriptor_t, cudnnPersistentRNNPlan_t);
//handle to the libwrapper library, used to fetch original fntions with dlsym
extern void* libwrapper_cudnn_handle;
extern "C"
{
	cudnnStatus_t cudnnSetPersistentRNNPlan(cudnnRNNDescriptor_t rnnDesc, cudnnPersistentRNNPlan_t plan){
		char* __dlerror;
        #ifdef PRINT_TRACE
    	fprintf(stderr,"%s()\n",__func__);
    	#endif
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cudnn_handle == NULL){
			libwrapper_cudnn_handle = dlopen("libwrapper_cudnn.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cudnnSetPersistentRNNPlan)
		{
			//fetch the original fntion addr using dlsym
			wrapper_cudnnSetPersistentRNNPlan = (cudnnStatus_t (*)(cudnnRNNDescriptor_t, cudnnPersistentRNNPlan_t)) dlsym(libwrapper_cudnn_handle, "wrapper_cudnnSetPersistentRNNPlan");
			fprintf(stderr, "wrapper_cudnnSetPersistentRNNPlan:%p\n", wrapper_cudnnSetPersistentRNNPlan);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for fntion cudnnSetPersistentRNNPlan():%s\n", __dlerror);
			fflush(stderr);
		}
		cudnnStatus_t retval = wrapper_cudnnSetPersistentRNNPlan(rnnDesc, plan);
		return retval;
	}
}

