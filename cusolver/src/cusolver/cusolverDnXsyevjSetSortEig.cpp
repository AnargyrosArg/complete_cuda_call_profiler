#include <cusolverDn.h>
#include <dlfcn.h>
#include <iostream>
cusolverStatus_t (*wrapper_cusolverDnXsyevjSetSortEig)(syevjInfo_t, int);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusolver_handle;
extern "C"
{
	cusolverStatus_t cusolverDnXsyevjSetSortEig(syevjInfo_t info, int sort_eig) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusolver_handle == NULL){
			libwrapper_cusolver_handle = dlopen("libwrapper_cusolver.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusolverDnXsyevjSetSortEig)
		{
			//fetch the original function addr using dlsym
			wrapper_cusolverDnXsyevjSetSortEig = (cusolverStatus_t (*)(syevjInfo_t, int)) dlsym(libwrapper_cusolver_handle, "wrapper_cusolverDnXsyevjSetSortEig");
			fprintf(stderr, "wrapper_cusolverDnXsyevjSetSortEig:%p\n", wrapper_cusolverDnXsyevjSetSortEig);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusolverDnXsyevjSetSortEig():%s\n", __dlerror);
			fflush(stderr);
		}
		cusolverStatus_t retval = wrapper_cusolverDnXsyevjSetSortEig(info, sort_eig);
		return retval;
	}
}