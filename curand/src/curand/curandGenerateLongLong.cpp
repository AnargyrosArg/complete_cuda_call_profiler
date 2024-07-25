#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGenerateLongLong)(curandGenerator_t, unsigned long long *, size_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGenerateLongLong(curandGenerator_t generator, unsigned long long *outputPtr, size_t num) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGenerateLongLong)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGenerateLongLong = (curandStatus_t (*)(curandGenerator_t, unsigned long long *, size_t)) dlsym(libwrapper_curand_handle, "wrapper_curandGenerateLongLong");
			fprintf(stderr, "wrapper_curandGenerateLongLong:%p\n", wrapper_curandGenerateLongLong);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGenerateLongLong():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGenerateLongLong(generator, outputPtr, num);
		return retval;
	}
}