#include <curand.h>
#include <dlfcn.h>
#include <iostream>
curandStatus_t (*wrapper_curandGetDirectionVectors64)(curandDirectionVectors64_t **, curandDirectionVectorSet_t);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_curand_handle;
extern "C"
{
	curandStatus_t curandGetDirectionVectors64(curandDirectionVectors64_t *vectors[], curandDirectionVectorSet_t set) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_curand_handle == NULL){
			libwrapper_curand_handle = dlopen("libwrapper_curand.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_curandGetDirectionVectors64)
		{
			//fetch the original function addr using dlsym
			wrapper_curandGetDirectionVectors64 = (curandStatus_t (*)(curandDirectionVectors64_t **, curandDirectionVectorSet_t)) dlsym(libwrapper_curand_handle, "wrapper_curandGetDirectionVectors64");
			fprintf(stderr, "wrapper_curandGetDirectionVectors64:%p\n", wrapper_curandGetDirectionVectors64);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function curandGetDirectionVectors64():%s\n", __dlerror);
			fflush(stderr);
		}
		curandStatus_t retval = wrapper_curandGetDirectionVectors64(vectors, set);
		return retval;
	}
}