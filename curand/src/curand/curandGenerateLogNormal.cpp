#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGenerateLogNormal)(curandGenerator_t, float *, size_t, float, float);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGenerateLogNormal(curandGenerator_t generator, float *outputPtr, size_t n, float mean, float stddev) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGenerateLogNormal)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGenerateLogNormal = (curandStatus_t (*)(curandGenerator_t, float *, size_t, float, float)) dlsym(libwrapper_curand_handle, "wrapper_curandGenerateLogNormal");
			fprintf(stderr, "wrapper_curandGenerateLogNormal:%p\n", wrapper_curandGenerateLogNormal);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGenerateLogNormal():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGenerateLogNormal(generator, outputPtr, n, mean, stddev);
		return retval;
	}
}