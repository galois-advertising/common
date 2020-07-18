#include <memory>
#include <mutex>
#include <atomic>

namespace galois::common {
/**************************************************
§6.7 [stmt.dcl] p4
C++11 removes the need for manual locking. 
Concurrent execution shall wait if a static local variable is already being initialized.
If control enters the declaration concurrently while the variable is being initialized, 
the concurrent execution shall wait for completion of the initialization.
**************************************************/
template<class T>
T* get_singleton() {
    static T _s_instance;
    return &_s_instance;
};

template<class T>
class singleton {
public:
    template <class...args_types> 
    static T* instance(args_types...args) {
        if (nullptr == _s_instance) {
            std::lock_guard<std::mutex> guard(_mtx);
            if (nullptr == _s_instance) {
                _s_instance = new T(args...);
            }
        }
        return _s_instance;
    }

    singleton() = delete;
    singleton(const singleton&) = delete;
    singleton & operator=(const singleton&) = delete;

private:
    static std::atomic<T*> _s_instance;
    static std::mutex _mtx;
};
template<class T>
std::atomic<T*> singleton<T>::_s_instance = nullptr;

template<class T>
std::mutex singleton<T>::_mtx;
}
