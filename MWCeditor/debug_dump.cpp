#ifdef _DEBUG

#include "utils.h"

#include <sstream>
#include <iomanip>

namespace
{
	std::wstring EscapeJsonString(const std::wstring& input)
	{
		std::wstring escaped;
		escaped.reserve(input.size());
		for (const auto ch : input)
		{
			switch (ch)
			{
			case L'\\': escaped += L"\\\\"; break;
			case L'"': escaped += L"\\\""; break;
			case L'\n': escaped += L"\\n"; break;
			case L'\r': escaped += L"\\r"; break;
			case L'\t': escaped += L"\\t"; break;
			default:
				if (ch < 0x20)
				{
					std::wstringstream ss;
					ss << L"\\u" << std::hex << std::uppercase << std::setw(4) << std::setfill(L'0') << static_cast<int>(ch);
					escaped += ss.str();
				}
				else
				{
					escaped.push_back(ch);
				}
				break;
			}
		}
		return escaped;
	}

	std::wstring BytesToHex(const std::string& data)
	{
		static const wchar_t* hexDigits = L"0123456789ABCDEF";
		std::wstring hex;
		hex.reserve(data.size() * 2);
		for (const unsigned char c : data)
		{
			hex.push_back(hexDigits[(c >> 4) & 0x0F]);
			hex.push_back(hexDigits[c & 0x0F]);
		}
		return hex;
	}

	void WriteJsonString(std::wostream& stream, const std::wstring& value)
	{
		stream << L"\"" << EscapeJsonString(value) << L"\"";
	}

	void EnsureDebugDirectory(std::wstring& directory)
	{
		if (directory.empty())
			return;

		AppendPath(directory, L"debug");
		CreateDirectory(directory.c_str(), NULL);
	}

	std::wstring ResolveDumpPath(const std::wstring& tag)
	{
		std::wstring directory = appfolderpath;
		EnsureDebugDirectory(directory);
		if (directory.empty())
			return L"";

		std::wstring filename;
		if (tag == L"AFTER_LOAD")
			filename = L"debug_after_load.json";
		else if (tag == L"AFTER_GROUPING")
			filename = L"debug_after_grouping.json";
		else if (tag == L"FINAL_STATE")
			filename = L"debug_final_state.json";
		else
			filename = L"debug_" + tag + L".json";

		AppendPath(directory, filename.c_str());
		return directory;
	}
}

void DumpStateToJson(const std::wstring& tag)
{
	const std::wstring dumpPath = ResolveDumpPath(tag);
	if (dumpPath.empty())
		return;

	std::wofstream file(dumpPath.c_str(), std::ios::trunc);
	if (!file.is_open())
		return;

	file << L"{\n";
	file << L"  \"tag\": ";
	WriteJsonString(file, tag);
	file << L",\n";

	file << L"  \"filepath\": ";
	WriteJsonString(file, filepath);
	file << L",\n";

	file << L"  \"variables\": [\n";
	for (size_t i = 0; i < variables.size(); ++i)
	{
		const Variable& var = variables[i];
		file << L"    {\n";
		file << L"      \"index\": " << i << L",\n";
		file << L"      \"pos\": " << var.pos << L",\n";
		file << L"      \"raw_key\": "; WriteJsonString(file, var.raw_key); file << L",\n";
		file << L"      \"key\": "; WriteJsonString(file, var.key); file << L",\n";
		file << L"      \"group\": " << var.group << L",\n";
		file << L"      \"flags\": {\n";
		file << L"        \"added\": " << (var.IsAdded() ? L"true" : L"false") << L",\n";
		file << L"        \"modified\": " << (var.IsModified() ? L"true" : L"false") << L",\n";
		file << L"        \"removed\": " << (var.IsRemoved() ? L"true" : L"false") << L",\n";
		file << L"        \"renamed\": " << (var.IsRenamed() ? L"true" : L"false") << L"\n";
		file << L"      },\n";
		file << L"      \"header\": {\n";
		file << L"        \"containertype\": " << static_cast<uint32_t>(var.header.containertype) << L",\n";
		file << L"        \"containertype_display\": "; WriteJsonString(file, EntryContainer::Ids[var.header.GetContainerType()].second); file << L",\n";
		file << L"        \"keytype\": " << var.header.keytype << L",\n";
		file << L"        \"keytype_display\": "; WriteJsonString(file, EntryValue::Ids[var.header.GetContainerKeyType()].second); file << L",\n";
		file << L"        \"valuetype\": " << var.header.valuetype << L",\n";
		file << L"        \"valuetype_display\": "; WriteJsonString(file, EntryValue::Ids[var.header.GetValueType()].second); file << L",\n";
		file << L"        \"properties_hex\": "; WriteJsonString(file, BytesToHex(var.header.properties)); file << L"\n";
		file << L"      },\n";
		file << L"      \"display_string\": "; WriteJsonString(file, var.GetDisplayString()); file << L",\n";
		file << L"      \"type_display\": "; WriteJsonString(file, var.GetTypeDisplayString()); file << L",\n";
		file << L"      \"value_hex\": "; WriteJsonString(file, BytesToHex(var.value)); file << L",\n";
		file << L"      \"static_value_hex\": "; WriteJsonString(file, BytesToHex(var.static_value)); file << L",\n";
		file << L"      \"static_raw_key\": "; WriteJsonString(file, var.static_raw_key.empty() ? std::wstring() : var.static_raw_key); file << L"\n";
		file << L"    }" << (i + 1 < variables.size() ? L"," : L"") << L"\n";
	}
	file << L"  ],\n";

	file << L"  \"entries\": [\n";
	for (size_t i = 0; i < entries.size(); ++i)
	{
		const GroupingEntry& entry = entries[i];
		file << L"    {\n";
		file << L"      \"index\": " << i << L",\n";
		file << L"      \"key\": "; WriteJsonString(file, entry.key); file << L",\n";
		file << L"      \"display\": "; WriteJsonString(file, entry.display); file << L",\n";
		file << L"      \"ruleSource\": "; WriteJsonString(file, entry.ruleSource); file << L",\n";
		file << L"      \"matchedPrefix\": "; WriteJsonString(file, entry.matchedPrefix); file << L"\n";
		file << L"    }" << (i + 1 < entries.size() ? L"," : L"") << L"\n";
	}
	file << L"  ],\n";

	file << L"  \"groupingAliases\": [\n";
	size_t aliasIndex = 0;
	for (const auto& alias : groupingAliases)
	{
		file << L"    {\n";
		file << L"      \"lookup\": "; WriteJsonString(file, alias.first); file << L",\n";
		file << L"      \"groupingKey\": "; WriteJsonString(file, alias.second.groupingKey); file << L",\n";
		file << L"      \"displayLabel\": "; WriteJsonString(file, alias.second.displayLabel); file << L"\n";
		file << L"    }" << (aliasIndex + 1 < groupingAliases.size() ? L"," : L"") << L"\n";
		aliasIndex++;
	}
	file << L"  ]\n";
	file << L"}\n";
	file.close();
}

#endif
