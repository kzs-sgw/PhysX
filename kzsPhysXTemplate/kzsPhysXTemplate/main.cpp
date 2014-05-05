#include "kzsGLmain.h"

int main( int argc, char *argv[] ){

	glObj = new kzsGLObject( argc, argv );

	atexit( callShutdown );

	glObj->runOpenGL( callDisplayFunc,
		              callResizeFunc,
					  callMouseFunc,
					  callMotionFunc,
					  callKeyboardFunc,
					  callIdleFunc,
					  /* Window Title = */ "no name" );

	delete glObj;

	return 0;
}