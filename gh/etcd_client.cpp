//   Copyright 2017 Carlos O'Ryan
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#include <gh/etcd_client.hpp>
#include <gh/detail/rpc_policies.hpp>

using namespace std::chrono_literals;

namespace gh {

etcd_client::etcd_client(std::shared_ptr<grpc::ChannelCredentials> credentials, std::string url)
    : rpc_backoff_(new gh::detail::exponential_backoff(10ms, 15min))
    , rpc_retry_(new gh::detail::limited_time(4h))
    , credentials_(credentials)
    , mu_()
    , urls_() {
  urls_.emplace_back(url);
}

std::shared_ptr<grpc::Channel> etcd_client::current_channel() {
  return grpc::CreateChannel(urls_[0], credentials_);
}

} // namespace gh
