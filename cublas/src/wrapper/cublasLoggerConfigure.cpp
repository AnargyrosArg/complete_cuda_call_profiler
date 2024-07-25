#include <cublas_v2.h>
#include <dlfcn.h>
#include <iostream>
//func_wrapper template
extern "C"
cublasStatus_t wrapper_cublasLoggerConfigure(int logIsOn, int logToStdOut, int logToStdErr, const char *logFileName)
{
	cublasStatus_t retval = cublasLoggerConfigure(logIsOn, logToStdOut, logToStdErr, logFileName);
	return retval;
}