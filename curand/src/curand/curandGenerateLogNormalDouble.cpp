#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGenerateLogNormalDouble)(curandGenerator_t, double *, size_t, double, double);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGenerateLogNormalDouble(curandGenerator_t generator, double *outputPtr, size_t n, double mean, double stddev) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGenerateLogNormalDouble)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGenerateLogNormalDouble = (curandStatus_t (*)(curandGenerator_t, double *, size_t, double, double)) dlsym(libwrapper_curand_handle, "wrapper_curandGenerateLogNormalDouble");
			fprintf(stderr, "wrapper_curandGenerateLogNormalDouble:%p\n", wrapper_curandGenerateLogNormalDouble);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGenerateLogNormalDouble():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGenerateLogNormalDouble(generator, outputPtr, n, mean, stddev);
		return retval;
	}
}