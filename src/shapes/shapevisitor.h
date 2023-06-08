#pragma once

struct Circle;
struct Rect;
struct Path;

struct ShapeVisitor
{
    virtual void Visit(const Circle &circle) = 0;
    virtual void Visit(const Rect &rectangle) = 0;
    virtual void Visit(const Path &rectangle) = 0;
};