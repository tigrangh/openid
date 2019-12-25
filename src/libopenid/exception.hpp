#pragma once

#include "global.hpp"

#include <exception>
#include <string>
#include <stdexcept>

namespace openid
{
class OPENIDSHARED_EXPORT custom_exception : public std::runtime_error
{
public:
    explicit custom_exception(std::string const& _message);

    custom_exception(custom_exception const&) noexcept;
    custom_exception& operator=(custom_exception const&) noexcept;

    virtual ~custom_exception() noexcept;

    std::string message;
};
}// end of namespace publiqpp
