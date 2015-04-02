#include <server/plugin.h>
#include <Python.h>

extern "C" bool plugin_entry(ouroboros::ouroboros_server& server)
{
	//Py_SetProgramName(name.c_str());  /* optional but recommended */
	Py_Initialize();
	PyRun_SimpleString("from time import time,ctime\n"
		"print('Today is', ctime(time()))\n");
	Py_Finalize();
	return true;
}
