#include <TemplateMethodPattern_classic/AuditReportGenerator.hpp>
#include <TemplateMethodPattern_classic/SalesReportGenerator.hpp>

#include <iostream>

int main()
{
    using namespace template_method_pattern_classic;

    const SalesReportGenerator sales_report{std::cout};
    const AuditReportGenerator audit_report{std::cout};

    sales_report.generate("Monthly sales");
    std::cout << '\n';
    audit_report.generate("Security audit");

    return 0;
}
