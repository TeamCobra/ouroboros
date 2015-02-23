#ifndef _TEST_H_
#define _TEST_H_

#include "../ouroboros_server.h"

typedef void (*initialize_func)(ouroboros::ouroboros_server& aServer);

extern "C" void initialize(ouroboros::ouroboros_server& aServer);


#endif//_TEST_H_
