#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGetScrambleConstants64)(unsigned long long **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGetScrambleConstants64(unsigned long long **constants) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGetScrambleConstants64)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGetScrambleConstants64 = (curandStatus_t (*)(unsigned long long **)) dlsym(libwrapper_curand_handle, "wrapper_curandGetScrambleConstants64");
			fprintf(stderr, "wrapper_curandGetScrambleConstants64:%p\n", wrapper_curandGetScrambleConstants64);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGetScrambleConstants64():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGetScrambleConstants64(constants);
		return retval;
	}
}