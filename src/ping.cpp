#include "ping.hpp"

#include <atomic>

#include <fmt/format.h>

#include <userver/clients/dns/component.hpp>
#include <userver/components/component.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/assert.hpp>

namespace pg_service_template {

namespace {

class Ping final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-ping";

  Ping(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& component_context)
      : HttpHandlerBase(config, component_context) {}

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {

    counter_++;

    return std::to_string(counter_);
  }


  mutable std::atomic<int> counter_ = 0;
};

}  // namespace

void AppendPing(userver::components::ComponentList& component_list) {
  component_list.Append<Ping>();
  component_list.Append<userver::clients::dns::Component>();
}

}  // namespace pg_service_template
