#pragma once

#include <iostream>
#include <type_traits>
#include <array>
#include <string>
#include <sstream>
#include <cstring>
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>

/**
 * @brief Brief explaination of namespace ip
 *
 * Detailed explaination of namespace MyNamespace
 */
namespace ip
{

    /**
    * Print IP address
    * @tparam Integer integer number type, representing IP
    * @param[in] ip IP address to be printed
    * @param[in] os output stream where to print IP address
    */
    template <typename Num,
              typename Fake = std::enable_if_t<std::is_integral_v<Num>, void>>
    void print_ip(Num ip, std::ostream& os = std::cout) {

        const size_t _size = sizeof(ip);
        std::vector<int> nums;
	    for (unsigned i = 0; i < _size; i++) {
            nums.push_back(ip & 0xFF);
		    ip >>= 8;
	    }

        for (auto it = nums.rbegin(); it != nums.rend(); it++) {
            os << *it;
            if (std::next(it) != nums.rend()) {
                os << '.';
            }
        }
    }
    
    /**
     * Prints IP address
     * @tparam 
     * 
     */
    template <typename C,
              typename Fake = std::enable_if_t<std::is_same_v<C, std::string>, void>>
    void print_ip(const C& ip, std::ostream& os = std::cout) {
        os << ip;
    }

    template <typename C> 
    struct is_container : std::false_type { };
    template <typename... Ts> struct is_container<std::list<Ts...> > : std::true_type { };
    template <typename... Ts> struct is_container<std::vector<Ts...> > : std::true_type { };
    template <typename T> 
    inline constexpr bool is_container_v = is_container<T>::value;

    /**
    * Prints IP address
    * @tparam One of list<T> or vector<T>
    * @param[in] container IP address to be printed
    * @param[in] os output stream where to print IP address
    */
    template <typename C, 
              typename Fake = std::enable_if_t<is_container_v<C>, void>>
    void print_ip(C&& container, std::ostream& os = std::cout) {
        if (container.empty()) {
            return;
        }

        std::copy(
            std::begin(container),
            std::prev(std::end(container)),
            std::ostream_iterator<typename C::value_type>(os, ".")
        );
        os << *std::rbegin(container);
    }

    template <typename... Args>
    struct is_homogeneous_tuple {
        static constexpr bool value = true;
    };

    template <typename T>
    struct is_homogeneous_tuple<T> {
        static constexpr bool value = true;
    };

    template <typename T, typename U, typename... Args>
    struct is_homogeneous_tuple<T, U, Args...> {
        static constexpr bool value = !std::is_same_v<T, U>
                                      ? false
                                      : is_homogeneous_tuple<U, Args...>::value;
    };

    template <typename... Args>
    inline constexpr bool is_homogeneous_tuple_v = is_homogeneous_tuple<Args...>::value;

    template <std::size_t index, typename... Args>
    void print_ip_tuple_utils(const std::tuple<Args...>& ip, std::ostream& os = std::cout) {
        if constexpr (index >= sizeof...(Args)) {
            return;
        } else {
            os << '.' << std::get<index>(ip);
            print_ip_tuple_utils<index + 1, Args...>(ip, os);
        }
    }

    /**
    * Prints IP address
    * @tparam Args... type pack with identical types
    * @param[in] ip IP address to be printed
    * @param[in] os output stream where to print IP address
    */
    template <typename... Args,
              typename Fake = std::enable_if_t<is_homogeneous_tuple_v<Args...>, void>>
    void print_ip(const std::tuple<Args...>& ip, std::ostream& os = std::cout) {
        if constexpr (std::tuple_size<std::tuple<Args...>>::value == 0) {
            return;
        } else {
            os << std::get<0>(ip);
            print_ip_tuple_utils<1, Args...>(ip, os);
        }
    }

} // namespace ip
