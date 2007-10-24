/**
 * osgGIS - GIS Library for OpenSceneGraph
 * Copyright 2007 Glenn Waldron and Pelican Ventures, Inc.
 * http://osggis.org
 *
 * osgGIS is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>
 */

#include <osgGIS/Filter>

using namespace osgGIS;

Filter::Filter()
{
}


Filter::~Filter()
{
}

void
Filter::setName( const std::string& value )
{
    name = value;
}


const std::string&
Filter::getName() const
{
    return name;
}


void
Filter::setProperty( const Property& p )
{
    //NOP
}

Properties
Filter::getProperties() const
{
    return Properties();
}

void
Filter::reset( ScriptContext* _context )
{
    if ( next_filter.valid() )
    {
        next_filter->reset( _context );
    }
    context = _context;
}


Filter*
Filter::setNextFilter( Filter* _next_filter )
{
    //TODO: validate the the input filter is valid here
    next_filter = _next_filter;
    return next_filter.get();
}


Filter*
Filter::getNextFilter()
{
    return next_filter.get();
}


Filter*
Filter::appendFilter( Filter* _last_filter )
{
    if ( next_filter.valid() )
    {
        next_filter->appendFilter( _last_filter );
    }
    else
    {
        next_filter = _last_filter;
    }

    return next_filter.get();
}


bool
Filter::signalCheckpoint()
{
    Filter* next = getNextFilter();
    return next? next->signalCheckpoint() : true;
}
