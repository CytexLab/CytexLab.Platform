# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
# 
# CytexLab (c) 2026

set(include "include")
set(files 
    "src/Base.cpp"
    "src/Mem.cpp"
    "src/Placement.cpp"
    "src/Unicode.cpp"
)
set(deps "")

platform_add_module("Base" "${files}" "${include}" "${deps}")