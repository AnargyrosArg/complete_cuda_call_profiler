#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGenerateUniformDouble)(curandGenerator_t, double *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGenerateUniformDouble(curandGenerator_t generator, double *outputPtr, size_t num) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGenerateUniformDouble)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGenerateUniformDouble = (curandStatus_t (*)(curandGenerator_t, double *, size_t)) dlsym(libwrapper_curand_handle, "wrapper_curandGenerateUniformDouble");
			fprintf(stderr, "wrapper_curandGenerateUniformDouble:%p\n", wrapper_curandGenerateUniformDouble);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGenerateUniformDouble():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGenerateUniformDouble(generator, outputPtr, num);
		return retval;
	}
}