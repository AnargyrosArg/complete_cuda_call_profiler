#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandDestroyGenerator)(curandGenerator_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandDestroyGenerator(curandGenerator_t generator) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandDestroyGenerator)
		{
			//fetch the original function addr using dlsym
			wrapper_curandDestroyGenerator = (curandStatus_t (*)(curandGenerator_t)) dlsym(libwrapper_curand_handle, "wrapper_curandDestroyGenerator");
			fprintf(stderr, "wrapper_curandDestroyGenerator:%p\n", wrapper_curandDestroyGenerator);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandDestroyGenerator():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandDestroyGenerator(generator);
		return retval;
	}
}