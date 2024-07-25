#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGenerate)(curandGenerator_t, unsigned int *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGenerate(curandGenerator_t generator, unsigned int *outputPtr, size_t num) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGenerate)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGenerate = (curandStatus_t (*)(curandGenerator_t, unsigned int *, size_t)) dlsym(libwrapper_curand_handle, "wrapper_curandGenerate");
			fprintf(stderr, "wrapper_curandGenerate:%p\n", wrapper_curandGenerate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGenerate():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGenerate(generator, outputPtr, num);
		return retval;
	}
}