/*
Created by @PieroCastillo on 2026-06-20
*/
module;

#include <type_traits>

export module tilapia.protocol:sharedring;
import :userqueues;

export namespace Tilapia::Protocol
{
    template<typename T>
    concept TrivialCopy = std::is_trivially_copyable_v<T>;

    template<TrivialCopy T>
    class SharedRing
    {
    private:
        
    public:
        explicit SharedRing()
        {

        };
    };
};