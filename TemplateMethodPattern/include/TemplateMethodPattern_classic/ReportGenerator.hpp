#pragma once

#include <iosfwd>
#include <string>
#include <string_view>

namespace template_method_pattern_classic {

class ReportGenerator {
public:
    explicit ReportGenerator(std::ostream& out);
    virtual ~ReportGenerator() = default;

    void generate(std::string_view title) const;

protected:
    virtual void before_generate() const;
    virtual std::string collect_data() const = 0;
    virtual std::string format_body(std::string_view raw_data) const = 0;
    virtual bool include_footer() const;
    virtual void after_generate() const;

    std::ostream& out() const;

private:
    std::ostream& out_;
};

}  // namespace template_method_pattern_classic
