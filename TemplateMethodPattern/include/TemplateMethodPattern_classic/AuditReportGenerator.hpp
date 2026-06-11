#pragma once

#include <TemplateMethodPattern_classic/ReportGenerator.hpp>

#include <iosfwd>
#include <string>
#include <string_view>

namespace template_method_pattern_classic {

class AuditReportGenerator : public ReportGenerator {
public:
    explicit AuditReportGenerator(std::ostream& out);

protected:
    void before_generate() const override;
    std::string collect_data() const override;
    std::string format_body(std::string_view raw_data) const override;
    bool include_footer() const override;
    void after_generate() const override;
};

}  // namespace template_method_pattern_classic
