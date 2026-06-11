#include <TemplateMethodPattern_modern/callable/CallableReportWorkflow.hpp>

#include <iostream>
#include <string>
#include <string_view>

namespace {

using namespace std::string_literals;

template_method_pattern_modern::callable::ReportSteps make_sales_report()
{
    return {
        .collect_data = [] {
            return "orders=42;revenue=1200";
        },
        .format_body = [](const std::string_view raw_data) {
            auto body = "Sales report from "s;
            body += raw_data;
            return body;
        },
    };
}

template_method_pattern_modern::callable::ReportSteps make_audit_report()
{
    return {
        .collect_data = [] {
            return "login=ok;permissions=reviewed";
        },
        .format_body = [](const std::string_view raw_data) {
            auto body = "Audit report from "s;
            body += raw_data;
            return body;
        },
        .before_generate = [](std::ostream& out) {
            out << "Opening audit trail\n";
        },
        .include_footer = [] {
            return false;
        },
        .after_generate = [](std::ostream& out) {
            out << "Closing audit trail\n";
        },
    };
}

}  // namespace

int main()
{
    using template_method_pattern_modern::callable::generate_report;

    generate_report(make_sales_report(), "Monthly sales", std::cout);
    std::cout << '\n';
    generate_report(make_audit_report(), "Security audit", std::cout);

    return 0;
}
