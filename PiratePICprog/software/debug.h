#ifndef DEBUG_h_
#define DEBUG_h_

#include <stdint.h>

enum {
	DEBUG_OFF = 0,
	DEBUG_ERROR,
	DEBUG_WARN,
	DEBUG_INFO,
	DEBUG_VERBOSE
};

extern int debug_level;

#define dbg_(level, args...) \
	do { \
		if (debug_level >= level) { \
			fprintf(stderr, "%s:%i %s(): ", __FILE__, __LINE__, __func__); \
			fprintf(stderr, args); \
		} \
	} while (0)

#define dbg_buf_(level, buffer, length) \
	do { \
		if (debug_level >= level) { \
			fprintf(stderr, "%s:%i %s(): ", __FILE__, __LINE__, __func__); \
			for (int i = 0; i < length; i++) { \
				fprintf(stderr, "%02x ", (uint8_t)buffer[i]); \
			} \
			fprintf(stderr, "\n"); \
		} \
	} while (0)

#define dbg(args...)              dbg_(DEBUG_OFF, args)
#define dbg_err(args...)          dbg_(DEBUG_ERROR, args)
#define dbg_warn(args...)         dbg_(DEBUG_WARN, args)
#define dbg_info(args...)         dbg_(DEBUG_INFO, args)
#define dbg_verbose(args...)      dbg_(DEBUG_VERBOSE, args)

#define dbg_buf_info(buf, len)    dbg_buf_(DEBUG_INFO, (buf), (len))
#define dbg_buf_verbose(buf, len) dbg_buf_(DEBUG_VERBOSE, (buf), (len))

#endif
