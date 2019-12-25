#include "exception.hpp"

#include <cassert>

using std::string;

namespace openid
{
custom_exception::custom_exception(std::string const& _message)
    : runtime_error("wrong_data_exception - " + _message)
    , message(_message)
{}
custom_exception::custom_exception(custom_exception const& other) noexcept
    : runtime_error(other)
    , message(other.message)
{}
custom_exception& custom_exception::operator=(custom_exception const& other) noexcept
{
    dynamic_cast<runtime_error*>(this)->operator =(other);
    message = other.message;
    return *this;
}
custom_exception::~custom_exception() noexcept
{}

}// end of namespace publiqpp
