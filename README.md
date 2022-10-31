Implementation of Prototype design pattern on simple example of detector creation,
that is described with name, thickness and geometry, that is theta angle and distance
from the target.
Prototype is created using struct DetectorFactory, but also using boost serialize
library. To test this, simple clone lambda function was created in main.cpp,
that checks serialize library.

CMake is used for project build. Doxygen is used for project documentation.


To build project and project documentation, go to root directory:
<pre>
$ cd root
$ mkdir build
$ cd build
$ cmake ..
$ make
$ make doc
</pre>
To check valgrind: valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./prototype
