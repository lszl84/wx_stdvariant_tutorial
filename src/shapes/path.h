#pragma once

#include <wx/wx.h>

#include <vector>

#include "shape.h"

struct Path : Shape
{
    std::vector<wxPoint2DDouble> points;
    wxColour color;
    int width;

    Path() = default;
    Path(const wxColour &color, int width, const wxPoint2DDouble firstPoint) : points{firstPoint}, color{color}, width{width}
    {
    }

    ~Path() noexcept = default;

    void Draw(wxGraphicsContext &gc) const override
    {
        if (points.size() > 1)
        {
            gc.SetPen(wxPen(color, width));
            gc.StrokeLines(points.size(), points.data());
        }
    }

    void HandleCreationByMouseDrag(wxPoint currentDragPoint) override
    {
        points.push_back(wxPoint2DDouble(currentDragPoint.x, currentDragPoint.y));
    }

    void Accept(ShapeVisitor &visitor) const override
    {
        return visitor.Visit(*this);
    }
};