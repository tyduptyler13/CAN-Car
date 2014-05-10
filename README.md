CANHost
=======

A project for connecting CAN components to a web based GUI.

Dependencies
------------
* Python 2.7
* Node.js
* Any popular C compiler for your system. (MSBUILD, gcc, clang, etc)
  + Make (linux only)

Building
--------

__Linux__:
  * Build and install the linuxcan with make, see their readme for details.

__Windows__:
  * The build is already available as part of our repo. (Headers and libraries only)

__All__:
Run `npm install` after all dependencies are built. It will complain if you are missing something.

Running
-------
Run `npm start` for this interface to start. Chrome app must be started separately for now.

Details on the app later.