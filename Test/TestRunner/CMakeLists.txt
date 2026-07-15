# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.
# 
# CytexLab (c) 2026

set(include "")
set(files "src/main.cpp")
set(deps "Base" "Interface" "WinInterface")

platform_add_executable("TestRunner" "${files}" "${include}" "${deps}")