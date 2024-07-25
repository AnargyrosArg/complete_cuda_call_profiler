#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGenerateUniform)(curandGenerator_t, float *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGenerateUniform(curandGenerator_t generator, float *outputPtr, size_t num) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGenerateUniform)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGenerateUniform = (curandStatus_t (*)(curandGenerator_t, float *, size_t)) dlsym(libwrapper_curand_handle, "wrapper_curandGenerateUniform");
			fprintf(stderr, "wrapper_curandGenerateUniform:%p\n", wrapper_curandGenerateUniform);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGenerateUniform():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGenerateUniform(generator, outputPtr, num);
		return retval;
	}
}