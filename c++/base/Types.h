#ifndef _BASE_TYPE_H_
#define _BASE_TYPE_H_

namespace base {

template <typename To, typename From>
inline To implicit_cast(From const& f)
{
  return f;
}
}

#endif
