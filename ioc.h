#ifndef IOC_H
#define IOC_H

#include <map>
#include <memory>
#include <typeinfo>

class IoCContainer
{
public:
    template <typename I, typename T, typename... Args>
    static void registerService(Args&& ...args)
    {
        instance.items.erase((typeid (I)).hash_code());
        instance.items.insert({ {(typeid (I)).hash_code(), std::static_pointer_cast<void>(std::make_shared<T>(std::forward<Args>(args)...))} });
    }

    template <typename I>
    static void registerService(std::shared_ptr<I> service)
    {
        instance.items.erase((typeid (I)).hash_code());
        instance.items.insert({ {(typeid (I)).hash_code(), std::static_pointer_cast<void>(service)} });
    }

    template <typename I>
    static std::shared_ptr<I> getService()
    {
        if (instance.items.count((typeid (I)).hash_code()))
            return std::static_pointer_cast<I>(instance.items[(typeid (I)).hash_code()]);
        else
            return nullptr;
    }

private:
    IoCContainer() = default;
    ~IoCContainer() = default;

    using type_hash = size_t;
    std::map<type_hash, std::shared_ptr<void>> items;

    static IoCContainer instance;
};

#endif // IOC_H
