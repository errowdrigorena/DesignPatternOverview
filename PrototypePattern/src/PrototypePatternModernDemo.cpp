#include <PrototypePattern_modern/Prototype.hpp>

#include <iostream>
#include <memory>
#include <utility>
#include <vector>

int main()
{
    using prototype_pattern_modern::CsvReportExporter;
    using prototype_pattern_modern::JsonReportExporter;
    using prototype_pattern_modern::ReportExporter;

    std::vector<std::unique_ptr<ReportExporter>> report_templates;
    report_templates.push_back(std::make_unique<CsvReportExporter>("monthly-sales", ';'));
    report_templates.push_back(std::make_unique<JsonReportExporter>("monthly-sales", true));

    for (const auto& report_template : report_templates) {
        report_template->add_column("customer");
        report_template->add_column("amount");
        report_template->add_column("country");
    }

    std::vector<std::unique_ptr<ReportExporter>> customer_reports;

    for (const auto& report_template : report_templates) {
        auto customer_report = report_template->clone();
        customer_report->set_report_title("customer-sales");
        customer_report->add_column("account_manager");
        customer_reports.push_back(std::move(customer_report));
    }

    for (const auto& report_template : report_templates) {
        report_template->describe(std::cout);
    }

    for (const auto& customer_report : customer_reports) {
        customer_report->describe(std::cout);
    }

    return 0;
}
