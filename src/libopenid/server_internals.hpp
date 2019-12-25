#pragma once

#include "http.hpp"

#include <belt.pp/event.hpp>
#include <belt.pp/socket.hpp>
#include <belt.pp/packet.hpp>
#include <belt.pp/utility.hpp>
#include <belt.pp/scope_helper.hpp>
#include <belt.pp/message_global.hpp>
#include <belt.pp/timer.hpp>
#include <belt.pp/ilog.hpp>

#include <mesh.pp/cryptoutility.hpp>
#include <mesh.pp/sessionutility.hpp>

#include <boost/filesystem/path.hpp>

#include <chrono>
#include <memory>

using namespace OpenIDMessage;
namespace filesystem = boost::filesystem;

using beltpp::ip_address;
using beltpp::ip_destination;
using beltpp::socket;
using beltpp::packet;
using peer_id = socket::peer_id;

using std::string;
using std::unique_ptr;

namespace chrono = std::chrono;
using chrono::system_clock;
using chrono::steady_clock;

namespace openid
{
using server_sf = beltpp::socket_family_t<&http::message_list_load<&OpenIDMessage::message_list_load>>;

namespace detail
{
class server_internals
{
public:
    server_internals(ip_address const& _server_bind_to_address,
                     beltpp::ilog* _plogger_server)
        : plogger_server(_plogger_server)
        , ptr_eh(new beltpp::event_handler())
        , ptr_server_socket(new beltpp::socket(
                                beltpp::getsocket<server_sf>(*ptr_eh)
                                ))
        , server_bind_to_address(_server_bind_to_address)
    {
        ptr_eh->set_timer(chrono::seconds(30));

        if (false == server_bind_to_address.local.empty())
            ptr_server_socket->listen(server_bind_to_address);

        ptr_eh->add(*ptr_server_socket);
    }

    void writeln_server(string const& value)
    {
        if (plogger_server)
            plogger_server->message(value);
    }

    void writeln_server_warning(string const& value)
    {
        if (plogger_server)
            plogger_server->warning(value);
    }

    beltpp::ilog* plogger_server;
    unique_ptr<beltpp::event_handler> ptr_eh;
    unique_ptr<beltpp::socket> ptr_server_socket;
    beltpp::ip_address server_bind_to_address;
};

}
}
