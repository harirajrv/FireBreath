#ifndef H_PLUGINWINDOWLESSWIN
#define H_PLUGINWINDOWLESSWIN

/**********************************************************\ 
Original Author: Anson MacKeracher (amackera) 

Created:    Aug 5, 2010
License:    Dual license model; choose one of two:
            New BSD License
            http://www.opensource.org/licenses/bsd-license.php
            - or -
            GNU Lesser General Public License, version 2.1
            http://www.gnu.org/licenses/lgpl-2.1.html

Copyright 2010 Anson MacKeracher, Firebreath development team
\**********************************************************/

#include "win_common.h"
#include "PluginWindow.h"

#include "Win/KeyCodesWin.h"
#include <boost/function.hpp>

#include "Win/WindowContextWin.h"


namespace FB {
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    /// @class  PluginWindowlessWin
    ///
    /// @brief  Windows specific implementation of PluginWindow.
    ///
    /// This class implements the windowless plugin "window" in FireBreath.
    /// Windowless plugins are different from windowed plugins in that they
    /// don't have a handle to a window, and instead are given a handle to
    /// a drawable from the browser. HandleEvent is called to give us system
    /// events instead of intercepting the events directly through the window. 
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    class PluginWindowlessWin : public PluginWindow
    {
        public:
            PluginWindowlessWin(const WindowContextWindowless&);
            ~PluginWindowlessWin();

            typedef boost::function<void (uint32_t, uint32_t, uint32_t, uint32_t)> InvalidateWindowFunc;

            ////////////////////////////////////////////////////////////////////////////////////////////////////
            /// @fn HDC PluginWindowlessWin::getHDC()
            ///
            /// @brief  Gets the HDC of the plugin window
            ///
            /// @note   The window's HDC is likely to change frequently
            /// @return The HDC 
            ////////////////////////////////////////////////////////////////////////////////////////////////////
            HDC getHDC() const { return m_hdc; }
            void setHDC(HDC hdc) { m_hdc = hdc; }
            void setHWND(HWND browserHwnd) { m_browserHwnd = browserHwnd; }
            void setInvalidateWindowFunc(InvalidateWindowFunc func) { m_invalidateWindow = func; }
            HWND getHWND() const { return m_browserHwnd; } 

            FB::Rect getWindowPosition() const;
            void setWindowPosition(long x, long y, long width, long height);
            void setWindowPosition(FB::Rect pos);

            FB::Rect getWindowClipping() const;
            void setWindowClipping(long top, long left, long bottom, long right);
            void setWindowClipping(FB::Rect clip);

            long getWindowWidth() const { return m_width; }

            long getWindowHeight() const { return m_height; }

            // Converts window-space coordinates into plugin-place coordinates
            void translateWindowToPlugin(long &x, long &y) const;

            // Handle event given to us from NPAPI (windowless plugins don't intercept raw Windows events)
            bool HandleEvent(uint32_t event, uint32_t wParam, uint32_t lParam, LRESULT& lRes);

            // Invalidate the window (Call from any thread)
            void InvalidateWindow() const;

        protected:
            HDC m_hdc;
            HWND m_browserHwnd;
            long m_x, m_y, m_width, m_height; 
            long m_clipTop, m_clipLeft, m_clipBottom, m_clipRight;
            InvalidateWindowFunc m_invalidateWindow;
    };    
};

#endif
