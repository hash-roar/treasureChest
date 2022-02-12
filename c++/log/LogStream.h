#ifndef _LOG_STREAM_H_
#define _LOG_STREAM_H_

#include "../base/noncopyable.h"
#include <cstddef>

namespace Log {
template <int SIZE>
class FixedBuffer : noncopyable {
  public:
  FixedBuffer()
      : cur_(data_)
  {
  }
  ~FixedBuffer() { }

  void append(const char* buf, size_t len);

  private:
  const char* end() const { return data_ + sizeof data_; }
  char* cur_;
  char data_[SIZE];
};
}

#endif
