#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandCreateGeneratorHost)(curandGenerator_t *, curandRngType_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandCreateGeneratorHost(curandGenerator_t *generator, curandRngType_t rng_type) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandCreateGeneratorHost)
		{
			//fetch the original function addr using dlsym
			wrapper_curandCreateGeneratorHost = (curandStatus_t (*)(curandGenerator_t *, curandRngType_t)) dlsym(libwrapper_curand_handle, "wrapper_curandCreateGeneratorHost");
			fprintf(stderr, "wrapper_curandCreateGeneratorHost:%p\n", wrapper_curandCreateGeneratorHost);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandCreateGeneratorHost():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandCreateGeneratorHost(generator, rng_type);
		return retval;
	}
}