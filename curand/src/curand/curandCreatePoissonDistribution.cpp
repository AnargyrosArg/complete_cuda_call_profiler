#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandCreatePoissonDistribution)(double, curandDiscreteDistribution_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandCreatePoissonDistribution(double lambda, curandDiscreteDistribution_t *discrete_distribution) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandCreatePoissonDistribution)
		{
			//fetch the original function addr using dlsym
			wrapper_curandCreatePoissonDistribution = (curandStatus_t (*)(double, curandDiscreteDistribution_t *)) dlsym(libwrapper_curand_handle, "wrapper_curandCreatePoissonDistribution");
			fprintf(stderr, "wrapper_curandCreatePoissonDistribution:%p\n", wrapper_curandCreatePoissonDistribution);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandCreatePoissonDistribution():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandCreatePoissonDistribution(lambda, discrete_distribution);
		return retval;
	}
}