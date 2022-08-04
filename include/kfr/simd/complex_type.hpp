/** @addtogroup complex
 *  @{
 */
/*
  Copyright (C) 2016 D Levin (https://www.kfrlib.com)
  This file is part of KFR

  KFR is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  KFR is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with KFR.

  If GPL is not suitable for your project, you must purchase a commercial license to use KFR.
  Buying a commercial license is mandatory as soon as you develop commercial activities without
  disclosing the source code of your own applications.
  See https://www.kfrlib.com for details.
 */
#pragma once

#include "constants.hpp"

#ifdef KFR_STD_COMPLEX
#include <complex>
#endif

namespace kfr
{
#ifdef KFR_STD_COMPLEX

template <typename T>
using complex = std::complex<T>;

#else
#ifndef KFR_CUSTOM_COMPLEX

/**
 * @brief Represents the complex numbers. If KFR_STD_COMPLEX is defined, then kfr::complex is an alias for
 * std::complex.
 */
template <typename T>
struct complex
{
    static_assert(is_simd_type<T>, "Incorrect type for complex");
    constexpr static bool is_pod     = true;
    constexpr complex() CMT_NOEXCEPT = default;
    KFR_MEM_INTRINSIC constexpr complex(T re) CMT_NOEXCEPT : re(re), im(0) {}
    KFR_MEM_INTRINSIC constexpr complex(T re, T im) CMT_NOEXCEPT : re(re), im(im) {}
    constexpr complex(const complex&) CMT_NOEXCEPT = default;
    constexpr complex(complex&&) CMT_NOEXCEPT      = default;
    template <typename U>
    KFR_MEM_INTRINSIC constexpr complex(const complex<U>& other) CMT_NOEXCEPT
        : re(static_cast<T>(other.real())),
          im(static_cast<T>(other.imag()))
    {
    }
    template <typename U>
    KFR_MEM_INTRINSIC constexpr complex(complex<U>&& other) CMT_NOEXCEPT : re(std::move(other.real())),
                                                                           im(std::move(other.imag()))
    {
    }
#ifdef CMT_COMPILER_GNU
    constexpr complex& operator=(const complex&) CMT_NOEXCEPT = default;
    constexpr complex& operator=(complex&&) CMT_NOEXCEPT = default;
#else
    complex& operator=(const complex&) = default;
    complex& operator=(complex&&) = default;
#endif
    KFR_MEM_INTRINSIC constexpr const T& real() const CMT_NOEXCEPT { return re; }
    KFR_MEM_INTRINSIC constexpr const T& imag() const CMT_NOEXCEPT { return im; }
    KFR_MEM_INTRINSIC constexpr void real(T value) CMT_NOEXCEPT { re = value; }
    KFR_MEM_INTRINSIC constexpr void imag(T value) CMT_NOEXCEPT { im = value; }

private:
    T re;
    T im;
};
#endif
#endif

} // namespace kfr