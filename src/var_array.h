// Variadic arrays
// Copyright Laurence Emms 2024


namespace var {
    template <typename T, int m, int n>
    struct ArrayImpl : public ArrayImpl<T, m, n - 1> {
        template <typename ...Ts>
        ArrayImpl(T arg, Ts... args) : data(arg), ArrayImpl<T, m, n - 1>(args...) {}

        T data;
    };

    template <typename T, int m>
    struct ArrayImpl<T, m, 0> {
        ArrayImpl() {}
    };

    template <typename T, int m>
    struct Array {
        template <typename ...Ts>
        Array(Ts... args) : impl(args...) {}

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
