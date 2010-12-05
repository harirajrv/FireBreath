
/**********************************************************\
 Original Author: Georg Fritzsche
 
 Created:    Nov 6, 2010
 License:    Dual license model; choose one of two:
 New BSD License
 http://www.opensource.org/licenses/bsd-license.php
 - or -
 GNU Lesser General Public License, version 2.1
 http://www.gnu.org/licenses/lgpl-2.1.html
 
 Copyright 2010 Georg Fritzsche and the Firebreath development team
 \**********************************************************/

#include "OneShotManager.h"
#import <Cocoa/Cocoa.h>
#include <iostream>
#include <fstream>
#include <cassert>

@interface OneShotManagerHelper : NSObject {
    FB::OneShotManager* manager_;
}

- (id)initWithManager:(FB::OneShotManager *)manager;
- (void)dealloc;

- (void)disconnect;
- (void)doStuff:(id)obj;
@end

@implementation OneShotManagerHelper

- (id)initWithManager:(FB::OneShotManager *)manager
{
    if ((self = [super init])) 
    {
        manager_ = manager;
    }
    
    return self;
}

- (void)dealloc
{
    manager_ = 0;
    [super dealloc];
}

- (void)disconnect
{
    manager_ = 0;
}

- (void)doStuff:(id)obj
{
    if (manager_) {
        manager_->shoot();
    }
}

@end

namespace 
{
    OneShotManagerHelper *getHelper(FB::OneShotManager *manager)
    {
        static OneShotManagerHelper *helper = [[OneShotManagerHelper alloc] initWithManager:manager];
        return helper;
    }
}

FB::OneShotManager::OneShotManager()
{
    
}

FB::OneShotManager::~OneShotManager()
{
    [getHelper(this) disconnect];
    m_sinks.clear();
}

void FB::OneShotManager::push(NPP npp, OneShotCallback sink)
{
    m_sinks.insert(std::make_pair(npp, sink));
    [getHelper(this) performSelectorOnMainThread:@selector(doStuff:) withObject:nil waitUntilDone:NO];
}

void FB::OneShotManager::clear(NPP npp)
{
    m_sinks.erase(npp);
}

FB::OneShotManager& FB::OneShotManager::getInstance()
{
    static OneShotManager manager;
    return manager;
}

void FB::OneShotManager::shoot()
{
    for (SinkMap::const_iterator it = m_sinks.begin(); it != m_sinks.end(); ++it)
    {
        it->second(it->first, 0);
    }
    
    m_sinks.clear();
}