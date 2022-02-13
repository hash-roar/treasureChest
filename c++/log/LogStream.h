#ifndef _LOG_STREAM_H_
#define _LOG_STREAM_H_

#include "../base/Types.h"
#include "../base/noncopyable.h"
#include <cstddef>
#include <string.h>
#include <string_view>
#include <strings.h>

namespace Log {
namespace detail {

  const int kSmallBuffer = 4000;
  const int kLargeBuffer = 4000 * 1000;

  template <int SIZE>
  class FixedBuffer : base::noncopyable {
public:
    FixedBuffer()
        : cur_(data_)
    {
    }
    ~FixedBuffer() { }

    void append(const char* buf, size_t len)
    {
      if (base::implicit_cast<size_t>(avail()) > len) {
        memcpy(data_, buf, len);
        cur_ += len;
      }
    };

    const char* data() { return data_; }
    char* current() { return cur_; }

    int length() const { return static_cast<int>(cur_ - data_); }
    void add(size_t len) { cur_ += len; }

    void reset() { cur_ = data_; }
    void bzero() { bzero(data_, sizeof(data_)); }

    //??
    std::string_view to_string_view() const { return std::string_view(data_, length()); }

private:
    const char* end() const { return data_ + sizeof data_; }
    char* cur_;
    int avail() { return static_cast<int>(cur_ - data_); }
    char data_[SIZE];
  };

} // detail

class LogStream : base::noncopyable {
  typedef LogStream self;

  public:
  typedef detail::FixedBuffer<detail::kSmallBuffer> Buffer;

  self& operator<<(bool v)
  {
    buffer_.append(v ? "1" : "0", 1);
    return *this;
  }

  self& operator<<(short);
  self& operator<<(unsigned short);
  self& operator<<(int);
  self& operator<<(unsigned int);
  self& operator<<(long);
  self& operator<<(unsigned long);
  self& operator<<(long long);
  self& operator<<(unsigned long long);

  self& operator<<(const void*);

  self& operator<<(float v)
  {
    *this << static_cast<double>(v);
    return *this;
  };

  self& operator<<(double);

  self& operator<<(char v)
  {
    buffer_.append(&v, 1);
    return *this;
  }

  self& operator<<(const char* str)
  {
    if (str) {
      buffer_.append(str, sizeof(str));
    } else {
      buffer_.append("(null)", 6);
    }
    return *this;
  }
  // ???
  //self& operator<<(const unsigned char* str)
  //{
  //return operator<<(reinterpret_cast<const char*>(str));
  //}
  self& operator<<(std::string_view strv)
  {
    buffer_.append(strv.data(), strv.size());
    return *this;
  }

  self& operator<<(const Buffer& v)
  {
    *this << v.to_string_view();
    return *this;
  }

  void append(const char* data, int len) { buffer_.append(data, len); }
  const Buffer& buffer() { return buffer_; }
  void resetBuffer() { buffer_.reset(); }

  private:
  Buffer buffer_;
};

}

#endif
