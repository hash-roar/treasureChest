
#include "Logging.h"
#include <bits/types/time_t.h>
#include <cstring>

__thread char t_errnobuf[512];
__thread char t_time[64];
__thread time_t t_lastSecond;

const char* strerror_tl(int saveError)
{
  return strerror_r(saveError,t_errnobuf,sizeof(t_errnobuf));
}


