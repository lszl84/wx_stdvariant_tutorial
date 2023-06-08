#pragma once

#include <wx/graphics.h>
#include <wx/xml/xml.h>

#include "shapevisitor.h"

struct Shape
{
    virtual void Draw(wxGraphicsContext &gc) const = 0;
    virtual void HandleCreationByMouseDrag(wxPoint currentDragPoint) = 0;
    virtual ~Shape() noexcept {};

    virtual void Accept(ShapeVisitor &visitor) const = 0;
};