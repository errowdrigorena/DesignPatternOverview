#pragma once

#include <string>

namespace proxy_pattern_modern {

class RealService {
public:
    explicit RealService(std::string service_id);
    [[nodiscard]] std::string request() const;

private:
    std::string service_id_;
};

}  // namespace proxy_pattern_modern
