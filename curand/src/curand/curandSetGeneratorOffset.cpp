#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandSetGeneratorOffset)(curandGenerator_t, unsigned long long);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandSetGeneratorOffset(curandGenerator_t generator, unsigned long long offset) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandSetGeneratorOffset)
		{
			//fetch the original function addr using dlsym
			wrapper_curandSetGeneratorOffset = (curandStatus_t (*)(curandGenerator_t, unsigned long long)) dlsym(libwrapper_curand_handle, "wrapper_curandSetGeneratorOffset");
			fprintf(stderr, "wrapper_curandSetGeneratorOffset:%p\n", wrapper_curandSetGeneratorOffset);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandSetGeneratorOffset():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandSetGeneratorOffset(generator, offset);
		return retval;
	}
}