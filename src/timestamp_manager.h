#pragma once

#include "cache_loader.h"

#include <optional.h>

#include <mutex>
#include <unordered_map>

using namespace std::experimental;
using std::experimental::nullopt;

// Caches timestamps of cc files so we can avoid a filesystem reads. This is
// important for import perf, as during dependency checking the same files are
// checked over and over again if they are common headers.
struct TimestampManager {
  optional<int64_t> GetLastCachedModificationTime(CacheLoader* cache_loader,
                                                  const std::string& path);

  void UpdateCachedModificationTime(const std::string& path, int64_t timestamp);

  // TODO: use std::shared_mutex so we can have multiple readers.
  std::mutex mutex_;
  std::unordered_map<std::string, int64_t> timestamps_;
};