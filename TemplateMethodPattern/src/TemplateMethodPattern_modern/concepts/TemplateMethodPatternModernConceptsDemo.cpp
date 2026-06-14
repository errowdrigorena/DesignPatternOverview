#include <TemplateMethodPattern_modern/concepts/ReportWorkflow.hpp>

#include <iostream>
#include <string>
#include <string_view>

namespace {

using namespace std::string_literals;

struct SalesReportSteps {
    std::string collect_data() const
    {
        return "orders=42;revenue=1200";
    }

    std::string format_body(const std::string_view raw_data) const
    {
        auto body = "Sales report from "s;
        body += raw_data;
        return body;
    }
};

struct AuditReportSteps {
    void before_generate(std::ostream& out) const
    {
        out << "Opening audit trail\n";
    }

    std::string collect_data() const
    {
        return "login=ok;permissions=reviewed";
    }

    std::string format_body(const std::string_view raw_data) const
    {
        auto body = "Audit report from "s;
        body += raw_data;
        return body;
    }

    bool include_footer() const
    {
        return false;
    }

    void after_generate(std::ostream& out) const
    {
        out << "Closing audit trail\n";
    }
};

}  // namespace

int main()
{
    using template_method_pattern_modern::concepts_based::generate_report;

    generate_report(SalesReportSteps{}, "Monthly sales", std::cout);
    std::cout << '\n';
    generate_report(AuditReportSteps{}, "Security audit", std::cout);

    return 0;
}
