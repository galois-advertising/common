#include <memory>
#include <mutex>

namespace galois::common {
template<class T>
class singleton
{
public:
    template <class...args_types> 
    static std::shared_ptr<T> instance(args_types...args)
    {
        if (nullptr == _s_instance) {
            std::lock_guard<std::mutex> guard(_mtx);
            if (nullptr == _s_instance) {
                _s_instance = std::make_shared<T>(args...);
                if (nullptr == _s_instance) {
                    return nullptr;
                }
            }
        }
        return _s_instance;
    }

    singleton() = delete;
    singleton(const singleton&) = delete;
    singleton & operator=(const singleton&) = delete;

private:
    static std::shared_ptr<T> _s_instance;
    static std::mutex _mtx;
};
template<class T>
std::shared_ptr<T> singleton<T>::_s_instance = nullptr;

template<class T>
std::mutex singleton<T>::_mtx;
}
