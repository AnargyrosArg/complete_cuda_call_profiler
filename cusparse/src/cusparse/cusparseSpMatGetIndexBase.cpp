#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseSpMatGetIndexBase)(cusparseSpMatDescr_t, cusparseIndexBase_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseSpMatGetIndexBase(cusparseSpMatDescr_t spMatDescr, cusparseIndexBase_t *idxBase) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseSpMatGetIndexBase)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseSpMatGetIndexBase = (cusparseStatus_t (*)(cusparseSpMatDescr_t, cusparseIndexBase_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseSpMatGetIndexBase");
			fprintf(stderr, "wrapper_cusparseSpMatGetIndexBase:%p\n", wrapper_cusparseSpMatGetIndexBase);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseSpMatGetIndexBase():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseSpMatGetIndexBase(spMatDescr, idxBase);
		return retval;
	}
}