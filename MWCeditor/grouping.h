#pragma once

#include <map>
#include <string>
#include <vector>

#include "variable.h"

struct GroupingAlias
{
	std::wstring groupingKey;
	std::wstring displayLabel;
};

struct GroupingIdentifierConfig
{
	bool isItemFile = false;
	const std::vector<Item>* sortedItemTypes = nullptr;
};

struct GroupingResolution
{
	std::wstring groupingKey;
	std::wstring displayLabel;
	std::wstring ruleSource;
	std::wstring matchedPrefix;
};

struct GroupingEntry
{
	std::wstring key;
	std::wstring display;
	std::wstring ruleSource;
	std::wstring matchedPrefix;
};

std::wstring NormalizePartBase(const std::wstring& base);
std::wstring ExtractBaseFromKey(const std::wstring& key, const std::wstring& identifier);

std::wstring GetItemPrefix(const std::wstring& variableKey, const std::vector<Item>* sortedItemTypes);
GroupingResolution ResolveGroupingKey(const std::wstring& rawKey, const std::wstring& sanitizedKey, const std::map<std::wstring, GroupingAlias>& aliasLookup, const GroupingIdentifierConfig& identifierConfig);
