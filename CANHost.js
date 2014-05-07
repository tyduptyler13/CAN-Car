/**
 * 
 */

var CI = require('bindings')('CANInterface');
var IO = require('socket.io').listen(8001);

//TODO

console.log(CI.testChannel());

