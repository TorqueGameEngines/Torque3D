//-----------------------------------------------------------------------------
// Verve
// Copyright (C) 2014 - Violent Tulip
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//-----------------------------------------------------------------------------
#ifndef _VT_ENUMERATORS_H_
#define _VT_ENUMERATORS_H_

//-----------------------------------------------------------------------------

enum eMove
{
    k_NullMove     = 0,

    k_ForwardMove  = ( 1 << 0 ),
    k_BackwardMove = ( 1 << 1 ),
    k_LeftMove     = ( 1 << 2 ),
    k_RightMove    = ( 1 << 3 ),
    k_UpMove       = ( 1 << 4 ),
    k_DownMove     = ( 1 << 5 ),

    k_XMove        = ( k_LeftMove | k_RightMove ),
    k_YMove        = ( k_ForwardMove | k_BackwardMove ),
    k_ZMove        = ( k_UpMove | k_DownMove ),
};

enum eControlState
{
    k_NullControlState = 0,

    k_PathControlState,
    k_GoToControlState,
};

#endif // _VT_ENUMERATORS_H_