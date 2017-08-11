#include <array>

template<typename T, std::size_t N, std::size_t M>
class matNxM
{
private:
    using layout_t = std::array<T, N * M>;

    layout_t data;
    std::array<char, (N * M) % 4> __padding;

    T & IX(std::size_t row, std::size_t col) { return data[col + row * M]; }
    T const & IX(std::size_t row, std::size_t col) const { return data[col + row * M]; }

public:
    matNxM(void) = default;
    matNxM(T const & elem) { std::fill(std::begin(data), std::end(data), elem); }
    template<typename...InitT>
    matNxM(InitT&&... data) : data{std::forward<InitT>(data)...} {}

    T & operator()(std::size_t row, std::size_t col) { return IX(row, col); }
    T const & operator()(std::size_t row, std::size_t col) const { return IX(row, col); }

    template<typename U = matNxM<T, N, M>, typename = typename std::enable_if<N == 4 && M == 4, U>::type>
    U inverse(void)
    {
        U ret({
            IX(1,1)*IX(2,2)*IX(3,3) + IX(1,2)*IX(2,3)*IX(3,1) + IX(1,3)*IX(2,1)*IX(3,2) -
                (IX(1,1)*IX(2,3)*IX(3,2) + IX(1,2)*IX(2,1)*IX(3,3) + IX(1,3)*IX(2,2)*IX(3,1)),
            IX(0,1)*IX(2,3)*IX(3,2) + IX(0,2)*IX(2,1)*IX(3,3) + IX(0,3)*IX(2,2)*IX(3,1) -
                (IX(0,1)*IX(2,2)*IX(3,3) + IX(0,2)*IX(2,3)*IX(3,1) + IX(0,3)*IX(2,1)*IX(3,2)),
            IX(0,1)*IX(1,2)*IX(3,3) + IX(0,2)*IX(1,3)*IX(3,1) + IX(0,3)*IX(1,1)*IX(3,2) -
                (IX(0,1)*IX(1,3)*IX(3,2) + IX(0,2)*IX(1,1)*IX(3,3) + IX(0,3)*IX(1,2)*IX(3,1)),
            IX(0,1)*IX(1,3)*IX(2,2) + IX(0,2)*IX(1,1)*IX(2,3) + IX(0,3)*IX(1,2)*IX(2,1) -
                (IX(0,1)*IX(1,2)*IX(2,3) + IX(0,2)*IX(1,3)*IX(2,1) + IX(0,3)*IX(1,1)*IX(2,2)),

            IX(1,0)*IX(2,3)*IX(3,2) + IX(1,2)*IX(2,0)*IX(3,3) + IX(1,3)*IX(2,2)*IX(3,0) -
                (IX(1,0)*IX(2,2)*IX(3,3) + IX(1,2)*IX(2,3)*IX(3,0) + IX(1,3)*IX(2,0)*IX(3,0)),
            IX(0,0)*IX(2,2)*IX(3,3) + IX(0,2)*IX(2,3)*IX(3,0) + IX(0,3)*IX(2,0)*IX(3,2) -
                (IX(0,0)*IX(2,3)*IX(3,2)  +IX(0,2)*IX(2,0)*IX(3,3) + IX(0,3)*IX(2,2)*IX(3,0)),
            IX(0,0)*IX(1,3)*IX(3,2) + IX(0,2)*IX(1,0)*IX(3,3) + IX(0,3)*IX(1,2)*IX(3,0) -
                (IX(0,0)*IX(1,2)*IX(3,3) + IX(0,2)*IX(1,3)*IX(3,0) + IX(0,3)*IX(1,0)*IX(3,2)),
            IX(0,0)*IX(1,2)*IX(2,3) + IX(0,2)*IX(1,3)*IX(2,0) + IX(0,3)*IX(1,0)*IX(2,2) -
                (IX(0,0)*IX(1,3)*IX(2,2) + IX(0,2)*IX(1,0)*IX(2,3) + IX(0,3)*IX(1,2)*IX(2,0)),

            IX(1,0)*IX(2,1)*IX(3,3) + IX(1,1)*IX(2,3)*IX(3,0) + IX(1,3)*IX(2,0)*IX(3,1) -
                (IX(1,0)*IX(2,3)*IX(3,1) + IX(1,1)*IX(2,0)*IX(3,3) + IX(1,3)*IX(2,1)*IX(3,0)),
            IX(0,0)*IX(2,3)*IX(3,1) + IX(0,1)*IX(2,0)*IX(3,3) + IX(0,3)*IX(2,1)*IX(3,0) -
                (IX(0,0)*IX(2,1)*IX(3,3) + IX(0,1)*IX(2,3)*IX(3,0) + IX(0,3)*IX(2,0)*IX(3,1)),
            IX(0,0)*IX(1,1)*IX(3,3) + IX(0,1)*IX(1,3)*IX(3,0) + IX(0,3)*IX(1,0)*IX(3,1) -
                (IX(0,0)*IX(1,3)*IX(3,1) + IX(0,1)*IX(1,0)*IX(3,3) + IX(0,3)*IX(1,1)*IX(3,0)),
            IX(0,0)*IX(1,3)*IX(2,1) + IX(0,1)*IX(1,0)*IX(2,3) + IX(0,3)*IX(1,1)*IX(2,0) -
                (IX(0,0)*IX(1,1)*IX(2,3) + IX(0,1)*IX(1,3)*IX(2,0) + IX(0,3)*IX(1,0)*IX(2,1)),

            IX(1,0)*IX(2,2)*IX(3,1) + IX(1,1)*IX(2,0)*IX(3,2) + IX(1,2)*IX(2,1)*IX(3,0) -
                (IX(1,0)*IX(2,1)*IX(3,2) + IX(1,1)*IX(2,2)*IX(3,0) + IX(1,2)*IX(2,0)*IX(3,1)),
            IX(0,0)*IX(2,1)*IX(3,2) + IX(0,1)*IX(2,2)*IX(3,0) + IX(0,2)*IX(2,0)*IX(3,1) -
                (IX(0,0)*IX(2,2)*IX(3,1) + IX(0,1)*IX(2,0)*IX(3,2) + IX(0,2)*IX(2,1)*IX(3,0)),
            IX(0,0)*IX(1,2)*IX(3,1) + IX(0,1)*IX(1,0)*IX(3,2) + IX(0,2)*IX(1,1)*IX(3,0) -
                (IX(0,0)*IX(1,1)*IX(3,2) + IX(0,1)*IX(1,2)*IX(3,0) + IX(0,2)*IX(1,0)*IX(3,1)),
            IX(0,0)*IX(1,1)*IX(2,2) + IX(0,1)*IX(1,2)*IX(2,0) + IX(0,2)*IX(1,0)*IX(2,1) -
                (IX(0,0)*IX(1,2)*IX(2,1) + IX(0,1)*IX(1,0)*IX(2,2) + IX(0,2)*IX(1,1)*IX(2,0))
        });
        return static_cast<float>(1.0 / determinant()) * ret;
    }

    template<typename U = double, typename = typename std::enable_if<N == 4 && M == 4, U>::type>
    double determinant(void)
    {
        double value;
        value =
            IX(0,0)*IX(1,1)*IX(2,2)*IX(3,3) + IX(0,0)*IX(1,2)*IX(2,3)*IX(3,1) + IX(0,0)*IX(1,3)*IX(2,1)*IX(3,2) +
            IX(0,1)*IX(1,0)*IX(2,3)*IX(3,2) + IX(0,1)*IX(1,2)*IX(2,0)*IX(3,3) + IX(0,1)*IX(1,3)*IX(2,2)*IX(3,0) +
            IX(0,2)*IX(1,0)*IX(2,1)*IX(3,3) + IX(0,2)*IX(1,1)*IX(2,3)*IX(3,0) + IX(0,2)*IX(1,3)*IX(2,0)*IX(3,1) +
            IX(0,3)*IX(1,0)*IX(2,2)*IX(3,1) + IX(0,3)*IX(1,1)*IX(2,0)*IX(3,2) + IX(0,3)*IX(1,2)*IX(2,1)*IX(3,0) -
            (IX(0,0)*IX(1,1)*IX(2,3)*IX(3,2) + IX(0,0)*IX(1,2)*IX(2,1)*IX(3,3) + IX(0,0)*IX(1,3)*IX(2,2)*IX(3,1) +
             IX(0,1)*IX(1,0)*IX(2,2)*IX(3,3) + IX(0,1)*IX(1,2)*IX(2,3)*IX(3,0) + IX(0,1)*IX(1,3)*IX(2,0)*IX(3,2) +
             IX(0,2)*IX(1,0)*IX(2,3)*IX(3,1) + IX(0,2)*IX(1,1)*IX(2,0)*IX(3,3) + IX(0,2)*IX(1,3)*IX(2,1)*IX(3,0) +
             IX(0,3)*IX(1,0)*IX(2,1)*IX(3,2) + IX(0,3)*IX(1,1)*IX(2,2)*IX(3,0) + IX(0,3)*IX(1,2)*IX(2,0)*IX(3,1));

        return value;
    }
};

template<typename T, std::size_t N, std::size_t M>
matNxM<T, N, M> operator+(matNxM<T, N, M> const & lhs, matNxM<T, N, M> const & rhs)
{
    matNxM<T, N, M> ret;
    for(std::size_t r = 0; r < N; r += 1) {
        for(std::size_t c = 0; c < M; c += 1) {
            ret(r, c) = lhs(r, c) + rhs(r, c);
        }
    }
    return ret;
}

template<typename T, std::size_t N, std::size_t M>
matNxM<T, N, M> operator-(matNxM<T, N, M> const & lhs, matNxM<T, N, M> const & rhs)
{
    matNxM<T, N, M> ret;
    for(std::size_t r = 0; r < N; r += 1) {
        for(std::size_t c = 0; c < M; c += 1) {
            ret(r, c) = lhs(r, c) - rhs(r, c);
        }
    }
    return ret;
}

template<typename T, std::size_t N, std::size_t M>
matNxM<T, N, M> operator*(matNxM<T, N, M> const & mat, T const & scale)
{
    matNxM<T, N, M> ret;
    for(std::size_t r = 0; r < N; r += 1) {
        for(std::size_t c = 0; c < M; c += 1) {
            ret(r, c) = mat(r, c) * scale;
        }
    }
    return ret;
}
template<typename T, std::size_t N, std::size_t M>
matNxM<T, N, M> operator*(T const & scale, matNxM<T, N, M> const & mat) { return mat * scale; }

template<typename T, std::size_t N>
class matNxM<T, N, 1>
{
private:
    using layout_t = std::array<T, N>;

    layout_t data;
    std::array<char, N % 4> __padding;

public:
    using iterator = typename layout_t::iterator;
    using const_iterator = typename layout_t::const_iterator;

    matNxM(void) = default;
    matNxM(T const & elem) { std::fill(std::begin(data), std::end(data), elem); }
    template<typename...InitT>
    matNxM(InitT&&... data) : data{std::forward<InitT>(data)...} {}

    T & operator()(std::size_t idx) { return data[idx]; }
    T const & operator()(std::size_t idx) const { return data[idx]; }

    T length(void) const
    {
        return static_cast<T>(sqrt(dot(*this)));
    }

    matNxM<T, N, 1> & normalize(void)
    {
        T len2 = dot(*this);
        if(len2 > 0) {
            T len_inv = 1 / sqrt(len2);
            for(std::size_t i = 0; i < N; i += 1) {
                data[i] *= len_inv;
            }
        }
        return *this;
    }

    T dot(matNxM<T, N, 1> const & rhs) const
    {
        T dot = 0;
        for(std::size_t i = 0; i < N; i += 1) {
            dot += data[i] * rhs.data[i];
        }
        return dot;
    }

    template<typename U = matNxM<T, N, 1>, typename = typename std::enable_if<N == 3>::type>
    U cross(matNxM<T, 3, 1> const & rhs) const
    {
        return {
            data[1]*rhs.data[2] - data[2]*rhs.data[1],
            data[2]*rhs.data[0] - data[0]*rhs.data[2],
            data[0]*rhs.data[1] - data[1]*rhs.data[0],
        };
    }

    typename layout_t::iterator begin(void) { return std::begin(data); }
    typename layout_t::const_iterator begin(void) const { return std::begin(data); }
    typename layout_t::iterator end(void) { return std::end(data); }
    typename layout_t::const_iterator end(void) const { return std::end(data); }
};

#ifdef _DEBUG
template<typename T, size_t N, size_t M>
std::ostream & operator<<(std::ostream & out, matNxM<T, N, M> const & mat)
{
    for(std::size_t r = 0; r < N; r += 1) {
        std::string pref = "";
        for(std::size_t c = 0; c < M; c += 1) {
            out << pref << mat(r, c);
            pref = ", ";
        }
        out << "\n";
    }
    return out;
}
#endif

using vec2 = matNxM<float, 2, 1>;
using vec3 = matNxM<float, 3, 1>;
using vec4 = matNxM<float, 4, 1>;
using mat4 = matNxM<float, 4, 4>;
