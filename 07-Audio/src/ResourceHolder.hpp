#pragma once

#include <map>
#include <memory>
#include <string>
#include <stdexcept>
#include <cassert>

template<typename Resource>
class ResourceHolder
{
public:
	void load(const std::string& identifier, const std::string& file_path);
	Resource& get(const std::string& identifier);

private:
	std::map<std::string, std::unique_ptr<Resource>> m_resources;
};

template <typename Resource>
void ResourceHolder<Resource>::load(const std::string& identifier, const std::string& file_path)
{
	auto resource = std::make_unique<Resource>();
	if(!resource->loadFromFile(file_path))
	{
		throw std::runtime_error("Failed to load resource '" + file_path + "'");
	}

	m_resources.insert({identifier, std::move(resource)});
}

template <typename Resource>
Resource& ResourceHolder<Resource>::get(const std::string& identifier)
{
	auto found = m_resources.find(identifier);
	assert(found != m_resources.end());

	return *found->second;
}
