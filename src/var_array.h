// Variadic arrays
// Copyright Laurence Emms 2024


#include <type_traits>


namespace var {
    template <typename T, int m, int n>
    struct ArrayImpl : public ArrayImpl<T, m, n - 1> {
        template <typename ...Ts>
        ArrayImpl(T arg, Ts... args) : data(arg), ArrayImpl<T, m, n - 1>(args...) {}

        ArrayImpl(T arg) : data(arg), ArrayImpl<T, m, n-1>(arg) {}

        ArrayImpl(const ArrayImpl<T, m, n>& other) : data(other.data), ArrayImpl<T, m, n - 1>(other) {}
        ArrayImpl(const ArrayImpl<T, m, n>&& other) : data(other.data), ArrayImpl<T, m, n - 1>(other) {}

        ArrayImpl& operator=(const ArrayImpl<T, m, n>& other) {
            data = other.data;
            ArrayImpl<T, m, n - 1>::operator=(other);

            return *this;
        }

        ArrayImpl& operator=(const ArrayImpl<T, m, n>&& other) {
            data = other.data;
            ArrayImpl<T, m, n - 1>::operator=(other);

            return *this;
        }

        ~ArrayImpl() {}

        T data;
    };

    template <typename T, int m>
    struct ArrayImpl<T, m, 0> {
        ArrayImpl() {} 
        ArrayImpl(T arg) {}

        ArrayImpl(const ArrayImpl<T, m, 0>& other) {}
        ArrayImpl(const ArrayImpl<T, m, 0>&& other) {}

        ArrayImpl& operator=(const ArrayImpl<T, m, 0>& other) {
            return *this;
        }
        ArrayImpl& operator=(const ArrayImpl<T, m, 0>&& other) {
            return *this;
        }
        ~ArrayImpl() {}
    };

    template <typename T, int m, typename Enable = void>
    struct Array {
        template <typename ...Ts>
        Array(Ts... args) : impl(args...) {}

        Array(const Array& other) : impl(other.impl) {}
        Array(const Array&& other) : impl(other.impl) {}

        Array& operator=(const Array& other) {
            impl = other.impl;

            return *this;
        }

        Array& operator=(const Array&& other) {
            impl = other.impl;

            return *this;
        }

        ~Array() {}

        ArrayImpl<T, m, m> impl;
    };

    template <typename T, int m>
    struct Array<T, m, typename std::enable_if<std::is_arithmetic<T>::value>::type> {
        template <typename ...Ts>
        Array(Ts... args) : impl(args...) {}

        Array() : impl(static_cast<T>(0)) {}

        Array(const Array& other) : impl(other.impl) {}
        Array(const Array&& other) : impl(other.impl) {}

        Array& operator=(const Array& other) {
            impl = other.impl;

            return *this;
        }

        Array& operator=(const Array&& other) {
            impl = other.impl;

            return *this;
        }

        ~Array() {}

        ArrayImpl<T, m, m> impl;
    };

    template <int n, typename T, int m>
    T& get(ArrayImpl<T, m, m - n>& array) {
        return array.data;
    }

    template <int n, typename T, int m>
    const T& get(const ArrayImpl<T, m, m - n>& array) {
        return array.data;
    }

    template <int n, typename T, int m>
    T& get(Array<T, m>& array) {
        return get<n, T, m>(array.impl);
    }

    template <int n, typename T, int m>
    const T& get(const Array<T, m>& array) {
        return get<n, T, m>(array.impl);
    }
}
