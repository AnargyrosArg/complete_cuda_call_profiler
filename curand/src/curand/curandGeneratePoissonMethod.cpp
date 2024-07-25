#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGeneratePoissonMethod)(curandGenerator_t, unsigned int *, size_t, double, curandMethod_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGeneratePoissonMethod(curandGenerator_t generator, unsigned int *outputPtr, size_t n, double lambda, curandMethod_t method) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGeneratePoissonMethod)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGeneratePoissonMethod = (curandStatus_t (*)(curandGenerator_t, unsigned int *, size_t, double, curandMethod_t)) dlsym(libwrapper_curand_handle, "wrapper_curandGeneratePoissonMethod");
			fprintf(stderr, "wrapper_curandGeneratePoissonMethod:%p\n", wrapper_curandGeneratePoissonMethod);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGeneratePoissonMethod():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGeneratePoissonMethod(generator, outputPtr, n, lambda, method);
		return retval;
	}
}