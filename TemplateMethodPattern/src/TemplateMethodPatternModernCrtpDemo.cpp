#include <TemplateMethodPattern_modern/crtp/CrtpReportGenerator.hpp>

#include <iostream>
#include <string>
#include <string_view>

namespace {

using namespace std::string_literals;

template<typename Derived>
using ReportGenerator = template_method_pattern_modern::crtp::ReportGenerator<Derived>;

struct SalesReport : ReportGenerator<SalesReport> {
private:
    friend ReportGenerator<SalesReport>;

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

struct AuditReport : ReportGenerator<AuditReport> {
private:
    friend ReportGenerator<AuditReport>;

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
    const SalesReport sales_report;
    const AuditReport audit_report;

    sales_report.generate("Monthly sales", std::cout);
    std::cout << '\n';
    audit_report.generate("Security audit", std::cout);

    return 0;
}
