#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGeneratePoisson)(curandGenerator_t, unsigned int *, size_t, double);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGeneratePoisson(curandGenerator_t generator, unsigned int *outputPtr, size_t n, double lambda) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGeneratePoisson)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGeneratePoisson = (curandStatus_t (*)(curandGenerator_t, unsigned int *, size_t, double)) dlsym(libwrapper_curand_handle, "wrapper_curandGeneratePoisson");
			fprintf(stderr, "wrapper_curandGeneratePoisson:%p\n", wrapper_curandGeneratePoisson);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGeneratePoisson():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGeneratePoisson(generator, outputPtr, n, lambda);
		return retval;
	}
}