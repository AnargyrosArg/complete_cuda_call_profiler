#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandCreateGenerator)(curandGenerator_t *, curandRngType_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandCreateGenerator(curandGenerator_t *generator, curandRngType_t rng_type) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandCreateGenerator)
		{
			//fetch the original function addr using dlsym
			wrapper_curandCreateGenerator = (curandStatus_t (*)(curandGenerator_t *, curandRngType_t)) dlsym(libwrapper_curand_handle, "wrapper_curandCreateGenerator");
			fprintf(stderr, "wrapper_curandCreateGenerator:%p\n", wrapper_curandCreateGenerator);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandCreateGenerator():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandCreateGenerator(generator, rng_type);
		return retval;
	}
}