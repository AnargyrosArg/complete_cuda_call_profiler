#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandSetQuasiRandomGeneratorDimensions)(curandGenerator_t, unsigned int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandSetQuasiRandomGeneratorDimensions(curandGenerator_t generator, unsigned int num_dimensions) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandSetQuasiRandomGeneratorDimensions)
		{
			//fetch the original function addr using dlsym
			wrapper_curandSetQuasiRandomGeneratorDimensions = (curandStatus_t (*)(curandGenerator_t, unsigned int)) dlsym(libwrapper_curand_handle, "wrapper_curandSetQuasiRandomGeneratorDimensions");
			fprintf(stderr, "wrapper_curandSetQuasiRandomGeneratorDimensions:%p\n", wrapper_curandSetQuasiRandomGeneratorDimensions);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandSetQuasiRandomGeneratorDimensions():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandSetQuasiRandomGeneratorDimensions(generator, num_dimensions);
		return retval;
	}
}