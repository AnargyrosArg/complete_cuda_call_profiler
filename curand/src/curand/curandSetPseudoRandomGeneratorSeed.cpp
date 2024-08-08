#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandSetPseudoRandomGeneratorSeed)(curandGenerator_t, unsigned long long);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandSetPseudoRandomGeneratorSeed(curandGenerator_t generator, unsigned long long seed) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandSetPseudoRandomGeneratorSeed)
		{
			//fetch the original function addr using dlsym
			wrapper_curandSetPseudoRandomGeneratorSeed = (curandStatus_t (*)(curandGenerator_t, unsigned long long)) dlsym(libwrapper_curand_handle, "wrapper_curandSetPseudoRandomGeneratorSeed");
			fprintf(stderr, "wrapper_curandSetPseudoRandomGeneratorSeed:%p\n", wrapper_curandSetPseudoRandomGeneratorSeed);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandSetPseudoRandomGeneratorSeed():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandSetPseudoRandomGeneratorSeed(generator, seed);
		return retval;
	}
}