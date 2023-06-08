#pragma once

#include <stdexcept>

#include "shapes/shape.h"
#include "shapes/path.h"
#include "shapes/rect.h"
#include "shapes/circle.h"

#include "toolsettings.h"

struct ShapeFactory
{
    static std::unique_ptr<Shape> Create(ToolSettings &settings, wxPoint origin)
    {
        switch (settings.currentTool)
        {
        case ToolType::Pen:
            return std::make_unique<Path>(settings.currentColor, settings.currentWidth, origin);
        case ToolType::Rect:
            return std::make_unique<Rect>(settings.currentColor, origin);
        case ToolType::Circle:
            return std::make_unique<Circle>(settings.currentColor, origin);
        default:
            throw std::runtime_error("ShapeFactory::CreateObject: Unknown tool type");
        }
    }
};