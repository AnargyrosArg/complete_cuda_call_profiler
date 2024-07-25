#include <cusparse.h>
#include <dlfcn.h>
#include <iostream>
cusparseStatus_t (*wrapper_cusparseCreateCsc)(cusparseSpMatDescr_t *, int64_t, int64_t, int64_t, void *, void *, void *, cusparseIndexType_t, cusparseIndexType_t, cusparseIndexBase_t, cudaDataType);
//handle to the libwrapper library, used to fetch original functions with dlsym
extern void* libwrapper_cusparse_handle;
extern "C"
{
	cusparseStatus_t cusparseCreateCsc(cusparseSpMatDescr_t *spMatDescr, int64_t rows, int64_t cols, int64_t nnz, void *cscColOffsets, void *cscRowInd, void *cscValues, cusparseIndexType_t cscColOffsetsType, cusparseIndexType_t cscRowIndType, cusparseIndexBase_t idxBase, cudaDataType valueType) {
		char* __dlerror;
		//this call clears any previous errors
		dlerror();
		if(libwrapper_cusparse_handle == NULL){
			libwrapper_cusparse_handle = dlopen("libwrapper_cusparse.so", RTLD_LAZY | RTLD_DEEPBIND);
		}
		if (!wrapper_cusparseCreateCsc)
		{
			//fetch the original function addr using dlsym
			wrapper_cusparseCreateCsc = (cusparseStatus_t (*)(cusparseSpMatDescr_t *, int64_t, int64_t, int64_t, void *, void *, void *, cusparseIndexType_t, cusparseIndexType_t, cusparseIndexBase_t, cudaDataType)) dlsym(libwrapper_cusparse_handle, "wrapper_cusparseCreateCsc");
			fprintf(stderr, "wrapper_cusparseCreateCsc:%p\n", wrapper_cusparseCreateCsc);
		}
		__dlerror = dlerror();
		if(__dlerror){
			fprintf(stderr, "dlsym error for function cusparseCreateCsc():%s\n", __dlerror);
			fflush(stderr);
		}
		cusparseStatus_t retval = wrapper_cusparseCreateCsc(spMatDescr, rows, cols, nnz, cscColOffsets, cscRowInd, cscValues, cscColOffsetsType, cscRowIndType, idxBase, valueType);
		return retval;
	}
}