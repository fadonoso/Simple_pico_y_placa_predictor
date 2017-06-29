A sample ¨pico y placa¨ predictor for Ecuador. This project is an exercise to show a simple C++ code, with unit tests (Google unit test) and CMAKE
This sample program was tested in Ubuntu 16.04.
The ¨pico y placa¨ restriction can be changed by modifying the file config.cfg.
The only external required library is CMAKE.

##Building

~~~
mkdir build
cd build
cmake ..
make
~~~

##Running program

~~~
cd build/src
./picoPlaca
~~~

##Running unit test

~~~
cd build/test
./unit_tests
~~~


