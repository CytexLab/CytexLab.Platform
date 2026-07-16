/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

extern "C" int __cdecl _purecall()
{
    // Если сюда попали — значит, вызвали чисто виртуальную функцию

    return 0;  // Мы знаем, что такое возможно только при вызове интерфейсов платформу, так что все хорошо
               // Если только пользователь не запоганил ничего)
}