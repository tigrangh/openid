#include "server.hpp"
#include "exception.hpp"
#include "server_internals.hpp"

#include <vector>
#include <string>
#include <memory>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <exception>

using beltpp::packet;
using beltpp::socket;
using beltpp::ip_address;
using peer_id = socket::peer_id;


namespace chrono = std::chrono;
using chrono::system_clock;

using std::pair;
using std::string;
using std::vector;
using std::unique_ptr;
using std::unordered_set;

namespace openid
{
server::server(ip_address const& server_bind_to_address,
               beltpp::ilog* plogger_server)
    : m_pimpl(new detail::server_internals(server_bind_to_address,
                                           plogger_server))
{}

server::server(server&&) noexcept = default;

server::~server() = default;

void server::wake()
{
    m_pimpl->ptr_eh->wake();
}

bool server::run()
{
    bool code = true;

    unordered_set<beltpp::ievent_item const*> wait_sockets;

    auto wait_result = m_pimpl->ptr_eh->wait(wait_sockets);

    if (wait_result & beltpp::event_handler::event)
    {
        for (auto& pevent_item : wait_sockets)
        {
            beltpp::socket::peer_id peerid;

            beltpp::isocket* psk = nullptr;
            if (pevent_item == m_pimpl->ptr_server_socket.get())
                psk = m_pimpl->ptr_server_socket.get();

            if (nullptr == psk)
                throw std::logic_error("event handler behavior");

            beltpp::socket::packets received_packets;
            if (psk != nullptr)
                received_packets = psk->receive(peerid);

            for (auto& received_packet : received_packets)
            {
            try
            {
                switch (received_packet.type())
                {
                case beltpp::isocket_join::rtt:
                {

                    break;
                }
                case beltpp::isocket_drop::rtt:
                {

                    break;
                }
                case beltpp::isocket_protocol_error::rtt:
                {
                    beltpp::isocket_protocol_error msg;
                    received_packet.get(msg);
                    m_pimpl->writeln_server("protocol error: ");
                    m_pimpl->writeln_server(msg.buffer);
                    psk->send(peerid, beltpp::packet(beltpp::isocket_drop()));

                    break;
                }
                case beltpp::isocket_open_refused::rtt:
                {
                    beltpp::isocket_open_refused msg;
                    received_packet.get(msg);
                    //m_pimpl->writeln_rpc_warning(msg.reason + ", " + peerid);
                    break;
                }
                case beltpp::isocket_open_error::rtt:
                {
                    beltpp::isocket_open_error msg;
                    received_packet.get(msg);
                    //m_pimpl->writeln_rpc_warning(msg.reason + ", " + peerid);
                    break;
                }
                default:
                {
                    m_pimpl->writeln_server("can't handle: " + std::to_string(received_packet.type()) +
                                            ". peer: " + peerid);

                    break;
                }
                }   // switch received_packet.type()
            }
            catch (std::exception const& e)
            {
                ServerError msg;
                msg.message = e.what();
                psk->send(peerid, beltpp::packet(msg));

                throw;
            }
            catch (...)
            {
                ServerError msg;
                msg.message = "unknown exception";
                psk->send(peerid, beltpp::packet(msg));

                throw;
            }
            }   // for (auto& received_packet : received_packets)
        }   // for (auto& pevent_item : wait_sockets)
    }

    if (wait_result & beltpp::event_handler::timer_out)
    {
        m_pimpl->ptr_server_socket->timer_action();
    }

    if (wait_result & beltpp::event_handler::on_demand)
    {
    }

    return code;
}
}


