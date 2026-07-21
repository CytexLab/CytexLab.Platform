/* 
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/. 
 * 
 * CytexLab (c) 2026
 */

#include "RenderWindowImpl.hpp"


RenderWindowImpl::RenderWindowImpl(WindowImpl *Window)
{
    this->window = Window;
}

RenderWindowImpl::~RenderWindowImpl()
{}

void RenderWindowImpl::SwapBuffers()
{}

void RenderWindowImpl::loadOpenGL33()
{

}