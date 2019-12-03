/**
 * Macros for tracing.
 */

#ifndef __trace_h
#define __trace_h

/* Trace macro for debugging output */
#ifdef DEBUG_OUTPUT
#define trace(a) { Serial.print(a); }
#define tracenl(a) { Serial.print(a); Serial.print("\n"); }
#else
#define trace(a)
#define tracenl(a)
#endif

#endif
