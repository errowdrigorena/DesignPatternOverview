#pragma once

#include <TemplateMethodPattern_classic/ReportGenerator.hpp>

#include <iosfwd>
#include <string>
#include <string_view>

namespace template_method_pattern_classic {

class SalesReportGenerator : public ReportGenerator {
public:
    explicit SalesReportGenerator(std::ostream& out);

protected:
    std::string collect_data() const override;
    std::string format_body(std::string_view raw_data) const override;
};

}  // namespace template_method_pattern_classic
