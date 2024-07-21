template <typename T, typename U> static constexpr bool IsSame = false;

template <typename T> static constexpr bool IsSame<T, T> = true;