#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGetDirectionVectors32)(curandDirectionVectors32_t **, curandDirectionVectorSet_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGetDirectionVectors32(curandDirectionVectors32_t *vectors[], curandDirectionVectorSet_t set) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGetDirectionVectors32)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGetDirectionVectors32 = (curandStatus_t (*)(curandDirectionVectors32_t **, curandDirectionVectorSet_t)) dlsym(libwrapper_curand_handle, "wrapper_curandGetDirectionVectors32");
			fprintf(stderr, "wrapper_curandGetDirectionVectors32:%p\n", wrapper_curandGetDirectionVectors32);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGetDirectionVectors32():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGetDirectionVectors32(vectors, set);
		return retval;
	}
}