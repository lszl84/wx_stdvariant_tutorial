#pragma once

#include <wx/graphics.h>

#include "shape.h"

struct Circle : Shape
{
    double radius;
    wxPoint2DDouble center;
    wxColour color;

    Circle() = default;
    Circle(const wxColour &color, const wxPoint2DDouble &center) : radius{0.0}, center{center}, color{color}
    {
    }

    ~Circle() noexcept = default;

    void Draw(wxGraphicsContext &gc) const override
    {
        gc.SetPen(wxPen(color));
        gc.SetBrush(wxBrush(color));
        gc.DrawEllipse(center.m_x - radius, center.m_y - radius, radius * 2, radius * 2);
    }

    void HandleCreationByMouseDrag(wxPoint currentDragPoint) override
    {
        radius = std::sqrt(std::pow(currentDragPoint.x - center.m_x, 2) + std::pow(currentDragPoint.y - center.m_y, 2));
    }

    void Accept(ShapeVisitor &visitor) const override
    {
        return visitor.Visit(*this);
    }
};