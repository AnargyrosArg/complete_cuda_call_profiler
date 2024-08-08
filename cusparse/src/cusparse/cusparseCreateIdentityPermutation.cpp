#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreateIdentityPermutation)(cusparseHandle_t, int, int *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreateIdentityPermutation(cusparseHandle_t handle, int n, int *p) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreateIdentityPermutation)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreateIdentityPermutation = (cusparseStatus_t (*)(cusparseHandle_t, int, int *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreateIdentityPermutation");
			fprintf(stderr, "wrapper_cusparseCreateIdentityPermutation:%p\n", wrapper_cusparseCreateIdentityPermutation);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreateIdentityPermutation():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreateIdentityPermutation(handle, n, p);
		return retval;
	}
}