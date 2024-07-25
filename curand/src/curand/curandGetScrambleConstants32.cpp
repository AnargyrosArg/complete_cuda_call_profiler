#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGetScrambleConstants32)(unsigned int **);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGetScrambleConstants32(unsigned int **constants) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGetScrambleConstants32)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGetScrambleConstants32 = (curandStatus_t (*)(unsigned int **)) dlsym(libwrapper_curand_handle, "wrapper_curandGetScrambleConstants32");
			fprintf(stderr, "wrapper_curandGetScrambleConstants32:%p\n", wrapper_curandGetScrambleConstants32);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGetScrambleConstants32():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGetScrambleConstants32(constants);
		return retval;
	}
}