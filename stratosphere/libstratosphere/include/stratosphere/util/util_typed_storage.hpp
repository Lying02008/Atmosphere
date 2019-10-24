/*
 * Copyright (c) 2018-2019 Atmosphère-NX
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include <switch.h>
#include "../defines.hpp"
#include <type_traits>

namespace sts::util {

    template<typename T, size_t Size, size_t Align>
    struct TypedStorage {
        typename std::aligned_storage<Size, Align>::type _storage;
    };

    #define TYPED_STORAGE(T) ::sts::util::TypedStorage<T, sizeof(T), alignof(T)>

    template<typename T>
    static constexpr inline __attribute__((always_inline)) T *GetPointer(TYPED_STORAGE(T) &ts) {
        return reinterpret_cast<T *>(&ts._storage);
    }

    template<typename T>
    static constexpr inline __attribute__((always_inline)) const T *GetPointer(const TYPED_STORAGE(T) &ts) {
        return reinterpret_cast<const T *>(&ts._storage);
    }

    template<typename T>
    static constexpr inline __attribute__((always_inline)) T &GetReference(TYPED_STORAGE(T) &ts) {
        return *GetPointer(ts);
    }

    template<typename T>
    static constexpr inline __attribute__((always_inline)) const T &GetReference(const TYPED_STORAGE(T) &ts) {
        return *GetPointer(ts);
    }

}