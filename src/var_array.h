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

    template <typename T, int m>
    size_t length(const Array<T, m>& array) {
        return m;
    }

    template <typename T, int m, int n, typename F>
    void map_impl(ArrayImpl<T, m, n>& result, const ArrayImpl<T, m, n>& lhs, const ArrayImpl<T, m, n>& rhs, T val, F op) {
        result.data = op(lhs.data, rhs.data);

        map_impl<T, m, n - 1, F>(result, lhs, rhs, val, op);
    }

    template <typename T, int m, int n, typename F>
    void map_impl(ArrayImpl<T, m, 0>& result, const ArrayImpl<T, m, 0>& lhs, const ArrayImpl<T, m, 0>& rhs, T val, F op) {
    }

    template <typename T, int m, int n, typename F>
    ArrayImpl<T, m, n> map(const ArrayImpl<T, m, n>& lhs, const ArrayImpl<T, m, n>& rhs, T val, F op) {
        ArrayImpl<T, m, n> result(val);

        map_impl<T, m, n, F>(result, lhs, rhs, val, op);

        return result;
    }

    template <typename T, int m, typename F>
    Array<T, m> map(const Array<T, m>& lhs, const Array<T, m>& rhs, T val, F op) {
        Array<T, m> result(val);

        result.impl = map<T, m, m, F>(lhs.impl, rhs.impl, val, op);

        return result;
    }

    template <typename T, int m, int n, typename F>
    T foldl(const ArrayImpl<T, m, n>& array, T acc, F op) {
        T z = op(acc, array.data);
        return foldl<T, m, n - 1, F>(array, z, op);
    }

    template <typename T, int m, int n, typename F>
    T foldl(const ArrayImpl<T, m, 0>& array, T acc, F op) {
        return acc;
    }

    template <typename T, int m, typename F>
    T foldl(const Array<T, m>& array, T acc, F op) {
        return foldl<T, m, m, F>(array.impl, acc, op);
    }

    template <typename T, int m, int n, typename F>
    T foldr(const ArrayImpl<T, m, n>& array, T acc, F op) {
        return op(array.data, foldl<T, m, n - 1, F>(array, acc, op));
    }

    template <typename T, int m, int n, typename F>
    T foldr(const ArrayImpl<T, m, 0>& array, T acc, F op) {
        return acc;
    }

    template <typename T, int m, typename F>
    T foldr(const Array<T, m>& array, T acc, F op) {
        return foldr<T, m, m, F>(array.impl, acc, op);
    }

    template <typename T, int m, int n, int p>
    void concat_impl_rhs(ArrayImpl<T, m + n, p>& result, const ArrayImpl<T, m, 0>& lhs, const ArrayImpl<T, n, p>& rhs) {
        result.data = rhs.data;
        concat_impl_rhs<T, m, n, p - 1>(result, lhs, rhs);
    }

    template <typename T, int m, int n, int p>
    void concat_impl_rhs(ArrayImpl<T, m + n, 0>& result, const ArrayImpl<T, m, 0>& lhs, const ArrayImpl<T, n, 0>& rhs) {
    }

    template <typename T, int m, int n, int o>
    void concat_impl_lhs(ArrayImpl<T, m + n, o + n>& result, const ArrayImpl<T, m, o>& lhs, const ArrayImpl<T, n, n>& rhs) {
        result.data = lhs.data;
        concat_impl_lhs<T, m, n, o - 1>(result, lhs, rhs);
    }

    template <typename T, int m, int n, int o>
    void concat_impl_lhs(ArrayImpl<T, m + n, n>& result, const ArrayImpl<T, m, 0>& lhs, const ArrayImpl<T, n, n>& rhs) {
        concat_impl_rhs<T, m, n, n>(result, lhs, rhs);
    }

    template <typename T, int m, int n>
    Array<T, m + n> concat(const Array<T, m>& lhs, const Array<T, n>& rhs, T val) {
        Array<T, m + n> result(val);

        concat_impl_lhs<T, m, n, m>(result.impl, lhs.impl, rhs.impl);

        return result;
    }

    /*
    template <typename T, int m, int n>
    ArrayImpl<T, m, n> intercalate(const ArrayImpl<T, m, n>& array, T delim) {
        return array.data, foldl<T, m, n - 1, F>(array, acc, op));
    }

    template <typename T, int m>
    Array<T, m * 2 - 1> intercalate(const Array<T, m>& array, T delim) {
        Array<T, m * 2 - 1> result;
    }
    */
}
