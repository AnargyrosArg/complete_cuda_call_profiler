#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnIRSInfosCreate)(cusolverDnIRSInfos_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnIRSInfosCreate(cusolverDnIRSInfos_t *infos_ptr) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnIRSInfosCreate)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnIRSInfosCreate = (cusolverStatus_t (*)(cusolverDnIRSInfos_t *)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnIRSInfosCreate");
			fprintf(stderr, "wrapper_cusolverDnIRSInfosCreate:%p\n", wrapper_cusolverDnIRSInfosCreate);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnIRSInfosCreate():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnIRSInfosCreate(infos_ptr);
		return retval;
	}
}