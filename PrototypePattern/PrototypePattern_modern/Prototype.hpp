#pragma once

#include <algorithm>
#include <iosfwd>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

namespace prototype_pattern_modern
{
    class ReportExporter
    {
    public:
        virtual ~ReportExporter() = default;

        // this only makes sense in C++ when we are talking about polymorfism
        [[nodiscard]] virtual std::unique_ptr<ReportExporter> clone() const = 0;
        virtual void set_report_title(std::string title) = 0;
        virtual void add_column(std::string column) = 0;
        virtual void describe(std::ostream& output) const = 0;
    };

    class CsvReportExporter final : public ReportExporter
    {
    public:
        CsvReportExporter(std::string report_title, char separator)
            : report_title_(std::move(report_title))
            , separator_(separator)
        {
        }

        ~CsvReportExporter() override = default;

        CsvReportExporter(const CsvReportExporter& other)
        {
            const std::scoped_lock lock(other.mutex_);
            report_title_ = other.report_title_;
            separator_ = other.separator_;
            columns_ = other.columns_;
        }

        CsvReportExporter& operator=(const CsvReportExporter& other)
        {
            if (this == &other) {
                return *this;
            }

            const std::scoped_lock lock(mutex_, other.mutex_);
            report_title_ = other.report_title_;
            separator_ = other.separator_;
            columns_ = other.columns_;
            return *this;
        }

        CsvReportExporter(CsvReportExporter&& other) noexcept
        {
            const std::scoped_lock lock(other.mutex_);
            report_title_ = std::move(other.report_title_);
            separator_ = std::exchange(other.separator_, ',');
            columns_ = std::move(other.columns_);
        }

        CsvReportExporter& operator=(CsvReportExporter&& other) noexcept
        {
            if (this == &other) {
                return *this;
            }

            const std::scoped_lock lock(mutex_, other.mutex_);
            report_title_ = std::move(other.report_title_);
            separator_ = std::exchange(other.separator_, ',');
            columns_ = std::move(other.columns_);
            return *this;
        }

        // this only makes sense in C++ when we are talking about polymorfism
        [[nodiscard]] std::unique_ptr<ReportExporter> clone() const override
        {
            return std::make_unique<CsvReportExporter>(*this);
        }

        void set_report_title(std::string title) override
        {
            const std::scoped_lock lock(mutex_);
            report_title_ = std::move(title);
        }

        void add_column(std::string column) override
        {
            const std::scoped_lock lock(mutex_);
            columns_.push_back(std::move(column));
        }

        void describe(std::ostream& output) const override
        {
            const std::scoped_lock lock(mutex_);
            output << "CsvReportExporter{title=" << report_title_
                   << ", separator='" << separator_
                   << "', columns=[";

            print_columns(output);

            output << "]}\n";
        }

    private:
        void print_columns(std::ostream& output) const
        {
            for (std::size_t index = 0; index < columns_.size(); ++index) {
                if (index != 0) {
                    output << ", ";
                }

                output << columns_[index];
            }
        }

        mutable std::mutex mutex_;
        std::string report_title_;
        char separator_;
        std::vector<std::string> columns_;
    };

    class JsonReportExporter final : public ReportExporter
    {
    public:
        JsonReportExporter(std::string report_title, bool pretty_print)
            : report_title_(std::move(report_title))
            , pretty_print_(pretty_print)
        {
        }

        ~JsonReportExporter() override = default;

        JsonReportExporter(const JsonReportExporter& other)
        {
            const std::scoped_lock lock(other.mutex_);
            report_title_ = other.report_title_;
            pretty_print_ = other.pretty_print_;
            columns_ = other.columns_;
        }

        JsonReportExporter& operator=(const JsonReportExporter& other)
        {
            if (this == &other) {
                return *this;
            }

            const std::scoped_lock lock(mutex_, other.mutex_);
            report_title_ = other.report_title_;
            pretty_print_ = other.pretty_print_;
            columns_ = other.columns_;
            return *this;
        }

        JsonReportExporter(JsonReportExporter&& other) noexcept
        {
            const std::scoped_lock lock(other.mutex_);
            report_title_ = std::move(other.report_title_);
            pretty_print_ = std::exchange(other.pretty_print_, false);
            columns_ = std::move(other.columns_);
        }

        JsonReportExporter& operator=(JsonReportExporter&& other) noexcept
        {
            if (this == &other) {
                return *this;
            }

            const std::scoped_lock lock(mutex_, other.mutex_);
            report_title_ = std::move(other.report_title_);
            pretty_print_ = std::exchange(other.pretty_print_, false);
            columns_ = std::move(other.columns_);
            return *this;
        }

        [[nodiscard]] std::unique_ptr<ReportExporter> clone() const override
        {
            return std::make_unique<JsonReportExporter>(*this);
        }

        void set_report_title(std::string title) override
        {
            const std::scoped_lock lock(mutex_);
            report_title_ = std::move(title);
        }

        void add_column(std::string column) override
        {
            const std::scoped_lock lock(mutex_);
            columns_.push_back(std::move(column));
        }

        void describe(std::ostream& output) const override
        {
            const std::scoped_lock lock(mutex_);
            output << "JsonReportExporter{title=" << report_title_
                   << ", pretty_print=" << std::boolalpha << pretty_print_
                   << ", columns=[";

            for (std::size_t index = 0; index < columns_.size(); ++index) {
                if (index != 0) {
                    output << ", ";
                }

                output << columns_[index];
            }

            output << "]}\n";
        }

    private:
        mutable std::mutex mutex_;
        std::string report_title_;
        bool pretty_print_;
        std::vector<std::string> columns_;
    };
}  // namespace prototype_pattern_modern
