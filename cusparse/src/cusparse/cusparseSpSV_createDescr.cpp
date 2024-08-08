#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpSV_createDescr)(cusparseSpSVDescr_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpSV_createDescr(cusparseSpSVDescr_t *descr) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpSV_createDescr)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpSV_createDescr = (cusparseStatus_t (*)(cusparseSpSVDescr_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpSV_createDescr");
			fprintf(stderr, "wrapper_cusparseSpSV_createDescr:%p\n", wrapper_cusparseSpSV_createDescr);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpSV_createDescr():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpSV_createDescr(descr);
		return retval;
	}
}