#include <TemplateMethodPattern_classic/AuditReportGenerator.hpp>

#include <iostream>
#include <string>

namespace template_method_pattern_classic {

using namespace std::string_literals;

AuditReportGenerator::AuditReportGenerator(std::ostream& out)
    : ReportGenerator{out}
{
}

void AuditReportGenerator::before_generate() const
{
    out() << "Opening audit trail\n";
}

std::string AuditReportGenerator::collect_data() const
{
    return "login=ok;permissions=reviewed";
}

std::string AuditReportGenerator::format_body(const std::string_view raw_data) const
{
    auto body = "Audit report from "s;
    body += raw_data;
    return body;
}

bool AuditReportGenerator::include_footer() const
{
    return false;
}

void AuditReportGenerator::after_generate() const
{
    out() << "Closing audit trail\n";
}

}  // namespace template_method_pattern_classic
