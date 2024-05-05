// Variadic arrays
// Copyright Laurence Emms 2024


namespace var {
    template <typename T, int n>
    struct Array : public Array<T, n - 1> {
        template <typename ...Ts>
        Array(T arg, Ts... args) : data(arg), Array<T, n - 1>(args...) {}

        T data;
    };

    template <typename T>
    struct Array<T, 0> {
        Array() {}
    };

    template <int n, typename T>
    T& get(Array<T, n + 1>& array) {
        return array.data;
    }

    template <int n, typename T>
    const T& get(const Array<T, n + 1>& array) {
        return array.data;
    }
}
