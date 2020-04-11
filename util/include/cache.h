#pragma once
#include <unordered_map>
#include <shared_mutex>
#include <thread>
#include "log.h"
#include "thread_pool.h"

namespace galois::common {

template <typename K, typename V>
class cache final
{
private:
    using hash_t = std::unordered_map<K, std::shared_future<V>>;
    hash_t store;
    thread_pool pool;
    std::shared_mutex mtx;
public:
    cache(size_t thread_num) : pool(thread_num) {}
    template<class F, class... Args>
    const V& get(K key, F&& f, Args&&... args) {
        std::shared_lock<std::shared_mutex> read_lock(mtx);
        if (auto res = store.find(key); res == store.end()) {
            read_lock.unlock();
            {
                std::unique_lock<std::shared_mutex> write_lock(mtx);
                // avoid write lock for long time
                if (auto res2 = store.find(key); res2 == store.end()) {
                    store[key] = pool.enqueue(f, args...);
                }
            }
            read_lock.lock();
            return store[key].get();
        } else {
            return res->second.get();
        }
    }
};
}