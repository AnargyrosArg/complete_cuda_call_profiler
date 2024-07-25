#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGenerateBinomialMethod)(curandGenerator_t, unsigned int *, size_t, unsigned int, double, curandMethod_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGenerateBinomialMethod(curandGenerator_t generator, unsigned int *outputPtr, size_t num, unsigned int n, double p, curandMethod_t method) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGenerateBinomialMethod)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGenerateBinomialMethod = (curandStatus_t (*)(curandGenerator_t, unsigned int *, size_t, unsigned int, double, curandMethod_t)) dlsym(libwrapper_curand_handle, "wrapper_curandGenerateBinomialMethod");
			fprintf(stderr, "wrapper_curandGenerateBinomialMethod:%p\n", wrapper_curandGenerateBinomialMethod);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGenerateBinomialMethod():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGenerateBinomialMethod(generator, outputPtr, num, n, p, method);
		return retval;
	}
}