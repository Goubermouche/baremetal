## My personal, opinionated, utility library
> **This library still under development, and I change the interface/implementation of core classes pretty often**

This is my personal, opinionated library, which I use as a base for most of my toy projects. It's meant to be a replacement for the C++ STL, but it still relies on it (although I'm working on removing all dependencies from it and become STD-free).

## Bits
- [**Allocators**](./utility/allocators)
  - Pool allocator
- [**Algorithms**](./utility/algorithms)
  - Stable sort
- [**Containers**](./utility/containers)
  - Array
  - Dynamic array
  - Dynamic string
  - Map
- [**Math**](./utility/math)
  - Vector
- [**System**](./utility/system)
  - Console/file interfaces
- [**Custom type names**]
  - This library attempts to provide alternatives to the C/C++ type names, which can be seen [here](./utility/types.h). The custom type names can be used in the global namespace by using the `using namespace utility::types` directive. 

## Style guide
- Namespaces
  - Everything should be placed in a named namespace, with a trailing comment specifying the name of the closed namespace:
    ```cpp
    namespace test {
    } // namespace test
    ```
  - Namespaces containing the implementation of a behavior which isn't used elsewhere shall use the `detail` namespace, which is reserved for this sole purpose. 
- Generic containers
  - Generic containers should expose the underlying types using the `using` keyword, in the public scope of the relevant container: 
    ```cpp
    template<typename value, template size>
    class example {
    public:
      using element_type = value;
      using size_type = size;
    }
    ```
  - Generic containers should use the public variant of every generic type, as opposed to the name specified in the template parameter list.
  - Every container should expose the type of the available iterators, if applicable:    
    ```cpp
    template<typename value, template size>
    class example {
    public:
      using element_type = value;
      using size_type = size;

      using const_iterator = const element_type*;
      using iterator = element_type*;
    }
    ```

