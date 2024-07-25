#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGenerateNormalDouble)(curandGenerator_t, double *, size_t, double, double);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGenerateNormalDouble(curandGenerator_t generator, double *outputPtr, size_t n, double mean, double stddev) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGenerateNormalDouble)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGenerateNormalDouble = (curandStatus_t (*)(curandGenerator_t, double *, size_t, double, double)) dlsym(libwrapper_curand_handle, "wrapper_curandGenerateNormalDouble");
			fprintf(stderr, "wrapper_curandGenerateNormalDouble:%p\n", wrapper_curandGenerateNormalDouble);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGenerateNormalDouble():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGenerateNormalDouble(generator, outputPtr, n, mean, stddev);
		return retval;
	}
}