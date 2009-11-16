/**********************************************************\ 
Original Author: Richard Bateman (taxilian)

Created:    Sept 24, 2009
License:    Eclipse Public License - Version 1.0
            http://www.eclipse.org/legal/epl-v10.html

Copyright 2009 Richard Bateman, Firebreath development team
\**********************************************************/

#ifndef H_FB_JSAPI
#define H_FB_JSAPI

#include "APITypes.h"
#include "AutoPtr.h"
#include <stdexcept>

namespace FB
{
    class EventHandlerObject;
    class BrowserHostWrapper;
    struct script_error : std::exception
    {
        script_error(std::string error)
            : m_error(error)
        { }
        virtual const char* what() { 
            return m_error.c_str(); 
        }
        std::string m_error;
    };

    struct invalid_arguments : script_error
    {
        invalid_arguments()
            : script_error("Invalid Arguments")
        { }

		invalid_arguments(const std::string& error)
			: script_error(error)
		{ }
    };

    struct object_invalidated : script_error
    {
        object_invalidated()
            : script_error("This object is no longer valid")
        { }
    };
    
    struct invalid_member : script_error
    {
        invalid_member(std::string memberName)
            : script_error("The specified member does not exist: " + memberName)
        { }
    };

    class JSAPI
    {
    public:
        JSAPI(void);
        virtual ~JSAPI(void);

    // Support Reference counting
    protected:
        unsigned int m_refCount;

    public:
        void AddRef();
        unsigned int Release();

        void invalidate();

    protected:
        // Used to fire an event to the listeners attached to this JSAPI
        virtual void FireEvent(std::string eventName, std::vector<variant>&);

    public:
		virtual void registerEventMethod(std::string name, EventHandlerObject *event);
        virtual void unregisterEventMethod(std::string name, EventHandlerObject *event);
        virtual void registerEventInterface(EventHandlerObject *event);
        virtual void unregisterEventInterface(EventHandlerObject *event);
        virtual EventHandlerObject *getDefaultEventMethod(std::string name);
        virtual void setDefaultEventMethod(std::string name, EventHandlerObject *event);

        // Methods to query existance of members on the API
        virtual bool HasMethod(std::string methodName) = 0;
        virtual bool HasProperty(std::string propertyName) = 0;
        virtual bool HasProperty(int idx) = 0;
        virtual bool HasEvent(std::string eventName);

        // Methods to manage properties on the API
        virtual variant GetProperty(std::string propertyName) = 0;
        virtual void SetProperty(std::string propertyName, const variant value) = 0;
        virtual variant GetProperty(int idx) = 0;
        virtual void SetProperty(int idx, const variant value) = 0;

        // Methods to manage methods on the API
        virtual variant Invoke(std::string methodName, std::vector<variant>& args) = 0;

    protected:
        EventMultiMap m_eventMap;
        EventSingleMap m_defEventMap;
        EventIFaceMap m_evtIfaces;
		        
        bool m_valid;
    };

};
#endif