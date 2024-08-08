#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandDestroyDistribution)(curandDiscreteDistribution_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandDestroyDistribution(curandDiscreteDistribution_t discrete_distribution) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandDestroyDistribution)
		{
			//fetch the original function addr using dlsym
			wrapper_curandDestroyDistribution = (curandStatus_t (*)(curandDiscreteDistribution_t)) dlsym(libwrapper_curand_handle, "wrapper_curandDestroyDistribution");
			fprintf(stderr, "wrapper_curandDestroyDistribution:%p\n", wrapper_curandDestroyDistribution);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandDestroyDistribution():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandDestroyDistribution(discrete_distribution);
		return retval;
	}
}