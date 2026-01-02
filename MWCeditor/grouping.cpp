#include "grouping.h"

#include <algorithm>
#include <cctype>
#include <cwctype>

// Forward declarations for helpers implemented elsewhere
std::wstring* SanitizeTagStr(std::wstring& str);
bool StartsWithStr(const std::wstring& target, const std::wstring& str);

std::wstring NormalizePartBase(const std::wstring& base)
{
	size_t digitOffset = base.size();
	while (digitOffset > 0 && std::iswdigit(base[digitOffset - 1]))
		--digitOffset;

	if (digitOffset == base.size())
		return base;

	std::wstring normalizedDigits = base.substr(digitOffset);
	size_t nonZeroOffset = normalizedDigits.find_first_not_of(L'0');
	normalizedDigits = nonZeroOffset == std::wstring::npos ? L"0" : normalizedDigits.substr(nonZeroOffset);

	return base.substr(0, digitOffset) + normalizedDigits;
}

std::wstring ExtractBaseFromKey(const std::wstring& key, const std::wstring& identifier)
{
	if (key.size() < identifier.size())
		return L"";

	return key.substr(0, key.size() - identifier.size());
}

std::wstring GetItemPrefix(const std::wstring& variableKey, const std::vector<Item>* sortedItemTypes)
{
	for (auto& item : *sortedItemTypes)
	{
		std::wstring name = *SanitizeTagStr(item.GetName());
		if (variableKey.substr(0, name.size()) == name)
			for (auto i = static_cast<uint32_t>(name.size()); i < variableKey.size(); i++)
				if (!isdigit(variableKey[i]))
					return variableKey.substr(0, i);
	}
	return std::wstring();
}

static GroupingResolution ResolveAlias(const std::wstring& sanitizedKey, const std::map<std::wstring, GroupingAlias>& aliasLookup)
{
	GroupingResolution resolution{ sanitizedKey, sanitizedKey, L"", sanitizedKey };

	if (sanitizedKey.empty() || aliasLookup.empty())
		return resolution;

	auto aliasIt = std::find_if(aliasLookup.begin(), aliasLookup.end(), [&](const auto& alias) {
		return !alias.first.empty() && StartsWithStr(sanitizedKey, alias.first);
	});

	if (aliasIt == aliasLookup.end())
		return resolution;

	resolution.groupingKey = aliasIt->second.groupingKey.empty() ? aliasIt->first : aliasIt->second.groupingKey;
	resolution.displayLabel = aliasIt->second.displayLabel.empty() ? resolution.groupingKey : aliasIt->second.displayLabel;
	resolution.ruleSource = L"alias";
	resolution.matchedPrefix = aliasIt->first;

	return resolution;
}

GroupingResolution ResolveGroupingKey(const std::wstring& rawKey, const std::wstring& sanitizedKey, const std::map<std::wstring, GroupingAlias>& aliasLookup, const GroupingIdentifierConfig& identifierConfig)
{
	const std::wstring& baseKey = !sanitizedKey.empty() ? sanitizedKey : rawKey;
	GroupingResolution resolution{ baseKey, baseKey, L"sanitized", baseKey };

	const auto aliasResolution = ResolveAlias(baseKey, aliasLookup);
	if (!aliasResolution.ruleSource.empty())
		return aliasResolution;

	if (identifierConfig.isItemFile && identifierConfig.sortedItemTypes)
	{
		const std::wstring prefix = GetItemPrefix(baseKey, identifierConfig.sortedItemTypes);
		if (!prefix.empty())
		{
			return GroupingResolution{ prefix, prefix, L"item_prefix", prefix };
		}
	}

	return resolution;
}
