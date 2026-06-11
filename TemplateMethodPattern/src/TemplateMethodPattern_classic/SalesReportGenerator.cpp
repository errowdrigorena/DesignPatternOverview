#include <TemplateMethodPattern_classic/SalesReportGenerator.hpp>

#include <string>

namespace template_method_pattern_classic {

using namespace std::string_literals;

SalesReportGenerator::SalesReportGenerator(std::ostream& out)
    : ReportGenerator{out}
{
}

std::string SalesReportGenerator::collect_data() const
{
    return "orders=42;revenue=1200";
}

std::string SalesReportGenerator::format_body(const std::string_view raw_data) const
{
    auto body = "Sales report from "s;
    body += raw_data;
    return body;
}

}  // namespace template_method_pattern_classic
