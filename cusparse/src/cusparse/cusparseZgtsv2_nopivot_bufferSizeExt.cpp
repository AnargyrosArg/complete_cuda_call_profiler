#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseZgtsv2_nopivot_bufferSizeExt)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, int, size_t *);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseZgtsv2_nopivot_bufferSizeExt(cusparseHandle_t handle, int m, int n, const cuDoubleComplex *dl, const cuDoubleComplex *d, const cuDoubleComplex *du, const cuDoubleComplex *B, int ldb, size_t *bufferSizeInBytes) {
		#ifdef PRINT_TRACE
        fprintf(stderr,"%s()\n",__func__);
        #endif 
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseZgtsv2_nopivot_bufferSizeExt)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseZgtsv2_nopivot_bufferSizeExt = (cusparseStatus_t (*)(cusparseHandle_t, int, int, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, const cuDoubleComplex *, int, size_t *)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseZgtsv2_nopivot_bufferSizeExt");
			fprintf(stderr, "wrapper_cusparseZgtsv2_nopivot_bufferSizeExt:%p\n", wrapper_cusparseZgtsv2_nopivot_bufferSizeExt);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseZgtsv2_nopivot_bufferSizeExt():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseZgtsv2_nopivot_bufferSizeExt(handle, m, n, dl, d, du, B, ldb, bufferSizeInBytes);
		return retval;
	}
}