#include <PrototypePattern_modern/Prototype.hpp>

#include <gtest/gtest.h>

#include <memory>
#include <sstream>

namespace {

using prototype_pattern_modern::CsvReportExporter;
using prototype_pattern_modern::JsonReportExporter;
using prototype_pattern_modern::ReportExporter;

std::string describe(const ReportExporter& exporter)
{
    std::ostringstream output;
    exporter.describe(output);
    return output.str();
}

TEST(ModernCsvPrototype, DescribesReportWithoutColumns)
{
    const CsvReportExporter exporter{"Quarterly sales", ';'};

    EXPECT_EQ(describe(exporter), "CsvReportExporter{title=Quarterly sales, separator=';', columns=[]}\n");
}

TEST(ModernCsvPrototype, CloneCopiesStateAndCanDiverge)
{
    CsvReportExporter original{"Quarterly sales", ';'};
    original.add_column("region");
    original.add_column("revenue");

    const std::unique_ptr<ReportExporter> clone = original.clone();
    clone->set_report_title("Monthly sales");
    clone->add_column("margin");

    EXPECT_EQ(
        describe(original),
        "CsvReportExporter{title=Quarterly sales, separator=';', columns=[region, revenue]}\n");
    EXPECT_EQ(
        describe(*clone),
        "CsvReportExporter{title=Monthly sales, separator=';', columns=[region, revenue, margin]}\n");
}

TEST(ModernCsvPrototype, CopyAndMoveAssignmentKeepIndependentState)
{
    CsvReportExporter source{"Source", '|'};
    source.add_column("id");
    source.add_column("amount");
    CsvReportExporter copied{"Copied", ','};

    copied = source;
    copied.set_report_title("Copied source");

    CsvReportExporter moved{"Moved", ','};
    moved = std::move(copied);
    moved.add_column("status");

    EXPECT_EQ(describe(source), "CsvReportExporter{title=Source, separator='|', columns=[id, amount]}\n");
    EXPECT_EQ(describe(moved), "CsvReportExporter{title=Copied source, separator='|', columns=[id, amount, status]}\n");
}

TEST(ModernCsvPrototype, SelfAssignmentKeepsState)
{
    CsvReportExporter exporter{"Self", ','};
    exporter.add_column("id");

    exporter = exporter;

    EXPECT_EQ(describe(exporter), "CsvReportExporter{title=Self, separator=',', columns=[id]}\n");
}

TEST(ModernJsonPrototype, DescribesPrettyPrintedReport)
{
    JsonReportExporter exporter{"Audit", true};
    exporter.add_column("actor");
    exporter.add_column("event");

    EXPECT_EQ(describe(exporter), "JsonReportExporter{title=Audit, pretty_print=true, columns=[actor, event]}\n");
}

TEST(ModernJsonPrototype, CloneCopiesStateAndCanDiverge)
{
    JsonReportExporter original{"Audit", false};
    original.add_column("actor");

    const std::unique_ptr<ReportExporter> clone = original.clone();
    clone->set_report_title("Detailed audit");
    clone->add_column("timestamp");

    EXPECT_EQ(describe(original), "JsonReportExporter{title=Audit, pretty_print=false, columns=[actor]}\n");
    EXPECT_EQ(describe(*clone), "JsonReportExporter{title=Detailed audit, pretty_print=false, columns=[actor, timestamp]}\n");
}

TEST(ModernJsonPrototype, CopyAndMoveAssignmentKeepIndependentState)
{
    JsonReportExporter source{"Source", true};
    source.add_column("id");
    source.add_column("payload");
    JsonReportExporter copied{"Copied", false};

    copied = source;
    copied.set_report_title("Copied source");

    JsonReportExporter moved{"Moved", false};
    moved = std::move(copied);
    moved.add_column("checksum");

    EXPECT_EQ(describe(source), "JsonReportExporter{title=Source, pretty_print=true, columns=[id, payload]}\n");
    EXPECT_EQ(describe(moved), "JsonReportExporter{title=Copied source, pretty_print=true, columns=[id, payload, checksum]}\n");
}

TEST(ModernJsonPrototype, SelfAssignmentKeepsState)
{
    JsonReportExporter exporter{"Self", false};
    exporter.add_column("id");

    exporter = exporter;

    EXPECT_EQ(describe(exporter), "JsonReportExporter{title=Self, pretty_print=false, columns=[id]}\n");
}

}  // namespace
