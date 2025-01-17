/******************************************************************************\

    CAMotics is an Open-Source simulation and CAM software.
    Copyright (C) 2011-2015 Joseph Coffland <joseph@cauldrondevelopment.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

\******************************************************************************/

/****************************************************************************
** $Id: dl_exception.h 3591 2006-10-18 21:23:25Z andrew $
**
** Copyright (C) 2001-2003 RibbonSoft. All rights reserved.
** Copyright (C) 2001 Robert J. Campbell Jr.
**
** This file is part of the dxflib project.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** Licensees holding valid dxflib Professional Edition licenses may use 
** this file in accordance with the dxflib Commercial License
** Agreement provided with the Software.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.ribbonsoft.com for further details.
**
** Contact info@ribbonsoft.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

#ifndef DL_EXCEPTION_H
#define DL_EXCEPTION_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/**
 * Used for exception handling.
 */
class DL_Exception {}
;

/**
 * Used for exception handling.
 */
class DL_NullStrExc : public DL_Exception {}
;

/**
 * Used for exception handling.
 */
class DL_GroupCodeExc : public DL_Exception {
    DL_GroupCodeExc(int gc=0) : groupCode(gc) {}
    int groupCode;
};
#endif

