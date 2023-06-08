#pragma once

#include <wx/graphics.h>

#include "shape.h"

struct Rect : Shape
{
    wxRect2DDouble rect;
    wxColour color;

    Rect() = default;
    Rect(const wxColour &color, const wxPoint2DDouble origin)
        : rect{origin.m_x, origin.m_y, 0.0, 0.0}, color{color}
    {
    }

    ~Rect() noexcept = default;

    void Draw(wxGraphicsContext &gc) const override
    {
        gc.SetPen(wxPen(color));
        gc.SetBrush(wxBrush(color));
        gc.DrawRectangle(rect.m_x, rect.m_y, rect.m_width, rect.m_height);
    }

    void HandleCreationByMouseDrag(wxPoint currentDragPoint) override
    {
        rect.SetRightBottom(currentDragPoint);
    }

    void Accept(ShapeVisitor &visitor) const override
    {
        return visitor.Visit(*this);
    }
};