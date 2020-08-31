#include <systemd/sd-journal.h>
#include <fmt/core.h>
#include <system_error>
#include <cassert>
#include <string>
#include <optional>
#include <utility>
#include <string_view>

namespace {
using namespace std::literals;

sd_journal* open_journal(const int flags = SD_JOURNAL_LOCAL_ONLY) {
	sd_journal* ret = nullptr;
	const auto errc = sd_journal_open(&ret, flags);
	if (errc < 0) {
		throw std::system_error{ -errc, std::generic_category() };
	}
	assert(ret);
	return ret;
}

struct journal_field {
	std::string name;
	std::string value;
};

std::optional<journal_field> get_next_field(sd_journal* const journal) {
	const void* data_ptr{};
	size_t data_length{};
	const auto status_code = sd_journal_enumerate_data(journal, &data_ptr, &data_length);
	if (status_code == 0) return {};
	if (status_code < 0) throw std::system_error{ -status_code, std::generic_category() };
	assert(data_ptr);
	assert(data_length > 0);
	const char* const data_str_ptr = reinterpret_cast<const char*>(data_ptr);
	const std::string_view data_sv{ data_str_ptr, data_length };
	const auto eq_pos = data_sv.find('=');
	assert(eq_pos != std::string_view::npos);
	const auto field_name = data_sv.substr(0, eq_pos);
	const auto field_value = data_sv.substr(eq_pos + 1);
	return journal_field{std::string{field_name}, std::string{field_value}};
}
} // namespace <anonymous>

int main() {
	sd_journal* const journal = open_journal();
	
	SD_JOURNAL_FOREACH(journal) {
		std::optional<journal_field> field;
		while((field = get_next_field(journal)).has_value()) {
			fmt::print("{:10}: {}\n", field->name, field->value);
		}
		fmt::print("========\n");
	}
	sd_journal_close(journal);
}
