#ifndef ERR_H
#define ERR_H
/* The state of the drone, with respect to errors. Each bit is a unique error. */
 unsigned long DRONE_ERROR = 0;
 
 /* According to Arduino Documentation, sizeof(long) == 32. So 32 bits of DRONE_ERROR are usable. */
 
 /* Reserved error types. Allowable in the open range (0, 32)*/
 const short ERROR_TYPE_BAROMETER = 1;
 const short ERROR_TYPE_FLIGHT_CONTROL = 2;
 const short ERROR_TYPE_MOTOR = 3;
 const short ERROR_TYPE_POWER = 4;
 const short ERROR_TYPE_PID = 5;
 #endif
