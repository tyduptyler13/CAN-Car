/**
 * 
 */

var test = require('bindings')('CNI');
var IO = require('socket.io').listen(8001);

var canStuff = require('CANInterface.cpp');


