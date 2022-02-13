#ifndef _BASE_NONCOPY_H_
#define _BASE_NONCOPY_H_

namespace base {
class noncopyable {
  public:
  noncopyable(const noncopyable&) = delete;
  void operator=(const noncopyable&) = delete;

  protected:
  noncopyable() = default;
  ~noncopyable() = default;
};
}

#endif
