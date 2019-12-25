#pragma once

#include "global.hpp"

#include <belt.pp/ilog.hpp>
#include <belt.pp/isocket.hpp>

#include <memory>

namespace openid
{
namespace detail
{
class server_internals;
}

class OPENIDSHARED_EXPORT server
{
public:
    server(beltpp::ip_address const& server_bind_to_address,
           beltpp::ilog* plogger_server);
    server(server&& other) noexcept;
    ~server();

    void wake();
    bool run();

private:
    std::unique_ptr<detail::server_internals> m_pimpl;
};

}

