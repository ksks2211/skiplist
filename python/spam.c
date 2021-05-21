#include "Python.h"

static PyObject*
spam_strlen(PyObject* self, PyObject* args) {
	char* str;
	int len;
	if (!PyArg_ParseTuple(args, "s", &str))
		return NULL;
	len = strlen(str);
	return Py_BuildValue("i", len);
}

// 4, 모듈에 등록할 함수에 대한 정의담은 배열 __dict__ 속성에 등록되는 함수
static PyMethodDef SpamMethods[] = {
	// 함수이름, 실행될 함수포인터, 파이썬에서 호출할떄 인자를 어떤 자료형으로 받는지 결정하는상수, 함수설명
	// METH_VARARGS 는 튜플형식 => PyArg_ParseTuple 함수로 인자처리
	// METH_KEYWORDS 는 사전형식
	{"strlen",spam_strlen,METH_VARARGS,"count a string length."},
	{NULL,NULL,0,NULL}
};


// 3, 생성할 모듈의 정보가 담긴 구조체. 
static struct PyModuleDef spammodule = {
	PyModuleDef_HEAD_INIT,
	"spam",
	"It is test module.",
	-1,SpamMethods  // 마지막 매개변수는 모듈에 등록할 함수에 대한 정의를 담고있는 배열을 가리킨다.
};

// 1,파이썬 인터프리터에서 호출하면 PyInit_spam() 함수를 실행
PyMODINIT_FUNC PyInit_spam(void) {

	//  2,spammodule을 찾고해서 모듈을 생성, 생성된 모듈객체의 포인터를 반환, 에러발생시 NULL
	return PyModule_Create(&spammodule);
};

