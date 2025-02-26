// Copyright (C) 2025 Intel Corporation
// SPDX-License-Identifier: Apache-2.0

#include <mutex>
#include <shared_mutex>
#include <unordered_map>

static const int SHARDS = 64;

template <typename Key, typename Value>
class ShardedMap {
 public:
  Value Get(Key key) {
    unsigned int shard = GetShard(key);
    std::unique_lock<std::shared_mutex> lock(shard_mutexes[shard]);
    return map[shard][key];
  }
  void Set(Key key, Value value) {
    unsigned int shard = GetShard(key);
    std::unique_lock<std::shared_mutex> lock(shard_mutexes[shard]);
    if (auto search = map[shard].find(key); search != map[shard].end()) {
      delete search->second;
      map[shard].erase(key);
    }
    map[shard][key] = value;
  }

  void Unset(Key key) {
    unsigned int shard = GetShard(key);
    std::unique_lock<std::shared_mutex> lock(shard_mutexes[shard]);
    delete map[shard][key];
    map[shard].erase(key);
  }

 private:
  unsigned int GetShard(Key key) {
    return (unsigned int)(hash(std::to_string((long)key)) % SHARDS);
  }

  std::unordered_map<Key, Value> map[SHARDS];
  std::shared_mutex shard_mutexes[SHARDS];
  std::hash<std::string> hash;
};
