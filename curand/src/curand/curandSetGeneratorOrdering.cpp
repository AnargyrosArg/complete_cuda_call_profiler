#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandSetGeneratorOrdering)(curandGenerator_t, curandOrdering_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandSetGeneratorOrdering(curandGenerator_t generator, curandOrdering_t order) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandSetGeneratorOrdering)
		{
			//fetch the original function addr using dlsym
			wrapper_curandSetGeneratorOrdering = (curandStatus_t (*)(curandGenerator_t, curandOrdering_t)) dlsym(libwrapper_curand_handle, "wrapper_curandSetGeneratorOrdering");
			fprintf(stderr, "wrapper_curandSetGeneratorOrdering:%p\n", wrapper_curandSetGeneratorOrdering);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandSetGeneratorOrdering():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandSetGeneratorOrdering(generator, order);
		return retval;
	}
}